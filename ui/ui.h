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
extern int inputDefaultHeight;
extern int inputDefaultWidth;

Widget createInput(Widget parent, int id, int w, int h,int x, int y, char *label, int offset,bool inputActive);
Widget createInputDefault(Widget parent, int id, int w, int h,int x, int y,bool inputActive);

extern Buttons buttons;
extern int buttonDefaultHeight;
extern int buttonDefaultWidth;

Widget createButton(Widget parent, int id, int w, int h, int x, int y, char *label, bool inputActive);

void enableInputMode(WINDOW *win,bool *inputActive);
bool isInside(WINDOW *win, int y, int x);
void handleClick(WINDOW *win,int y, int x,bool inputActive);

extern Screens screens;
Widget createScreen(Widget parent, int id, int w, int h,int x, int y, char *label, int offset,bool inputActive);
#endif