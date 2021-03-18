#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27

#include <conio.h>
//#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>
#include <windows.h>
//too many includes already ;(

//using namespace std; 

using std::cout;
using std::endl; 
using std::thread;

const int MAX_POSITION = 9;
const int MAX_LINES = 9;
const char SHIP_ICON = '@';
const char WALL_ICON = 'W';
const char STAR_ICON = '*';
//
int points = 0;
int interval = 1000;
int position = 4;
int linesInFront = 4;
int star[2]; //[row][col]
bool NewWall=false;
int bestResult=0;
//
//prototypes
void printMap(char **map);
void updateMapWalls(int *walls, char **map);
//

void hitWall()
{
    points--;
}
void claimStar()
{
    points++;
    if(points==3)
    {
        interval=800;
        NewWall=true;
    }
    else if(points==6)
    {
        interval=650;
        NewWall=true;
    }
    else if (points==10)
    {
        interval=500;
        NewWall=true;
    }
}

void addNewStar(int *walls)
{
    srand(time(NULL));
    int newStar;
    do
    {
        newStar = rand() % (MAX_LINES - 1); //find a place with no wall on it to spawn

    } while (walls[newStar] == 0);
    star[0] = 0;
    star[1] = newStar;
    return;
}

void addNewWall(int *walls)
{
    if(NewWall)
    {
        NewWall=false;
        addNewWall(walls);
    }
    srand(time(NULL));
    int newWall;
    do
    {
        newWall = rand() % (MAX_LINES - 1); //find a column with no walls on it currently

    } while (walls[newWall] >= 0);
    walls[newWall] = 0;
    //cout<<"Added on "<<newWall;
    return;
}

void timerStart(char **map, int *walls) //should be called every interval of time
{
    std::thread([map, walls]() {
        while (true)
        {
            // printMap(map);
            updateMapWalls(walls, map);
            printMap(map);
            std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        }
    }).detach();
}

/*
void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  // Get the number of cells in the current buffer 
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  // Fill the entire buffer with spaces 
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  // Fill the entire buffer with the current colors and attributes 
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }
  */
void ClearScreen()
{
    system("CLS");
}


void printMap(char **map)
{
    //system("CLS");
    ClearScreen();
    cout << endl;
    for (int i = 0; i < MAX_POSITION; i++)
    {
        cout << "|"; //<<map[i]<<"|"<<endl; -> buggy for some reason
        for (int j = 0; j < MAX_LINES; j++)
        {
            cout << map[i][j]; //works perfect , probably slower than the upper solution
        }
        cout << "|" << endl;
    }
    for (int i = 0; i < MAX_LINES + 2; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "Points: " << points << endl;
    if(points>bestResult)
    {
        bestResult=points;
    }
    cout<<"Best result: "<<bestResult<<endl
         << std::flush;
    return;
}

void updateMapWalls(int *walls, char **map) //wall cell is the column and it's value is the row
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (walls[i] >= 0) //there is a wall
        {
            if (walls[i] >= MAX_POSITION - 1) //out of the window. Destroyed
            {                                 //cout<<"removed ";
                map[walls[i]][i] = ' ';
                walls[i] = -1;
                addNewWall(walls);
                continue;
            }
            //if(map[walls[i]][i]==SHIP_ICON) //does not work well
            if (walls[i] + 1 == position && i == linesInFront) //hit
            {
                map[walls[i]][i] = ' ';
                walls[i] = -1;
                addNewWall(walls);
                hitWall();
                // return;
                continue;
            }
            //else move it
            map[walls[i]][i] = ' ';
            walls[i]++;
            map[walls[i]][i] = WALL_ICON;
        }
    }

    if (star[0] + 1 == position && star[1] == linesInFront) //hit the star
    {
        map[star[0]][star[1]] = ' ';
        claimStar();
        addNewStar(walls);
        return;
    }
    //else move the star
    if (star[0] < MAX_POSITION) {
        map[star[0]][star[1]] = ' ';
        map[++star[0]][star[1]] = STAR_ICON;
    }
    else {
        map[star[0]][star[1]] = ' ';
        addNewStar(walls);
    }

    return;
}

