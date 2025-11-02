#ifndef UTILS_H
#define UTILS_H
#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include "../ui/common/common.h"
#include "../ui/ui.h"
#include "../main.h"

Widget* resizeWidgetArray(Widget *sourceArray, int currentSize, int newSize);
int getStringWidth(const char *str);

void updateButton(Widget *widget);
void updateWidget(Widget *widget);
void deleteWidgets();
Widget* addToWidgetList(Widget **array, Widget newWidget, int currentSize);

#endif