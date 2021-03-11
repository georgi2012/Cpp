#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

#include <conio.h>
#include <stdio.h>
//#include <windows.h>
#include <iostream>

using namespace std;

const int MAX_POSITION=8;
const int MAX_LINES=7;
const char SHIP_ICON='@';

void printMap(char** map)
{
   for (int i=0;i<MAX_POSITION;i++)
   {
       cout<<"|"<<map[i]<<"|"<<endl;
   }
   for (int i=0;i<MAX_LINES+2;i++)
   {
       cout<<"-";
   }
   cout<<endl;
    return;
}

void updateMap(int & position ,  int &linesInFront, char** map)
{
    //system("cls");
        for (int i=0;i<linesInFront;i++)
        {
            cout<<"|";
            for (int j=0;j<=MAX_POSITION;j++)
            {
                cout<<" ";
            }
            cout<<"|";
            cout<<endl;
        }
        //cout<<"|"<<ship<<"|"<<endl;
        for(int i=0;i<MAX_LINES-linesInFront;i++)
        {
             cout<<"|";
            for (int j=0;j<=MAX_POSITION;j++)
            {
                cout<<" ";
            }
            cout<<"|";
            cout<<endl;
        }
        for(int i=0;i<2;i++)
        {
             cout<<"|";
            for (int j=0;j<=MAX_POSITION;j++)
            {
                cout<<"-";
            }
            cout<<"|";
            cout<<endl;
        }

}

void moveDown(int & position, int &linesInFront, char** map){
  if(position<MAX_POSITION)
  {
     map[position+1][linesInFront]=SHIP_ICON;
     map[position++][linesInFront]=' ';
  }
  return;

}

void moveUp(int & position,int &linesInFront, char **map){
 if(position>0)
  {
      map[position-1][linesInFront]=SHIP_ICON;
     map[position--][linesInFront]=' ';
  }
  return;
}

void moveLeft(int & position,int &linesInFront,char** map)
{
   if(linesInFront>0)
   {
      
        map[position][linesInFront-1]=SHIP_ICON;
        map[position][linesInFront--]=' ';
   }
   return;
}

void moveRight(int & position,int &linesInFront, char** map)
{
   if(linesInFront<MAX_LINES)
   {
       map[position][linesInFront+1]=SHIP_ICON;
        map[position][linesInFront++]=' ';
   }
   return;
}

int main()
{
    //char *ship=new char[9]{' ',' ',' ',' ','+',' ',' ',' ',' '};
    char** map= new char*[MAX_POSITION];
    for(int i=0;i<MAX_POSITION;i++)
    {
        map[i]=new char[MAX_LINES];
        for (int j=0;j<MAX_LINES;j++)
        {
            map[i][j]=' '; 
        }
    }
    int position=4;
    int linesInFront=5;
    map[position][linesInFront]=SHIP_ICON;//ship

    int c = 0;

    while ( c!= 27 )    //esc key code is 27
    {
        system("cls");
        //updateMap(position,linesInFront,map);
        printMap(map);

        //if (kbhit()) {
            c = getch();
            switch ( c ) 
                {
                case KEY_UP:
                   moveUp(position,linesInFront,map);//key up
                    break;
                case KEY_DOWN:
                    moveDown(position,linesInFront,map);  // key down
                    break;
                case KEY_LEFT:
                      moveLeft(position,linesInFront,map);
                    break;
                case KEY_RIGHT:
                    moveRight(position,linesInFront,map);  // key right
                    break;

                }//switch
       // }//if
    }//while

    for(int i=0;i<MAX_LINES;i++)
    {
        delete[] map[i];
    }
    delete[] map;
    return 0;
}