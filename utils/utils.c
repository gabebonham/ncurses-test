#include "./utils.h"
#include <string.h>
int getStringWidth(const char *str) {
    int width = 0, line_len = 0;
    for (const char *p = str; *p; p++) {
        if (*p == '\n') {
            if (line_len > width) width = line_len;
            line_len = 0;
        } else {
            line_len++;
        }
    }
    if (line_len > width) width = line_len;
    return width;
}
Widget **resizeWidgetArray(Widget **sourceArray, int currentSize, int newSize) {
    Widget **array = realloc(sourceArray, newSize * sizeof(Widget*));
    if (!array) {
        fprintf(stderr, "resizeWidgetArray: realloc failed\n");
        return sourceArray;  // keep old array if realloc fails
    }

    // Initialize new slots to NULL
    if (newSize > currentSize) {
        for (int i = currentSize; i < newSize; i++) {
            array[i] = NULL;
        }
    }

    return array;
}

Widget** addToWidgetList(Widget **array, Widget **newWidget, int currentSize) {
    int newSize = currentSize + 1;
    Widget **newList = resizeWidgetArray(array,currentSize, newSize);
    newList[newSize-1] = *newWidget;
    return newList;
}
int ruleOfThree(int tr, int bl,int br){
    int right = tr/br;
    return bl*right;
}
void getProportionalUnits(Widget* widget) {
    if (!widget) return;

    int parentW = 0, parentH = 0;
    float unitH, unitW;

    if (!widget->parentWidget) {
        getmaxyx(stdscr, parentH, parentW);
    } else if (widget->parentWidget->win) {
        parentH = widget->parentWidget->height;
        parentW = widget->parentWidget->width;
        
    } else {
        getmaxyx(stdscr, parentH, parentW);
    }

    // unitH = (float)parentH / propH;
    // unitW = (float)parentW / propW;

    // widget->units.unitH = unitH;
    // widget->units.unitW = unitW;
    // if (widget->type==WSCREEN){
    //     widget->width = widget->parentWidget->width*widget->wper;
    //     widget->height = widget->parentWidget->height*widget->hper;
    // }
    // if (widget->type==WINPUT){
    //     widget->width = widget->width;
    //     widget->height = widget->height;
    // }
}

void updateDimensions(Widget *widget){
    getProportionalUnits(widget);
    
    widget->height = widget->units.unitH*widget->h;
    widget->width = widget->units.unitW*widget->w;
    
    widget->xPos = widget->x == 0 ? 0 : widget->units.unitW * widget->x;
    widget->yPos = widget->y == 0 ? 0 : widget->units.unitH * widget->y;
}

void resizeWidget(Widget *widget) {
    
    // if (widget->parentWidget && widget->parentWidget->win) {
    //     mvderwin(widget->win, widget->yPos, widget->xPos);
    // } else {
    //     mvwin(widget->win, widget->yPos, widget->xPos);
    // }
    // if (widget->type!=WINPUT) wresize(widget->win, (int)widget->height, (int)widget->width);
    // wresize(widget->win, (int)widget->height, (int)widget->width);
    wclear(widget->win);
    box(widget->win, 0, 0);

    if (widget->label && strcmp(widget->label, "label") != 0) {
        if (widget->labelOffset < widget->width - 1) {
            mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
        }
    }
    wrefresh(widget->win);
}


void updateWidget(Widget *widget) {
    if (!widget || !widget->win) return;
    if (widget->parentWidget && !widget->parentWidget->win) return;
    updateDimensions(widget);
    resizeWidget(widget);
}
void updateButton(Widget *widget){
    updateDimensions(widget);
}

void deleteWidgets() {
    for (int i = 0; i < widgets.len; i++) {
        delwin(widgets.widgets[i]->win);
    }
    free(widgets.widgets);
    widgets.widgets = NULL;
    widgets.len = 0;
}
Widget* findWidgetByName(char* name) {
    for (int i = 0; i < widgets.len; i++) {
        Widget* currentWidget = widgets.widgets[i]; // pointer from list
        if (strcmp(currentWidget->name, name) == 0) {
            return currentWidget;
        }
    }
    return NULL; // not found
}
void showOnScreen(char* widgetName, char* buffer){
    Widget* widget = findWidgetByName(widgetName);
    werase(widget->win);        
    box(widget->win, 0, 0);    
    mvwprintw(widget->win, 1, 1, "%s", buffer);
    wrefresh(widget->win);
}
bool clickedWidget(Widget* widget,int x, int y){
    bool isInside =
        x >= widget->x &&
        x <  widget->x + widget->width &&
        y >= widget->y &&
        y <  widget->y + widget->height;
    return isInside;
}
void handleInput(Widget* widget, char* buffer, int* index,int ch,MEVENT* event) {
    if (ch == KEY_MOUSE) {
        if (getmouse(event) == OK) {
            if (clickedWidget(widget, event->x, event->y)) {
                widget->inputActive = true;
            } else {
                widget->inputActive = false;
            }
        } else {
            widget->inputActive = false;
        }
        return;
    }
    if (!widget->inputActive) return;
    if (ch == '\n' || ch == KEY_ENTER) {
        showOnScreen("viewnotesscreen", buffer);
        werase(widget->win);       
        widget->inpCount = 0;
    }
    if (widget->inpCount==widget->width-2){
        buffer[*index] = '\n';
        (*index)++;
        buffer[*index] = ' ';
        (*index)++;
        widget->inpCount = 1;
    }
    if (ch >= 32 && ch <= 126 && *index < 255) {
        buffer[*index] = (char)ch;
        (*index)++;
        buffer[*index] = '\0';
        widget->inpCount++;
    }
    werase(widget->win);         // clear window
    box(widget->win, 0, 0);      // redraw box
    mvwprintw(widget->win, 1, 1, "%s", buffer);
    if (widget->label && strcmp(widget->label, "label") != 0) {
        if (widget->labelOffset < widget->width - 1) {
            mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
        }
    }
    wrefresh(widget->win);
}
