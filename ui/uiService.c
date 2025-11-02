#include "./ui.h"


void enableInputMode(WINDOW *win,bool *inputActive) {
    *inputActive = true;
    curs_set(1);
    wmove(win, 1, 1);
}
bool isInside(WINDOW *win, int y, int x) {
    int starty, startx;
    int height, width;

    getbegyx(win, starty, startx); // fine
    getmaxyx(win, height, width);  // fine

    return (y >= starty && y < starty + height &&
            x >= startx && x < startx + width);
}
void handleClick(WINDOW *win,int y, int x,bool inputActive) {
    if (isInside(win, y, x)) {
        mvprintw(LINES - 1, 0, "Clicked inside input field!");
        refresh();
        enableInputMode(win, &inputActive);
    } else {
        mvprintw(LINES - 1, 0, "Clicked outside input field. Input disabled.");
        refresh();
    }
}
