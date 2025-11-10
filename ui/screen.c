#include "./ui.h"

Screens screens = { .len = 0, .widgets = NULL };

void createScreenPer(
    Widget *parent, int id, int w, int h, int x, int y, 
    char *label, bool inputActive,
    int minw, int minh, int maxw, int maxh, char *name,float wper,float hper
) {
    int parentH = 0, parentW = 0;

    if (!parent) {
        getmaxyx(stdscr, parentH, parentW);
    } else if (parent->win) {
        getmaxyx(parent->win, parentH, parentW);
    } else {
        return;
    }

    Widget* screenWidget = malloc(sizeof(Widget));
    if (!screenWidget) return;

    // Compute proportional units
    float unitH = (float)parentH / propH;
    float unitW = (float)parentW / propW;

    // Now safely compute height/width
    // float height = unitH * h;
    // float width  = unitW * w;
    float height = hper*parentH;    
    float width = wper*parentW;    
    // float xPos  = x==0?0:unitW * x;
    // float yPos  = y==0?0:unitH * y;
    int xPos = x;
    int yPos = y;
    WINDOW *screen = subwin(
        parent?(parent->win ? parent->win : stdscr):stdscr,
        (int)height,
        (int)width,
        (int)y,
        (int)x
    );
    *screenWidget = (Widget){
        .id = id,
        .win = screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .parentWidget = parent,  
        .height = hper*parentH,
        .width  = wper*parentW,
        .units = { .unitH = unitH, .unitW = unitW },
        .w = w,
        .h = h,
        .label = label,
        .labelOffset = 1,
        .type = WSCREEN,
        .inputActive = inputActive,
        .textRGB = {0, 0, 0},
        .minh = 6,
        .minw = 8,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .xPos = xPos,
        .x = x,
        .y = y,
        .yPos = yPos
    };

    widgets.widgets = addToWidgetList(widgets.widgets, &screenWidget, widgets.len++);
}

void createScreen(
    Widget *parent, int id, int w, int h, int x, int y, 
    char *label, bool inputActive,
    int minw, int minh, int maxw, int maxh, char *name
) {
    int parentH = 0, parentW = 0;

    if (!parent) {
        getmaxyx(stdscr, parentH, parentW);
    } else if (parent->win) {
        getmaxyx(parent->win, parentH, parentW);
    } else {
        return;
    }

    Widget* screenWidget = malloc(sizeof(Widget));
    if (!screenWidget) return;

    // Compute proportional units
    float unitH = (float)parentH / propH;
    float unitW = (float)parentW / propW;

    // Now safely compute height/width
    // float height = unitH * h;
    // float width  = unitW * w;
    float height = h;    
    float width = w;    
    // float xPos  = x==0?0:unitW * x;
    // float yPos  = y==0?0:unitH * y;
    int xPos = x;
    int yPos = y;
    WINDOW *screen = subwin(
        parent?(parent->win ? parent->win : stdscr):stdscr,
        (int)height,
        (int)width,
        (int)y,
        (int)x
    );
    *screenWidget = (Widget){
        .id = id,
        .win = screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .parentWidget = parent,  
        .height = h,
        .width  = w,
        .units = { .unitH = unitH, .unitW = unitW },
        .w = w,
        .h = h,
        .label = label,
        .labelOffset = 1,
        .type = WSCREEN,
        .inputActive = inputActive,
        .textRGB = {0, 0, 0},
        .minh = 6,
        .minw = 8,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .xPos = xPos,
        .x = x,
        .y = y,
        .yPos = yPos
    };

    widgets.widgets = addToWidgetList(widgets.widgets, &screenWidget, widgets.len++);
}
