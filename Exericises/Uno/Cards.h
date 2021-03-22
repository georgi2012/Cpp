#pragma once

enum COLOR
{
    unknown,
    red,
    blue,
    green,
    yellow
};

struct Card
{
    unsigned short number;
    COLOR clr;

    Card();
    Card(COLOR newClr, short num);
    //operator=
};

