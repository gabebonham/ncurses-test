#include "./main.h"

Widgets widgets={.len=0,.widgets=NULL};
int terminalHeight = 0;
int terminalWidth = 0;
int propW = 0;
int propH = 0;
volatile sig_atomic_t resized = 0;


void updateWidgets(){
    for (int i = 0; i < widgets.len; i++) {
        Widget* currentWidget = widgets.widgets[i];
        if (!currentWidget) continue;
        // updateDimensions(currentWidget);
        resizeWidget(currentWidget);
    }
}
void update() {
    endwin();
    clear();
    refresh();

    getmaxyx(stdscr, terminalHeight, terminalWidth);
    
    updateWidgets();

    refresh();
}

void handle_winch() {
    update();
}
void loop() {
    Widget* notesTitle = findWidgetByName("createnotestitle");
    Widget* notesDescription = findWidgetByName("createnotesdesc");
    keypad(notesTitle->win, FALSE);
    keypad(notesDescription->win, FALSE);
    char buffer[256] = {0};
    int index = 0;
    char buffer2[256] = {0};
    int index2 = 0;
    while (1) {
        int ch = getch();
        MEVENT event;
        handleInput(notesTitle,buffer,&index,ch, &event);
        handleInput(notesDescription,buffer2,&index2,ch,&event);
    }
}

void createWidgets(){
    float cnwper = 0.7;
    float cnhper = 0.8;
    int cnw = 0;
    int cnh = 0;
    getmaxyx(stdscr, terminalHeight, terminalWidth);
    createScreenPer(NULL,widgets.len+1,30,10,0,0,"Create Notes",true,6,3,terminalWidth,terminalHeight,"createnotesscreen", cnwper,cnhper);
    Widget* createNotesScreen = findWidgetByName("createnotesscreen");

    getmaxyx(createNotesScreen->win, cnh, cnw);
    
    int inputw = 40;
    int inputh = 3;

    int descw = 40;
    int desch = 10;

    

    int descx = 1;
    int descy = createNotesScreen->height-desch-1;

    int inputx = 1;
    int inputy = createNotesScreen->height-desch-inputh-1;

    int viewnotesw = cnw-2-descw-1;
    int viewnotesh = cnh-inputh-2;

    int viewnotesx = descw+2;
    int viewnotesy = 1;
    createInput(createNotesScreen,widgets.len+1,inputw,inputh,inputx,inputy,"Title",false,3,2,0,0,"createnotestitle");
    createInput(createNotesScreen,widgets.len+1,descw,desch,descx,descy,"Description",false,3,2,0,0,"createnotesdesc");
    createScreen(createNotesScreen,widgets.len+1,viewnotesw,viewnotesh,viewnotesx,viewnotesy,"label",false,6,3,terminalWidth,terminalHeight,"viewnotesscreen");
}

void init() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);   
    curs_set(0);
    // start_color();    
    signal(SIGWINCH, handle_winch);
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
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
