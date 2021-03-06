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
        for (int j = 0; j < height; j++)
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

void updateAnswer(char **curMaze, char **&answer, const int &height, const int &width)
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; i < width; i++)
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
    int posX,posY;
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
    cout<<"Enter the position (x,y) where you start from . Firstly , X , than Y: ";
    cin>>posX>>posY;
    if(posX>=width || posX<0 || posY>=height || posY<0)
    {
        cout<<"Wrong coordinates!\n";
        return 1;
    }

    char **mazeSymbShort = new (nothrow) char *[height];
    char **mazeSymbLong = new (nothrow) char *[height];
    char **maze = new (nothrow) char *[height];
    for (int i = 0; i < height; i++)
    {
        mazeSymbShort[i] = new (nothrow) char[width];
        mazeSymbLong[i] = new (nothrow) char[width];
        maze[i] = new (nothrow) char[width];
    }
    cout << "By default its set to '0' for empty and 'x' for goal. Starting from (x,y) .\n";
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            cin >> mazeSymbShort[i][j];
            mazeSymbLong[i][j] = mazeSymbShort[i][j];
            maze[i][j] = mazeSymbShort[i][j];
        }
    }
    //
    unsigned int shortestPath = width * height + 1;
    unsigned int longestPath = 0;
    cout << "\nLooking for paths...\n";
    pathFinderShort(maze, width, height, 0, shortestPath, mazeSymbShort, posY, posX, false);
    if (shortestPath == width * height + 1)
    {
        cout << "No path found!\n";
    }
    else
    {
        pathFinderShort(maze, width, height, 0, shortestPath, mazeSymbShort, posY, posX, true);
        cout << "\nThe shortest path is " << shortestPath << endl;
        printAns(mazeSymbShort, height, width);

        pathFinderLong(maze, width, height, 0, longestPath, mazeSymbLong, posY, posX, false);
        pathFinderLong(maze, width, height, 0, longestPath, mazeSymbLong, posY, posX, true);
        cout << "\nThe longest path is " << longestPath << endl;
        printAns(mazeSymbLong, height, width);
    }

    for (int i = 0; i < height; i++)
    {
        delete[] mazeSymbShort[i];
        delete[] mazeSymbLong[i];
        delete[] maze[i];
    }
    delete[] mazeSymbShort;
    delete[] mazeSymbLong;
    delete[] maze;

    return 0;
}