#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

int getSentenceLenght(const char *sentence)
{
    int i = 0;
    while (sentence[i] != '.')
    {
        i++;
    }
    return i;
}

void printSentenceBackwards(const char *sentence)
{
    const int size = getSentenceLenght(sentence);
    int i = size - 1;
    while (i >= 0)
    {
        if (sentence[i] == ' ')
        {
            int j = i + 1;
            while (sentence[j] != ' ' && j < size)
            {
                cout << sentence[j];
                j++;
            }
            cout << " ";
        }

        i--;
    }
    i = 0;
    while (sentence[i] != ' ')
    {
        cout << sentence[i];
        i++;
    }
    cout << ".\n";

    return;
}

int main()
{
    char sentence[1000] = {};
    cin.getline(sentence, 999);
    cout<<endl;
    printSentenceBackwards(sentence);
    return 0;
}