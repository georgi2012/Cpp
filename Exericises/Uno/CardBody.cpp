#include <iostream>
#include "Cards.h"
/*
    unknown,
    red, 1
    blue, 2
    green, 3
    yellow 4
    */
Card::Card():clr(unknown),number(UNKNOWN_NUM) 
{
}

Card::Card(COLOR newClr, short num) //currently unusable
{
    if(num<0 || num>12)
    {
       number=UNKNOWN_NUM;
       std::cout<<"Unvalid card format.";
    }
    //if(newClr==unknown) TBD //because of the API :)

    clr = newClr;
    number = num;
}
