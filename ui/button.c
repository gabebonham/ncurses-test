#include "./ui.h"


int buttonDefaultHeight = 3;
int buttonDefaultWidth = 8;
Buttons buttons = {.len=0,.widgets=NULL};
Widget createButton(Widget parent, int id, int w, int h, int x, int y, char *label, bool inputActive) {
    WINDOW *button = newwin(h, w, x, y);

    Widget buttonWidget = {
        .id = id,
        .subWidgetsLen = 0,
        .win = button,           // use pointer directly
        .bgRGB = {255,255,255},
        .borderRGB = {0,0,0},
        .textRGB = {0,0,0},
        .height = h,
        .width = w,
        .label = label,          // assign pointer
        .labelOffset = 9999,
        .subWidgets = NULL,      // start empty
        .type = WBUTTON,         // correct enum
        .inputActive = inputActive,
        .x = x,
        .y = y
    };

    parent.subWidgets = addToWidgetList(&parent.subWidgets, buttonWidget, parent.subWidgetsLen);
    buttons.widgets = addToWidgetList(&buttons.widgets, buttonWidget, buttons.len);
    widgets.widgets = addToWidgetList(&widgets.widgets, buttonWidget, widgets.len);
    parent.subWidgetsLen = parent.subWidgetsLen +1;
    buttons.len = buttons.len +1;
    widgets.len = widgets.len   +1;   
    updateWidget(&buttonWidget);
    return buttonWidget;
}
