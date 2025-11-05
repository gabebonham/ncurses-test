#include "./main.h"

Widgets widgets={.len=0,.widgets=NULL};
int terminalHeight = 0;
int terminalWidth = 0;
float propW = 0;
float propH = 0;
volatile sig_atomic_t resized = 0;


void updateWidgets(){
    for (int i = 0; i < widgets.len; i++) {
        Widget* currentWidget = widgets.widgets[i];
        if (!currentWidget) continue;
        if (currentWidget->type == WSCREEN) updateWidget(currentWidget);
    }
}
void update() {
    endwin();
    clear();
    refresh();

    
    updateWidgets();

    
    refresh();
}

void handle_winch() {
    resized = 1;
}



void loop() {
    while (1) {

        
        if (resized) {
            resized = 0;
            update();
        }
        napms(50);
    }
}
void createWidgets(){
    getmaxyx(stdscr, terminalHeight, terminalWidth);
    createScreen(NULL,widgets.len+1,14,4,0,0,"Create Notes",true,6,3,terminalWidth,terminalHeight,"createnotesscreen");
}

void init() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    signal(SIGWINCH, handle_winch);
    propW = 24;
    propH = 14;
    
}

int main() {
    init();
    createWidgets();
    loop();
    deleteWidgets();
    endwin();
    return 0;
}
