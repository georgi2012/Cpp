#include <iostream>
#include <windows.h>

int checkForRepeats(char *text, const char symbow, int startingPoint)
{

    while (text[startingPoint] != '\0')
    {
        if (text[startingPoint] == symbow)
        {
            return startingPoint;
        }
        startingPoint++;
    }
    return -1;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    char text[206];
    std::cin.getline(text, 205);

    int min = 207;
    int minRepeat = 207;
    int repeat = -1;
    int i = 0;
    while (text[i + 1] != '\0')
    {
        repeat = checkForRepeats(text, text[i], i + 1);
        if (repeat > 0)
        {
            if (min == 207 || (repeat < minRepeat))
            {
                min = i;
                minRepeat = repeat;
            }
        }
        i++;
    }
    if (min != 207)
    {
        std::cout << min + 1 << " " << minRepeat + 1 << "\n";
    }

    return 0;
}