#include <iostream>
#include "Cards.h"
/*
    unknown,
    red, 1
    blue, 2
    green, 3
    yellow 4
    */
Card::Card()
{
    clr = unknown;
    number = 11;
}

Card::Card(COLOR newClr, short num)
{
    if(num<0 || num>9)
    {
       number=11;
       std::cout<<"Unvalid card format.";
    }
    //if(newClr==unknown) TBD //because of the API :)

    clr = newClr;
    number = num;
}
