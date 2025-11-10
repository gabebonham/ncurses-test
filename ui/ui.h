#ifndef UI_H
#define UI_H
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include "./common/common.h"
#include "../utils/utils.h"
#include "../main.h"

extern Widgets widgets;

extern Inputs inputs;
extern int propW;
extern int propH;


extern Buttons buttons;


void enableInputMode(WINDOW *win,bool *inputActive);
bool isInside(WINDOW *win, int y, int x);
void handleClick(WINDOW *win,int y, int x,bool inputActive);

extern Screens screens;
void createScreenPer(Widget *parent, int id, int w, int h, int x, int y, char *label, bool inputActive,int minw, int minh,int maxw, int maxh,char* name,float wper,float hper);
void createScreen(Widget *parent, int id, int w, int h, int x, int y, char *label, bool inputActive,int minw, int minh,int maxw, int maxh,char* name);
void createButton(Widget *parent, int id, int w, int h, int x, int y, char *label, bool inputActive,int minw, int minh,int maxw, int maxh,char* name);
void createInput(Widget *parent, int id, int w, int h, int x, int y, char *label, bool inputActive,int minw, int minh,int maxw, int maxh,char* name);
#endif