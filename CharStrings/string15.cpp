#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

char *getNextWord(char *text, int &index)
{
    char *word = new (nothrow) char[31];
    int j = 0;
    while (text[index] != ' ')
    {
        word[j] = text[index];
        index++;
        j++;
    }
    word[j] = '\0';
    return word;
}

int compareText(char *text1, char *text2) // +1 ->text1>text2 , -1 text1< text2  0-text1=text2 ,2 - text2 is empty
{

    if (text2[0] = '\0')
    {
        return 2;
    }
    int i = 0;
    while (text1[i] != '\0')
    {
        if (text1[i] > text2[i])
        {
            return 1;
        }
        else if (text1[i] < text2[i])
        {
            return -1;
        }
    }
    return 0;
}

int checkForExistance(char **library, char *word, const int librarySize)
{
    int result = 0;
    for (int i = 0; i < librarySize; i++)
    {
        result = compareText(library[i], word);
        if (result == 0)
        {
            return i; // we have that word already or its a new one
        }
        else if (result == 2)
        {
            library[i] = word; //new word added to the list
            return i;
        }
    }
    //return -1;
}

int removeCapsAndSymbowsAndGetSize(char *text)
{
    int i = 0;
    const int difference = 'A' - 'a';
    while (text[i] != '\0')
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            text[i] -= difference;
        }
        else if (text[i] < 'a' || text[i] > 'z') //some symbow
        {
            text[i] = ' ';
        }
        i++;
    }
    return i;
}

int findAllWords(int *differentWordsBr)
{
    int i = 0;
    int br = 0;
    while (differentWordsBr[i] != 0)
    {
        br = differentWordsBr[i];
        i++;
    }
    return br;
}
int findDiffWords(int *differentWordsBr)
{
    int i = 0;
    while (differentWordsBr[i] != 0)
    {
        i++;
    }
    return i;
}

void SortWords(int *differentWordsBr, char **differentWords)
{
    int diff = findDiffWords(differentWordsBr);
    for (int i = 0; i < diff - 1; i++)
    {
        for (int j = i + 1; j < diff; j++)
        {
            if (differentWordsBr[i] < differentWordsBr[j])
            {
                std::swap(differentWordsBr[i], differentWordsBr[j]);
                std::swap(differentWords[i], differentWords[j]);
            }
            else if (differentWordsBr[i] == differentWordsBr[j] && compareText(differentWords[i], differentWords[j]) == 1)
            {
                std::swap(differentWordsBr[i], differentWordsBr[j]);
                std::swap(differentWords[i], differentWords[j]);
            }
        }
    }
    return;
}

void printDiffentWords(int *differentWordsBr, char **differentWords)
{
    SortWords(differentWordsBr, differentWords);

    int i = 0;
    while (differentWordsBr[i] != 0)
    {
        cout << differentWords[i] << " - " << differentWordsBr[i] << endl;
    }
    return;
}

int main()
{

    char text[20000] = {};
    char *nextWord = new char[31];
    nextWord[0] = 'a';
    cin.getline(text, 19999, '$');
    cout<<"your input is :"<<text<<endl;
    const int size = removeCapsAndSymbowsAndGetSize(text);
    int *differentWordsBr;
    char **differentWords;
    int curIndex = 0;

    if (size < 2000)
    {
        differentWordsBr = new (nothrow) int[size];
        if (!differentWordsBr)
        {
            std::cerr << "Could not allocate enough memory.";
            return 1;
        }
        for (int i = 0; i < size; i++)
        {
            differentWordsBr[i] = 0;
        }
        differentWords = new (nothrow) char *[size];
        if (differentWords == nullptr)
        {
            delete[] differentWordsBr;
            std::cerr << "Could not allocate enough memory.";
            return 1;
        }
        for (int i = 0; i < size; i++)
        {
            differentWords[i] = new (nothrow) char[31];
            differentWords[i][0] = '\0';

            if (!differentWords[i])
            {
                cout << "Okay , I am pretty sure that wont happen and I am too lazy";
                cout << " to delete all that dynamic memory so I'll skip that part...";
            }
        }
    }
    else
    {
        differentWordsBr = new (nothrow) int[2000];
        if (!differentWordsBr)
        {
            std::cerr << "Could not allocate enough memory.";
            return 1;
        }

        differentWords = new (nothrow) char *[2000];
        if (differentWordsBr == nullptr)
        {
            delete[] differentWordsBr;
            std::cerr << "Could not allocate enough memory.";
            return 1;
        }
        for (int i = 0; i < 2000; i++)
        {
            differentWords[i] = new (nothrow) char[31];
            if (!differentWords[i])
            {
                cout << "Okay , I am pretty sure that wont happen and I am too lazy";
                cout << " to delete all that dynamic memory so I'll skip that part...";
            }
        }
    }

    while (nextWord[0] != '\0' )
    {
        nextWord = getNextWord(text, curIndex); cout<<"Next word : "<<nextWord<<endl;
        differentWordsBr[checkForExistance(differentWords, nextWord, size)]++; 
        delete[] nextWord;
    }

    cout << "All words - " << findAllWords(differentWordsBr) << endl;
    cout << "Distinct words - " << findDiffWords(differentWordsBr) << endl;

    delete[] differentWordsBr;
    if (size < 2000)
    {
        for (int i = 0; i < size; i++)
        {
            delete[] differentWords[i];
        }
    }
    else
    {
        for (int i = 0; i < 2000; i++)
        {
            delete[] differentWords[i];
        }
    }
    delete[] differentWords;
    return 0;
}
