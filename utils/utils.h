#ifndef UTILS_H
#define UTILS_H
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include "../ui/common/common.h"
#include "../ui/ui.h"
#include "../main.h"

Widget** resizeWidgetArray(Widget **sourceArray, int currentSize, int newSize);

int getStringWidth(const char *str);

void updateButton(Widget *widget,Widget *parent);
void updateWidget(Widget **widget,Widget **parent);
void deleteWidgets();
Widget** addToWidgetList(Widget **array, Widget **newWidget, int currentSize);

int ruleOfThree(int tr, int bl,int br);
void updateDimensions(Widget *widget,Widget *parent);
void resizeWidget(Widget *widget);

void resizeButton(Widget *widget);
CoefRatios getCoefs(int parentH,int parentW);

Widget* findWidgetByName(char* name);
#endif