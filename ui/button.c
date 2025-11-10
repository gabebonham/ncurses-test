#include "./ui.h"


int buttonDefaultHeight = 3;
int buttonDefaultWidth = 8;
Buttons buttons = {.len=0,.widgets=NULL};

void createButton(
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

    Widget* screenButton = malloc(sizeof(Widget));
    if (!screenButton) return;

    // Compute proportional units
    float unitH = (float)parentH / propH;
    float unitW = (float)parentW / propW;

    // Now safely compute height/width
    float height = unitH * h;
    float width  = unitW * w;
    float xPos  = x==0?0:unitW * x;
    float yPos  = y==0?0:unitH * y;
    WINDOW *screen = subwin(
        parent?(parent->win ? parent->win : stdscr):stdscr,
        (int)height,
        (int)width,
        (int)y,
        (int)x
    );

    *screenButton = (Widget){
        .id = id,
        .win = screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .parentWidget = parent,  
        .height = height,
        .width  = width,
        .units = { .unitH = unitH, .unitW = unitW },
        .w = w,
        .h = h,
        .label = label,
        .labelOffset = 1,
        .type = WBUTTON,
        .inputActive = inputActive,
        .textRGB = {0, 0, 0},
        .minh = minh,
        .minw = minw,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .xPos = xPos,
        .x = x,
        .y = y,
        .yPos = yPos
    };

    widgets.widgets = addToWidgetList(widgets.widgets, &screenButton, widgets.len++);
}
