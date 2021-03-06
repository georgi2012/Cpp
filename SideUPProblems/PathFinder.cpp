#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

//x goal , 0 not taken

void printAns(char **maze, const int height, const int width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (maze[i][j] == char(0))
            {
                cout << "X";
                continue;
            }
            cout << maze[i][j];
        }
        cout << endl;
    }
    return;
}

void copyMatrix(char **&curMaze, char **&answer, const int &height, const int &width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            answer[i][j] = curMaze[i][j];
        }
    }
    return;
}

bool pathFinderShort(char **maze, const int width, const int height, unsigned const int curPathLenght,
                     unsigned int &shortest, char **shortestMaze, const int posX, const int posY, bool isSecondRun)
{
    if (maze[posX][posY] == 'x') //goal!
    {
        if (!isSecondRun && curPathLenght < shortest)
        {
            shortest = curPathLenght;
            //updateAnswer(maze, shortestMaze, height, width);
            return false;
        }
        if (isSecondRun && curPathLenght == shortest)
        {
            shortestMaze[posX][posY] = char(0);
            return true;
        }
        return false;
    }
    maze[posX][posY] = char(0); //marked
    bool isAns = false;

    if (posX + 1 < height && (maze[posX + 1][posY] == '0' || maze[posX + 1][posY] == 'x'))
    {
        if (pathFinderShort(maze, width, height, curPathLenght + 1, shortest, shortestMaze, posX + 1, posY, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                shortestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posX - 1 > 0 && (maze[posX - 1][posY] == '0' || maze[posX - 1][posY] == 'x'))
    {
        if (pathFinderShort(maze, width, height, curPathLenght + 1, shortest, shortestMaze, posX - 1, posY, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                shortestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posY + 1 < width && (maze[posX][posY + 1] == '0' || maze[posX][posY + 1] == 'x'))
    {
        if (pathFinderShort(maze, width, height, curPathLenght + 1, shortest, shortestMaze, posX, posY + 1, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                shortestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posY - 1 > 0 && (maze[posX][posY - 1] == '0' || maze[posX][posY - 1] == 'x'))
    {
        if (pathFinderShort(maze, width, height, curPathLenght + 1, shortest, shortestMaze, posX, posY - 1, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                shortestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }

    maze[posX][posY] = '0'; //unmark path

    return isAns;
}

bool pathFinderLong(char **maze, const int width, const int height, unsigned const int curPathLenght,
                    unsigned int &longest, char **longestMaze, const int posX, const int posY, bool isSecondRun)
{
    if (maze[posX][posY] == 'x') //goal!
    {
        if (!isSecondRun && curPathLenght > longest)
        {
            longest = curPathLenght;
            //updateAnswer(maze, shortestMaze, height, width);
            return false; //found
        }
        if (isSecondRun && curPathLenght == longest)
        {
            longestMaze[posX][posY] = char(0);
            return true;
        }
        return false;
    }

    maze[posX][posY] = char(0); //marked
    bool isAns = false;

    if (posX + 1 < height && (maze[posX + 1][posY] == '0' || maze[posX + 1][posY] == 'x'))
    {
        if (pathFinderLong(maze, width, height, curPathLenght + 1, longest, longestMaze, posX + 1, posY, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                longestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posX - 1 > 0 && (maze[posX - 1][posY] == '0' || maze[posX - 1][posY] == 'x'))
    {
        if (pathFinderLong(maze, width, height, curPathLenght + 1, longest, longestMaze, posX - 1, posY, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                longestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posY + 1 < width && (maze[posX][posY + 1] == '0' || maze[posX][posY + 1] == 'x'))
    {
        if (pathFinderLong(maze, width, height, curPathLenght + 1, longest, longestMaze, posX, posY + 1, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                longestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }
    if (posY - 1 > 0 && (maze[posX][posY - 1] == '0' || maze[posX][posY - 1] == 'x'))
    {
        if (pathFinderLong(maze, width, height, curPathLenght + 1, longest, longestMaze, posX, posY - 1, isSecondRun))
        {
            isAns = true;
            if (isSecondRun)
            {
                longestMaze[posX][posY] = char(0);
                maze[posX][posY] = '0';
                return isAns;
            }
        }
    }

    maze[posX][posY] = '0'; //unmark path
    return isAns;
}

main()
{
    int width, height;
    int posX, posY;
    //input
    cout << "Enter maze width :";
    cin >> width;
    cout << "\nEnter maze height:";
    cin >> height;
    if (width <= 0 || height <= 0)
    {
        cout << "Inappropriate size!\n";
        return 1;
    }
    cout << "Enter the position (x,y) where you start from . Firstly , X , than Y: ";
    cin >> posX >> posY;
    if (posX >= width || posX < 0 || posY >= height || posY < 0)
    {
        cout << "Wrong coordinates!\n";
        return 1;
    }

    char **mazeSymb = new (nothrow) char *[height];
    if (!mazeSymb)
    {
        std::cerr << "Problem allocating enough memory.";
        return 2;
    }

    char **maze = new (nothrow) char *[height];
    if (!maze)
    {
        delete[] mazeSymb;
        std::cerr << "Problem allocating enough memory.";
        return 2;
    }

    for (int i = 0; i < height; i++)
    {
        mazeSymb[i] = new (nothrow) char[width];
        if(!mazeSymb[i])
        {
             std::cerr << "Problem allocating enough memory.";
            for(int j=0;j<=i;j++)
            {
                delete[] mazeSymb[j];
                delete[] maze[j];
            }
            delete[] mazeSymb;
            delete[] maze;
            return 2;
        }
        maze[i] = new (nothrow) char[width];
        if(!maze[i])
        {
             std::cerr << "Problem allocating enough memory.";
            for(int j=0;j<=i;j++)
            {
                delete[] mazeSymb[j];
                delete[] maze[j];
            }
            delete[] mazeSymb;
            delete[] maze;
            return 2;
        }
    }
    cout << "By default its set to '0' for empty and 'x' for goal. Starting from (x,y) .\n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cin >> mazeSymb[i][j];
            maze[i][j] = mazeSymb[i][j];
        }
    }
    //end of input and declaration
    unsigned int shortestPath = width * height + 1;
    unsigned int longestPath = 0;
    cout << "\nLooking for paths...\n";
    pathFinderShort(maze, width, height, 0, shortestPath, mazeSymb, posY, posX, false);
    if (shortestPath == width * height + 1)
    {
        cout << "No path found!\n";
    }
    else
    {
        pathFinderShort(maze, width, height, 0, shortestPath, mazeSymb, posY, posX, true);
        cout << "\nThe shortest path is " << shortestPath << endl;
        printAns(mazeSymb, height, width);
        //
        copyMatrix(maze, mazeSymb, height, width); //nullify mazeSymb
        //
        pathFinderLong(maze, width, height, 0, longestPath, mazeSymb, posY, posX, false);
        pathFinderLong(maze, width, height, 0, longestPath, mazeSymb, posY, posX, true);
        //
        cout << "\nThe longest path is " << longestPath << endl;
        printAns(mazeSymb, height, width);
    }

    for (int i = 0; i < height; i++)
    {
        delete[] mazeSymb[i];
        delete[] maze[i];
    }
    delete[] mazeSymb;
    delete[] maze;

    return 0;
}
/* test input

6 7 0 0
001111
01100x
000010
011110
011110
000000
00000x

*/