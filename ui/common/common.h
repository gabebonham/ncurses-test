#ifndef COMMON_H
#define COMMON_H

#include <ncurses.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    WSCREEN,
    WBUTTON,
    WINPUT
} WidgetType;

typedef struct Widget Widget;
typedef struct {float unitH;float unitW;} Units;

struct Widget {
    WINDOW *win;
    WidgetType type;
    Widget **subWidgets;   // flexible array
    int subWidgetsLen;
    int id;
    Units units;
    Widget* parentWidget;
    float width;
    float height;
    int w;
    int h;
    int labelOffset;
    int x;
    int y;
    int minw;
    int minh;
    int maxw;
    int maxh;
    bool inputActive;
    char *label;
    char *name;
    int borderRGB[3];
    int bgRGB[3];
    int textRGB[3];
};

typedef struct {
    int len;
    Widget *widgets;
} Inputs;

typedef struct {
    int len;
    Widget *widgets;
} Buttons;

typedef struct {
    int len;
    Widget *widgets;
} Screens;
typedef struct {
    int len;
    Widget** widgets;
} Widgets;

#endif
