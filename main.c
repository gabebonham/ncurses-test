#include "./main.h"

Widgets widgets={.len=0,.widgets=NULL};
int terminalHeight = 0;
int terminalWidth = 0;
int wRatio = 24;
int hRatio = 10;
volatile sig_atomic_t resized = 0;


void updateWidgets(){
    for (int i = 0; i < widgets.len; i++) {
        Widget* currentWidget = widgets.widgets[i];
        if (!currentWidget) continue;

        // if (currentWidget->type == WBUTTON) updateButton(currentWidget,currentWidget->parentWidget);
        if (currentWidget->type == WSCREEN) {
            Widget* widget = currentWidget;
            if (!widget) {
        // fprintf(stderr, "updateDimensions: invalid widget or parent\n");
                return;
            }
            getmaxyx(stdscr, terminalHeight, terminalWidth); 
            widget->height = LINES * 0.9;
            widget->width  = COLS * 0.6; 
            
            // wresize() first	Changes internal ncurses buffers safely
            // mvwin() second	Moves window without invalidating buffer
            // wclear() next	Clears new size area (not old one)
            // box() + mvwprintw()	Draw your decorations
            // wrefresh() last	Push final result to display
            wresize(widget->win, widget->height, widget->width);
            mvwin(widget->win, 0, 0);
            wclear(widget->win);
            box(widget->win, 0, 0);
            // if (strcmp(widget->label, "label") != 0) {
            //     mvwprintw(widget->win, 0, widget->labelOffset, "%s", widget->label);
            // }

            wrefresh(widget->win);
        }
    }
}

void update() {
    

    // Update main widget

    // Clear screen and refresh
    // endwin();
    clear();
    refresh();
    updateWidgets();

    refresh();
    endwin();
    // Update all child widgets
}

void handle_winch() {
    resized = 1;
}



void loop() {
    while (1) {

        
        refresh();
        if (resized) {
            resized = 0;
            update();
        }
        napms(50);
    }
}
void createWidgets(){
    getmaxyx(stdscr, terminalHeight, terminalWidth); 
    
    CoefRatios coefs = getCoefs(terminalHeight, terminalWidth);
    WINDOW *screenn = subwin(stdscr,10*coefs.hcoef,14*coefs.wcoef, 0, 0);
    WINDOW **screen = &screenn;
    
    Widget* screenWidget = malloc(sizeof(Widget));
    *screenWidget = (Widget){
        .id = 5,
        .win = *screen,
        .bgRGB = {255, 255, 255},
        .borderRGB = {0, 0, 0},
        .subWidgets = NULL,
        .subWidgetsLen = 0,
        .parentWidget = NULL,  
        .height = LINES/10*3,
        .width  = COLS/24*6,
        .w = 14,
        .h = 4,
        .label = "Create Notes",
        .labelOffset = 0,
        .type = WSCREEN,
        .inputActive = true,
        .textRGB = {0, 0, 0},
        .minh = 0,
        .minw = 0,
        .maxh = 0,
        .maxw = 0,
        .name = "createnotesscreen",
        .x = 0,
        .y = 0
    };

    // parent->subWidgets = addToWidgetList(parent->subWidgets, screenWidget, parent->subWidgetsLen);
    // parent->subWidgetsLen++;

    // screens.widgets = addToWidgetList(screens.widgets, screenWidget, screens.len++);
    widgets.len++;
    widgets.widgets = realloc(widgets.widgets, widgets.len * sizeof(Widget*));
    widgets.widgets[widgets.len-1] = screenWidget;
    
    
    
    
    
    // createScreen(screen,terminalWidget,widgets.len,14,4,0,0,"Create Notes",3,true,6,3,terminalWidth,terminalHeight,"createnotesscreen");
    // Widget *createWidget = findWidgetByName("createnotesscreen");
    // createButton(createWidget,widgets.len,createWidget->x+2,createWidget->y+2,"button",true,"testbutton");
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

    loop();
    deleteWidgets();
    endwin();
    return 0;
}
