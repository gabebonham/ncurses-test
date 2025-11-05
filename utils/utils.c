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
// from left top to right bottom
int ruleOfThree(int tr, int bl,int br){
    int right = tr/br;
    return bl*right;
}
CoefRatios getCoefs(int parentH,int parentW){
    int hcoef = parentH/10;
    int wcoef = parentW/24;
    CoefRatios ratios = {.wcoef=wcoef,.hcoef=hcoef};
    return ratios;
}

// void updateDimensions(Widget *widget, Widget *parent) {
    // if (!widget || !parent) {
    //     fprintf(stderr, "updateDimensions: invalid widget or parent\n");
    //     return;
    // }

    // // Get parent size (logical or ncurses)
    // int parentH, parentW;
    // if (parent->win == stdscr) {
    //     getmaxyx(stdscr, parentH, parentW);
    // } else if (parent->win) {
    //     getmaxyx(parent->win, parentH, parentW);
    // } else {
    //     // Fallback: use stored parent->width/height if no window yet
    //     parentH = parent->height;
    //     parentW = parent->width;
    // }

    // // Always update the parent size fields
    // parent->width = parentW;
    // parent->height = parentH;

    // // --- proportional scaling ---
    // // widget->w_ratio = 0.8 -> 80% of parent width
    // // widget->h_ratio = 0.6 -> 60% of parent height
    //  w_ratio = 0.583 > 0 ? 0.6 : 1.0f;
    //  h_ratio = 0.583 > 0 ? 0.6 : 1.0f;
    // int newWidth = (int)(parentW * w_ratio);
    // int newHeight = (int)(parentH * h_ratio);

    // // Clamp to min/max if you have them
    // if (widget->minw && newWidth < widget->minw) newWidth = widget->minw;
    // if (widget->maxw && newWidth > widget->maxw) newWidth = widget->maxw;
    // if (widget->minh && newHeight < widget->minh) newHeight = widget->minh;
    // if (widget->maxh && newHeight > widget->maxh) newHeight = widget->maxh;

    // // Only update if changed
    // if (widget->width != newWidth || widget->height != newHeight) {
        

    //     // If using ncurses windows, resize the actual window too
    //     if (widget->win) {
    //         wresize(widget->win, newHeight, newWidth);
    //     }

    //     // Optional debug info
    //     fprintf(stderr,
    //         "updateDimensions: parent (%dx%d) -> child (%dx%d) [ratios: %.2f, %.2f]\n",
    //         parentW, parentH, newWidth, newHeight, w_ratio, h_ratio);
    // }
// }
void updateDimensions(Widget *widget, Widget *parent){
     if (!widget) {
        // fprintf(stderr, "updateDimensions: invalid widget or parent\n");
        return;
    }
    mvwprintw(widget->win, 0, 0, "%d", widget->height);
    widget->height = terminalHeight * 0.9;
    widget->width  = terminalWidth * 0,9; 
    
    // wresize() first	Changes internal ncurses buffers safely
    // mvwin() second	Moves window without invalidating buffer
    // wclear() next	Clears new size area (not old one)
    // box() + mvwprintw()	Draw your decorations
    // wrefresh() last	Push final result to display
    wresize(widget->win, widget->height, widget->width);
    mvwin(widget->win, 0, 0);
    wclear(widget->win);
    box(widget->win, 0, 0);
    if (strcmp(widget->label, "label") != 0) {
        mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
    }

    wrefresh(widget->win);
}

void resizeWidget(Widget *widget) {
    if (!widget || !widget->win) return;

    // Move first (helps avoid clipping when shrinking)
    mvwin(widget->win, widget->y, widget->x);

    // Resize to new dimensions
    wresize(widget->win, widget->height, widget->width);

    // Clear contents efficiently (does not reset attributes)
    werase(widget->win);

    // Draw border
    box(widget->win, 0, 0);

    // Draw label if applicable
    if (widget->label && strcmp(widget->label, "label") != 0) {
        if (widget->labelOffset < widget->width - 1) {
            mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
        }
    }

    // Redraw the widget window only
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
void updateWidget(Widget **widget,Widget **parent){
    
    
    updateDimensions(*widget,*parent);
    // resizeWidget(*widget);
}
void updateButton(Widget *widget,Widget *parent){
    updateDimensions(widget,parent);
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