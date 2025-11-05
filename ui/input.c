#include "./ui.h"


int inputDefaultHeight = 3;
int inputDefaultWidth = 8;
Inputs inputs = {.len=0,.widgets=NULL};

Widget* createInput(Widget *parent, int id, int w, int h,int x, int y, char *label, int offset,bool inputActive,int minw, int minh,int maxw, int maxh,char* name){
    CoefRatios coefs = getCoefs(parent->h,parent->w);


    WINDOW *input = newwin(h, w, x, y);
    Widget* inputWidget = malloc(sizeof(Widget));
    *inputWidget =(Widget) {
        .id=id,
        .win=input,
        .subWidgetsLen=0,
        .bgRGB={255,255,255},
        .borderRGB={0,0,0},
        .label=label,
        .parentWidget = parent,
        .subWidgets = NULL,      // start empty
        .type=WINPUT,
        .w = w,          
        .h = h,     
        .labelOffset=offset,
        .textRGB={0,0,0},
        .height = 0,
        .width = 0,
        .inputActive=inputActive,
        .minh = minh,
        .minw = minw,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .x=x,
        .y=y
    };
    // parent->subWidgets = addToWidgetList(parent->subWidgets, inputWidget, parent->subWidgetsLen);
    // parent->subWidgetsLen++;

    // buttons.widgets = addToWidgetList(buttons.widgets, inputWidget, buttons.len++);
    widgets.widgets = addToWidgetList(widgets.widgets, &inputWidget, widgets.len++);
  
    updateWidget(&inputWidget,&inputWidget->parentWidget);
    return inputWidget;
}
Widget* createInputDefault(Widget* parent, int id, int w, int h,int x, int y,bool inputActive,int minw, int minh,int maxw, int maxh,char* name){
    CoefRatios coefs = getCoefs(parent->h,parent->w);

    WINDOW *input = newwin(h, w, x, y);
    Widget* inputWidget = malloc(sizeof(Widget));
    *inputWidget =(Widget) {
        .id=id,
        .win=input,
        .bgRGB={255,255,255},
        .borderRGB={0,0,0},
        .height=h,
        .w = w,          
        .h = h,     
        .label="label",
        .inputActive=inputActive,
        .parentWidget = parent,
        .subWidgets = NULL,      // start empty
        .textRGB={0,0,0},
        .labelOffset=9999,
        .type=WINPUT,
        .width=w,
        .minh = minh,
        .minw = minw,
        .maxh = maxh,
        .maxw = maxw,
        .name = name,
        .x=x,
        .y=y
    };
    // parent->subWidgets = addToWidgetList(parent->subWidgets, inputWidget, parent->subWidgetsLen);
    // parent->subWidgetsLen++;

    // buttons.widgets = addToWidgetList(buttons.widgets, inputWidget, buttons.len++);
    widgets.widgets =  addToWidgetList(widgets.widgets, &inputWidget, widgets.len++);
    updateWidget(&inputWidget,&inputWidget->parentWidget);
    return inputWidget;
}

