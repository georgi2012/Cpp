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
            if(maze[i][j]==char(0))
            {
                cout<<"X";
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

void pathFinderRec(char **maze, const int width, const int height, unsigned const int curPathLenght,
                   unsigned int &shortest, unsigned int &longest, char **shortestMaze, char **longestMaze, const int posX, const int posY)
{
    if (maze[posX][posY] == 'x' || maze[posX][posY] == 'x') //goal!
    {
        if (curPathLenght > longest)
        {
            longest = curPathLenght;//cout<<"\nLongest: "<<longest<<" ";
            updateAnswer(maze, longestMaze, height, width);
             
            if (curPathLenght < shortest)
            {
                shortest = curPathLenght; //cout<<"\nShortest: "<<shortest<<" ";
                updateAnswer(maze, shortestMaze, height, width);
            }
            return ;
        }
        else if (curPathLenght < shortest)
        {
            shortest = curPathLenght;//cout<<"\nShortest: "<<shortest<<" ";
            updateAnswer(maze, shortestMaze, height, width);
            return;
        }
        return ;
    }

    maze[posX][posY] = char(0); //marked

    if (posX + 1 < height && (maze[posX + 1][posY] == '0' || maze[posX + 1][posY] == 'x' ))
    {
        pathFinderRec(maze, width, height, curPathLenght + 1, shortest, longest, shortestMaze, longestMaze, posX + 1, posY);
    }
    if (posX - 1 > 0 && (maze[posX - 1][posY] == '0' || maze[posX - 1][posY] == 'x'))
    {
        pathFinderRec(maze, width, height, curPathLenght + 1, shortest, longest, shortestMaze, longestMaze, posX - 1, posY);
    }
    if (posY + 1 < width && (maze[posX][posY + 1] == '0' || maze[posX][posY + 1] == 'x'))
    {
        pathFinderRec(maze, width, height, curPathLenght + 1, shortest, longest, shortestMaze, longestMaze, posX, posY + 1);
    }
    if (posY - 1 > 0 && (maze[posX][posY - 1] == '0' || maze[posX][posY - 1] == 'x'))
    {
        pathFinderRec(maze, width, height, curPathLenght + 1, shortest, longest, shortestMaze, longestMaze, posX, posY - 1);
    }

    maze[posX][posY] = '0'; //unmark path
    return;
}

/*int **convertToInt(char **mazeChar, const int width, const int height)
{
    int **mazeInt = new (nothrow) int *[height];
    for (int i = 0; i < height; i++)
    {
        mazeInt[i] = new (nothrow) int[width];

        for (int j = 0; j < width)
        {
            if (mazeChar[i][j] == '0')
            {
                mazeInt[i][j] = -300; //-300 are empty
            }
            else if (mazeChar[i][j] == 'x')
            {
                mazeInt[i][j] = 300; //goal
            }
            else
            {
                mazeInt[i][j] = (int)mazeChar[i][j];
            }
        }
    }
    return mazeInt;
}*/

main()
{
    int width, height;
    //input
    cout << "Enter maze width :";
    cin >> width;
    cout << "\nEnter maze height:";
    cin >> height;
    if (width <= 0 || height <= 0)
    {
        cout << "Inappropriate size!";
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
    cout << "By default its set to '0' for empty and 'x' for goal. Starting from (0,0) .\n";
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

    //int **maze = convertToInt(mazeSymbShort, width, height);

    unsigned int shortestPath = width * height + 1;
    unsigned int longestPath = 0;
    cout<<"Looking for paths...\n";
    pathFinderRec(maze, width, height, 0, shortestPath, longestPath, mazeSymbShort, mazeSymbLong, 0, 0);
    cout << "\nThe shortest path is " << shortestPath << endl;
    printAns(mazeSymbShort, height, width);
    cout << "\nThe longest path is " << longestPath << endl;
    printAns(mazeSymbLong, height, width);

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