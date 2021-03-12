#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
 
#include <conio.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h> 
//too many includes already ;(

//using namespace std;

using std::thread;
using std::cout;
using std::endl;

const int MAX_POSITION=9;
const int MAX_LINES=9;
const char SHIP_ICON='@';
const char WALL_ICON='#';

int points=0;
int interval=1000;
int position=4;
int linesInFront=4;

//prototypes
void printMap(char** map);
void updateMapWalls(int* walls, char** map);
//

void gameOver()
{
  points--;
}

void addNewWall(int * walls)
{  
    srand (time(NULL));
    int newWall;
    do{ 
        newWall= rand() % (MAX_LINES-1); //find a column with no walls on it currently
        
    }while(walls[newWall]>=0);
    walls[newWall]=0;
    //cout<<"Added on "<<newWall;
    return;
    
}

void timerStart(char** map,int* walls) //should be called every interval of time
{
    std::thread([map,walls]() {
        while (true)
        {
         // printMap(map);
           updateMapWalls(walls,map);
           printMap(map);
           std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

void printMap(char** map)
{
   system("CLS");
   cout<<endl;
   for (int i=0;i<MAX_POSITION;i++)
   {
       cout<<"|";//<<map[i]<<"|"<<endl; -> buggy for some reason
       for(int j=0;j<MAX_LINES;j++)
       {
           cout<<map[i][j]; //works perfect , probably slower than the upper solution
       }
       cout<<"|"<<endl;
   }
   for (int i=0;i<MAX_LINES+2;i++)
   {
       cout<<"-";
   }
   cout<<endl;
   cout<<"Points: "<<points<<endl;
    return;
}

void updateMapWalls(int* walls, char** map) //wall cell is the column and it's value is the row
{
   for(int i=0;i<MAX_LINES;i++)
   {
       if(walls[i]>=0) //there is a wall
       {
           if(walls[i]>=MAX_POSITION-1) //out of the window. Destroyed
           {//cout<<"removed ";
              map[walls[i]][i]=' ';
              walls[i]=-1;
              addNewWall(walls);
              continue;
           }
           //if(map[walls[i]][i]==SHIP_ICON) //does not work well
           if(walls[i]+1==position && i==linesInFront) //hit
           {
             // map[walls[i]][i]=SHIP_ICON;
              walls[i]=-1;
              addNewWall(walls);
              gameOver();
            // return;
            continue;
           }
           //else move it
           map[walls[i]][i]=' ';
           walls[i]++;
           map[walls[i]][i]=WALL_ICON;
       }
   }
  return;
}

void moveDown(int & position, int &linesInFront, char** map,int* walls){
  if(position<MAX_POSITION-1)
  {
      if(position+1==walls[linesInFront] ) //its a wall
      {
        gameOver();
        walls[linesInFront]=-1;
        addNewWall(walls);
      }
     map[position+1][linesInFront]=SHIP_ICON;
     map[position++][linesInFront]=' ';
  }
  return;

}

void moveUp(int & position, int &linesInFront, char** map,int* walls){
 if(position>0)
  {
      if(position-1==walls[linesInFront] ) //its a wall
      {
        gameOver();
        walls[linesInFront]=-1;
        addNewWall(walls);
      }
      map[position-1][linesInFront]=SHIP_ICON;
     map[position--][linesInFront]=' ';
  }
  return;
}

void moveLeft(int & position, int &linesInFront, char** map,int* walls)
{
   if(linesInFront>0)
   {
      if(walls[linesInFront-1]==position ) //its a wall
      {
        gameOver();
        walls[linesInFront-1]=-1;
        addNewWall(walls);
      }
        map[position][linesInFront-1]=SHIP_ICON;
        map[position][linesInFront--]=' ';
   }
   return;
}

void moveRight(int & position, int &linesInFront, char** map,int* walls)
{
   if(linesInFront<MAX_LINES-1)
   {
        if(walls[linesInFront+1]==position ) //its a wall
      {
        gameOver();
        walls[linesInFront+1]=-1;
        addNewWall(walls);
      }
       map[position][linesInFront+1]=SHIP_ICON;
        map[position][linesInFront++]=' ';
   }
   return;
}

int main()
{
    //int points=0;
    char** map= new char*[MAX_POSITION];
    for(int i=0;i<MAX_POSITION;i++)
    {
        map[i]=new char[MAX_LINES];
        for (int j=0;j<MAX_LINES;j++)
        {
            map[i][j]=' '; 
        }
    }
    int* walls=new int[MAX_LINES];
    for(int i=0;i<MAX_LINES;i++)
    {
        walls[i]=-1;
    }

    int numberOfWalls=4;
   // int position=4;
   // int linesInFront=4;
    map[position][linesInFront]=SHIP_ICON;//ship

    for(int i=0;i<numberOfWalls;i++) //create the walls
    {
        addNewWall(walls);
    }
    timerStart(map,walls);

    int c = 0;

    while ( c!= 27 )    //esc key code is 27
    {
        //system("cls");
        //updateMap(position,linesInFront,map);
        printMap(map);
        
        //timerStart(1000,map);
        //if (kbhit()) {
            c = getch();
            switch ( c ) 
                {
                case KEY_UP:
                   moveUp(position,linesInFront,map,walls);//key up
                    break;
                case KEY_DOWN:
                    moveDown(position,linesInFront,map,walls);  // key down
                    break;
                case KEY_LEFT:
                      moveLeft(position,linesInFront,map,walls);
                    break;
                case KEY_RIGHT:
                    moveRight(position,linesInFront,map,walls);  // key right
                    break;

                }//switch
       // }//if
    }//while

    for(int i=0;i<MAX_LINES;i++)
    {
        delete[] map[i];
    }
    delete[] map;
    delete[] walls;
    return 0;
}