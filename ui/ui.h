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
extern float propW;
extern float propH;

Widget* createInput(Widget *parent, int id, int w, int h,int x, int y, char *label, int offset,bool inputActive,int minw, int minh,int maxw, int maxh,char* name);
Widget* createInputDefault(Widget* parent, int id, int w, int h,int x, int y,bool inputActive,int minw, int minh,int maxw, int maxh,char* name);

extern Buttons buttons;

Widget* createButton(Widget* parent, int id, int x, int y, char *label, bool inputActive,char* name);

void enableInputMode(WINDOW *win,bool *inputActive);
bool isInside(WINDOW *win, int y, int x);
void handleClick(WINDOW *win,int y, int x,bool inputActive);

extern Screens screens;
void createScreen(Widget *parent, int id, int w, int h, int x, int y, char *label, bool inputActive,int minw, int minh,int maxw, int maxh,char* name);
#endif