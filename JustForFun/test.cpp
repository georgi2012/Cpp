//#include <conio.h>
//#include <stdio.h>
#include <iostream>
//#include <thread>
//#include <chrono>
//#include <time.h> 
//#include <windows.h>

const int MAX_POSITION=9;
const int MAX_LINES=9;
const char SHIP_ICON='@';
const char WALL_ICON='#';


#include <windows.h>

void ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }

  int main()
  {
       int i=0;
      while(i!=5){
      std::cout<<"Hello there";
      ClearScreen();
      std::cout<<"Is it clear?"<<std::endl;
     
      std::cin>>i;
      }
      return 0;
  }