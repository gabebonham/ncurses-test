#include "./ui.h"


int buttonDefaultHeight = 3;
int buttonDefaultWidth = 8;
Buttons buttons = {.len=0,.widgets=NULL};
Widget* createButton(Widget* parent, int id, int x, int y, char *label, bool inputActive,char* name) {
    // CoefRatios coefs = getCoefs(parent->h,parent->w);
    // int w = getStringWidth(label)+3;
    // int h = 4;
    // WINDOW *button = newwin(h, w, x, y);
    // Widget* buttonWidget = malloc(sizeof(Widget));
    // *buttonWidget = (Widget){
    //     .id = id,
    //     .subWidgetsLen = 0,
    //     .win = button,           // use pointer directly
    //     .w = 6,          
    //     .h = 3,   
    //     .bgRGB = {255,255,255},
    //     .borderRGB = {0,0,0},
    //     .textRGB = {0,0,0},
    //     .parentWidget = parent,
    //     .height = 0,
    //     .width = 0,
    //     .label = label,          // assign pointer
    //     .labelOffset = 9999,
    //     .subWidgets = NULL,      // start empty
    //     .type = WBUTTON,         // correct enum
    //     .inputActive = inputActive,
    //     .x = x,
    //     .minh = 2,
    //     .minw = getStringWidth(label)+1,
    //     .maxh = h+1,
    //     .maxw = w+1,
    //     .name = name,
    //     .y = y
    // };

    // // parent->subWidgets = addToWidgetList(parent->subWidgets, buttonWidget, parent->subWidgetsLen);
    // // parent->subWidgetsLen++;

    // // buttons.widgets = addToWidgetList(buttons.widgets, buttonWidget, buttons.len++);
    // widgets.widgets = addToWidgetList(widgets.widgets, &buttonWidget, widgets.len++);
 
    // updateWidget(&buttonWidget,&buttonWidget->parentWidget);
    return NULL;
}
