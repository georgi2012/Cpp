#pragma once

#define DRAW4_NUMBER 10
#define CHANGEDIR_NUMBER 11
#define CHANGECOLOR_NUMBER 12
#define UNKNOWN_NUM 0

enum COLOR
{
    unknown,
    red,
    blue,
    green,
    yellow,
};

#define RED 1
#define BLUE 2
#define GREEN 3
#define YELLOW 4

struct Card
{
    unsigned short number;
    COLOR clr;

    Card();
    Card(COLOR newClr, short num);
    //operator=
};

