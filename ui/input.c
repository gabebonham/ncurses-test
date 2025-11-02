#include "./ui.h"


int inputDefaultHeight = 3;
int inputDefaultWidth = 8;
Inputs inputs = {.len=0,.widgets=NULL};

Widget createInput(Widget parent, int id, int w, int h,int x, int y, char *label, int offset,bool inputActive){
    WINDOW *input = newwin(h, w, x, y);
    Widget inputWidget = {
        .id=id,
        .win=input,
        .subWidgetsLen=0,
        .bgRGB={255,255,255},
        .borderRGB={0,0,0},
        .height=h,
        .label=label,
        .subWidgets = NULL,      // start empty
        .type=WINPUT,
        .labelOffset=offset,
        .textRGB={0,0,0},
        .width=w,
        .inputActive=inputActive,
        .x=x,
        .y=y
    };
    parent.subWidgets = addToWidgetList(&parent.subWidgets, inputWidget, parent.subWidgetsLen);
    inputs.widgets = addToWidgetList(&inputs.widgets, inputWidget, inputs.len);
    widgets.widgets = addToWidgetList(&widgets.widgets, inputWidget, widgets.len);
    parent.subWidgetsLen = parent.subWidgetsLen +1;
    inputs.len = inputs.len +1;
    widgets.len = widgets.len+1;  
    updateWidget(&inputWidget);
    return inputWidget;
}
Widget createInputDefault(Widget parent, int id, int w, int h,int x, int y,bool inputActive){
    WINDOW *input = newwin(h, w, x, y);
    Widget inputWidget = {
        .id=id,
        .win=input,
        .bgRGB={255,255,255},
        .borderRGB={0,0,0},
        .height=h,
        .label="label",
        .inputActive=inputActive,
        .subWidgets = NULL,      // start empty
        .textRGB={0,0,0},
        .labelOffset=9999,
        .type=WINPUT,
        .width=w,
        .x=x,
        .y=y
    };
    parent.subWidgets = addToWidgetList(&parent.subWidgets, inputWidget, parent.subWidgetsLen);
    inputs.widgets = addToWidgetList(&inputs.widgets, inputWidget, inputs.len);
    widgets.widgets = addToWidgetList(&widgets.widgets, inputWidget, widgets.len);
    parent.subWidgetsLen = parent.subWidgetsLen +1;
    inputs.len = inputs.len +1;
    widgets.len = widgets.len+1; 
    updateWidget(&inputWidget);
    return inputWidget;
}

