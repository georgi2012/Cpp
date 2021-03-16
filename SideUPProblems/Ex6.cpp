#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int numberOfWords(char *text)
{
    int index = 0;
    int br = 0;
    bool isNextWord = true;
    while (text[index] != '\0')
    {
        if (text[index] == ' ')
        {
            isNextWord = true;
        }
        else
        {
            if (isNextWord)
            {
                br++;
                isNextWord = false;
            }
        }
        index++;
    }
    return br;
}

int nextWordHelper(char *text, const int wordIndex) ///find where the wanted word starts
{
    int index = 0;
    int br = 0;
    bool isNextWord = true;

    while (text[index] != '\0')
    {
        if (br == wordIndex)
        {
            if (br == 0)
            {
                return 0;
            }
            return index - 1;
        }
        if (text[index] == ' ')
        {
            isNextWord = true;
        }
        else
        {
            if (isNextWord)
            {
                br++;
                isNextWord = false;
            }
        }

        index++;
    }
}
char *nextWord(char *text, const int wordIndex)
{
    int index = nextWordHelper(text, wordIndex); //where to start from
    //cout<<"starts from index :"<<index<<" ";
    char *word = new (std::nothrow) char[100];
    int br = 0;

    while (text[index] == ' ') //leading spaces
    {
        index++;
    }
    while (text[index] != ' ' || text[index] == '\0') //next word
    {
        word[br] = text[index];
        br++;
        index++;
    }
    //cout<<"Ind for "<<wordIndex<<": "<<index<<endl;
    word[br] = '\0';
    return word;
}
bool areEqual(char *word1, char *word2)
{
    int index = 0;
    while (word1[index] != '\0')
    {
        if (word1[index] != word2[index])
        {
            return false;
        }
        index++;
    }
    if (word2[index] == '\0')
    {
        return true;
    }
    return false;
}

int numOfRepeats(char *word, char *text, const int wordIndex, bool *isChecked, const int numOfWords)
{
    isChecked[wordIndex] = true;
    int numOfRepeats=0;
    char *wordToCompare;
    for (int i = wordIndex; i < numOfWords; i++)
    {
        wordToCompare = nextWord(text, i );
        //cout<<"Comp "<<word<<" and "<<wordToCompare;
        if (!isChecked[i] && areEqual(wordToCompare, word))
        {
            isChecked[i]=true; //cout<<" "<<i+1<<" checked! \n";
            numOfRepeats++;
        }//cout<<endl;
        delete[] wordToCompare;
    }
    return numOfRepeats;
}

int main()
{
    char *text = new (std::nothrow) char[1001];
    char *word;
    cin.getline(text, 1000);
    const int numOfWords = numberOfWords(text);
    bool *isChecked = new (std::nothrow) bool[numOfWords];
    for (int i = 0; i < numOfWords; i++)
    {
        isChecked[i] = false;
    }
    //int index = 0;
    cout<<"Num of words:"<<numOfWords<<endl;
    for (int i = 0; i < numOfWords; i++)
    {
        if (!isChecked[i])
        {
            word = nextWord(text, i); 
            cout<<word<<" "<<numOfRepeats(word,text,i,isChecked,numOfWords)+1<<endl;
            //
            delete[] word;
        }
        
    }

    return 0;
}