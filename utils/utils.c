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
Widget* resizeWidgetArray(Widget *sourceArray, int currentSize, int newSize) {
    Widget *array = malloc(newSize * sizeof(Widget));
    if (!array) return sourceArray; 

    if (sourceArray != NULL) {
        for (int i = 0; i < currentSize; i++) {
            array[i] = sourceArray[i];
        }
        free(sourceArray); 
    }

    for (int i = currentSize; i < newSize; i++) {
        array[i] = (Widget){0};
    }

    return array;
}

Widget* addToWidgetList(Widget **array, Widget newWidget, int currentSize) {
    int newSize = currentSize + 1;
    Widget *newList = resizeWidgetArray(*array,currentSize, newSize);
    newList[newSize-1] = newWidget;
    return newList;
}

void updateWidget(Widget *widget){
    widget->height = terminalHeight / 2;
    widget->width  = terminalWidth / 3; 
    
    if (widget->height < 1) widget->height = 1;
    if (widget->width < 1) widget->width = 1;
    // wresize() first	Changes internal ncurses buffers safely
    // mvwin() second	Moves window without invalidating buffer
    // wclear() next	Clears new size area (not old one)
    // box() + mvwprintw()	Draw your decorations
    // wrefresh() last	Push final result to display
    wresize(widget->win, widget->height, widget->width);
    mvwin(widget->win, widget->y, widget->x);
    wclear(widget->win);
    box(widget->win, 0, 0);
    if (strcmp(widget->label, "label") != 0) {
        mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
    }

    wrefresh(widget->win);
}
void updateButton(Widget *widget){
    
    if (widget->height < 1) widget->height = 1;
    int labelWidth = getStringWidth(widget->label);
    if (widget->width < labelWidth)
        widget->width = labelWidth;
    // wresize() first	Changes internal ncurses buffers safely
    // mvwin() second	Moves window without invalidating buffer
    // wclear() next	Clears new size area (not old one)
    // box() + mvwprintw()	Draw your decorations
    // wrefresh() last	Push final result to display
    wresize(widget->win, widget->height, widget->width);
    mvwin(widget->win, widget->y, widget->x);
    wclear(widget->win);
    box(widget->win, 0, 0);
    int startX = (widget->width - labelWidth) / 2;
    int startY = widget->height / 2; // for single-line text
    mvwprintw(widget->win, startY, startX, "%s", widget->label);

    wrefresh(widget->win);
}

void deleteWidgets() {
    for (int i = 0; i < widgets.len; i++) {
        delwin(widgets.widgets[i].win);
    }
    free(widgets.widgets);
    widgets.widgets = NULL;
    widgets.len = 0;
}