void moveDown(int &position, int &linesInFront, char **map, int *walls)
{
    if (position < MAX_POSITION - 1)
    {
        if (position + 1 == walls[linesInFront]) //its a wall
        {
            hitWall();
            walls[linesInFront] = -1;
            addNewWall(walls);
        }
        else if (position + 1 == star[0] && linesInFront == star[1]) //its a star
        {
            claimStar();
            addNewStar(walls);
        }
        map[position + 1][linesInFront] = SHIP_ICON;
        map[position++][linesInFront] = ' ';
    }
    return;
}

void moveUp(int &position, int &linesInFront, char **map, int *walls)
{
    if (position > 0)
    {
        if (position - 1 == walls[linesInFront]) //its a wall
        {
            hitWall();
            walls[linesInFront] = -1;
            addNewWall(walls);
        }
        else if (position - 1 == star[0] && linesInFront == star[1])
        {
            claimStar();
            addNewStar(walls);
        }
        map[position - 1][linesInFront] = SHIP_ICON;
        map[position--][linesInFront] = ' ';
    }
    return;
}

void moveLeft(int &position, int &linesInFront, char **map, int *walls)
{
    if (linesInFront > 0)
    {
        if (walls[linesInFront - 1] == position) //its a wall
        {
            hitWall();
            walls[linesInFront - 1] = -1;
            addNewWall(walls);
        }
        else if (position == star[0] && linesInFront - 1 == star[1])
        {
            claimStar();
            addNewStar(walls);
        }
        map[position][linesInFront - 1] = SHIP_ICON;
        map[position][linesInFront--] = ' ';
    }
    return;
}

void moveRight(int &position, int &linesInFront, char **map, int *walls)
{
    if (linesInFront < MAX_LINES - 1)
    {
        if (walls[linesInFront + 1] == position) //its a wall
        {
            hitWall();
            walls[linesInFront + 1] = -1;
            addNewWall(walls);
        }
        else if (position == star[0] && linesInFront + 1 == star[1])
        {
            claimStar();
            addNewStar(walls);
        }
        map[position][linesInFront + 1] = SHIP_ICON;
        map[position][linesInFront++] = ' ';
    }
    return;
}

int main()
{
    //cout << std::flush;
    char **map = new char *[MAX_POSITION];
    for (int i = 0; i < MAX_POSITION; i++)
    {
        map[i] = new char[MAX_LINES];
        for (int j = 0; j < MAX_LINES; j++)
        {
            map[i][j] = ' ';
        }
    }
    int *walls = new int[MAX_LINES];
    for (int i = 0; i < MAX_LINES; i++)
    {
        walls[i] = -1;
    }

    int numberOfWalls = 4;
    // int position=4;
    // int linesInFront=4;
    map[position][linesInFront] = SHIP_ICON; //ship

    for (int i = 0; i < numberOfWalls; i++) //create the walls
    {
        addNewWall(walls);
    }
    addNewStar(walls);

    timerStart(map, walls);

    int c = 0;

    while (c != KEY_ESC) //esc key code is 27
    {
        printMap(map);

        //if (kbhit()) {
        c = _getch();
        switch (c)
        {
        case KEY_UP:
            moveUp(position, linesInFront, map, walls); //key up
            break;
        case KEY_DOWN:
            moveDown(position, linesInFront, map, walls); // key down
            break;
        case KEY_LEFT:
            moveLeft(position, linesInFront, map, walls);
            break;
        case KEY_RIGHT:
            moveRight(position, linesInFront, map, walls); // key right
            break;

        } //switch
          // }//if
    }     //while

    for (int i = 0; i < MAX_LINES; i++)
    {
        delete[] map[i];
    }
    delete[] map;
    delete[] walls;
    //system("CLS");
    
    return 0;
}