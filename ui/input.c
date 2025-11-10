#include "./ui.h"


int inputDefaultHeight = 3;
int inputDefaultWidth = 8;
Inputs inputs = {.len=0,.widgets=NULL};


void createInput(
    Widget *parent, int id, int w, int h, int x, int y, 
    char *label, bool inputActive,
    int minw, int minh, int maxw, int maxh, char *name
) {
    int parentH = 0, parentW = 0;

    getmaxyx(parent->win, parentH, parentW);


    Widget* screenInput = malloc(sizeof(Widget));
    if (!screenInput) return;

    // Compute proportional units
    float unitH = (float)parentH / propH;
    float unitW = (float)parentW / propW;

    // Now safely compute height/width
    // float height = unitH * h;
    // float width  = unitW * w;
    int height = h;    
    int width = w;    
    // float xPos = x == 0 ? 0 : unitW * x;
    // float yPos = y == 0 ? 0 : unitH * y;
    int xPos = x;
    int yPos = y;
    WINDOW *screen = subwin(
        parent?(parent->win ? parent->win : stdscr):stdscr,
        (int)height,
        (int)width,
        (int)y,
        (int)x
    );

    *screenInput = (Widget){
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
        .inpCount = 0,
        .label = label,
        .labelOffset = 1,
        .type = WINPUT,
        .inputActive = inputActive,
        .textRGB = {0, 0, 0},
        .minh = 4,
        .minw = 12,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .xPos = xPos,
        .x = x,
        .y = y,
        .yPos = yPos
    };

    widgets.widgets = addToWidgetList(widgets.widgets, &screenInput, widgets.len++);
}

