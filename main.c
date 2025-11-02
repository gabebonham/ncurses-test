#include "./main.h"

Widgets widgets={.len=0,.widgets=NULL};
int terminalHeight = 0;
int terminalWidth = 0;
volatile sig_atomic_t resized = 0;


void updateWidgets(){
    for (int i = 1; i< widgets.len;i++){
        Widget currentWidget = widgets.widgets[i];
        if (currentWidget.type==WBUTTON){
            updateButton(&currentWidget);
        }
        if (currentWidget.type==WSCREEN){
            updateWidget(&currentWidget);
        }
    }
}

void update() {
    // The terminal size or state might have changed — reset internal buffers and prepare for reinitialization
    endwin();
    getmaxyx(stdscr, terminalHeight, terminalWidth); // get current size
    clear();                                         // clear stdscr
    refresh();                                       // draw base
    updateWidgets();                                 // update all windows
}
void handle_winch(int sig) {
    resized = 1;
}



void loop() {
    while (1) {
        if (resized) {
            resized = 0;
            update();
        }
        // handle input etc.
        napms(50);
    }
}
void createWidgets(){
    getmaxyx(stdscr, terminalHeight, terminalWidth); 
    Widget terminal = {
        .id=0,
        .win=stdscr,
        .bgRGB={255,255,255},
        .subWidgetsLen=0,
        .borderRGB={0,0,0},
        .height=terminalHeight,
        .label="label",
        .subWidgets=NULL,
        .type=WSCREEN,
        .width=terminalWidth,
        .labelOffset=0,
        .inputActive=true,
        .x=0,
        .y=0,
        .textRGB={0,0,0}
    };
    
    widgets.widgets = addToWidgetList(&widgets.widgets, terminal, widgets.len);
    widgets.len = widgets.len+1;
    screens.widgets = addToWidgetList(&screens.widgets, terminal, screens.len);
    screens.len = screens.len+1;
    createScreen(terminal,widgets.len,COLS/3,LINES/2,0,0,"Create Notes",3,true);
    createButton(widgets.widgets[1],widgets.len,8,3,widgets.widgets[1].x+2,widgets.widgets[1].height-4,"button",true);
}

void init() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    signal(SIGWINCH, handle_winch);
}


int main() {
    init();
    createWidgets();
    update();
    loop();
    deleteWidgets();
    endwin();
    return 0;
}
