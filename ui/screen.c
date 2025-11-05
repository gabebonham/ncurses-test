#include "./ui.h"

Screens screens = { .len = 0, .widgets = NULL };

Widget* createScreen(WINDOW *screen,Widget *parent, int id, int w, int h, int x, int y, 
                    char *label, int offset, bool inputActive,
                    int minw, int minh, int maxw, int maxh, char *name) {

    int wunit = wRatio;
    int hunit = hRatio;

    int parentH = 0, parentW = 0;
    if (parent->win==stdscr){
        getmaxyx(stdscr, parentH, parentW);
    }
    getmaxyx(parent->win, parentH, parentW);


    Widget* screenWidget = malloc(sizeof(Widget));
    *screenWidget = (Widget){
        .id = id,
        .win = screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .parentWidget = parent,  
        .height = ruleOfThree(parentH, 4, 10),
        .width  = ruleOfThree(parentW, 14, 24),
        .w = w,
        .h = h,
        .label = label,
        .labelOffset = offset,
        .type = WSCREEN,
        .inputActive = inputActive,
        .textRGB = {0, 0, 0},
        .minh = minh,
        .minw = minw,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .x = x,
        .y = y
    };

    // parent->subWidgets = addToWidgetList(parent->subWidgets, screenWidget, parent->subWidgetsLen);
    // parent->subWidgetsLen++;

    // screens.widgets = addToWidgetList(screens.widgets, screenWidget, screens.len++);
    widgets.widgets = addToWidgetList(widgets.widgets, &screenWidget, widgets.len++);

    updateWidget(&screenWidget,&screenWidget->parentWidget);
    return screenWidget;
}
