#include "./ui.h"

Screens screens ={.len=0,.widgets=NULL};
Widget createScreen(Widget parent, int id, int w, int h, int x, int y, char *label, int offset, bool inputActive) {
    WINDOW *screen = newwin(h, w, x, y);
    
    Widget screenWidget = {
        .id = id,
        .win = screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .height = h,
        .width = w,
        .label = label,
        .labelOffset = offset,
        .type = WSCREEN,
        .inputActive = inputActive,
        .textRGB={0,0,0},
        .x = x,
        .y = y
    };

    parent.subWidgets = addToWidgetList(&parent.subWidgets, screenWidget, parent.subWidgetsLen);
    screens.widgets = addToWidgetList(&screens.widgets, screenWidget, screens.len);
    widgets.widgets = addToWidgetList(&widgets.widgets, screenWidget, widgets.len);
    parent.subWidgetsLen = parent.subWidgetsLen + 1;
    screens.len = screens.len + 1;
    widgets.len = widgets.len + 1;
    updateWidget(&screenWidget);
    return screenWidget;

}
