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

    unitH = (float)parentH / propH;
    unitW = (float)parentW / propW;

    widget->units.unitH = unitH;
    widget->units.unitW = unitW;
}

void updateDimensions(Widget *widget){
    getProportionalUnits(widget);
    widget->height = widget->units.unitH*widget->h;
    widget->width = widget->units.unitW*widget->w;
    
}
void resizeWidget(Widget *widget) {
    wresize(widget->win, widget->height, widget->width);
    mvwin(widget->win, 0, 0);
    wclear(widget->win);
    box(widget->win, 0, 0);

    if (widget->label && strcmp(widget->label, "label") != 0) {
        if (widget->labelOffset < widget->width - 1) {
            mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
        }
    }
    wrefresh(widget->win);
}

void resizeButton(Widget *widget){
    wresize(widget->win, widget->height, widget->width);
    mvwin(widget->win, widget->y, widget->x);
    wclear(widget->win);
    box(widget->win, 0, 0);
    if (strcmp(widget->label, "label") != 0) {
        mvwprintw(widget->win, 2, 2, "%s", widget->label);
    }
    delwin(widget->win);
}
void updateWidget(Widget *widget) {
    if (!widget || !widget->win) return;
    if (widget->parentWidget && !widget->parentWidget->win) return;
    updateDimensions(widget);
    resizeWidget(widget);
}
void updateButton(Widget *widget){
    updateDimensions(widget);
    resizeButton(widget);
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