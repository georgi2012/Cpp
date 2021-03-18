#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Library
{
public:
    char healine[100];
    char author[100];
    char ISBN[14];
};

void addBook(Library &bookSpace)
{
    //cout<<endl;
    cin.ignore();;
    cin.get(bookSpace.author, 99); // nqma go
    cin.ignore();
   
    cin.getline(bookSpace.healine, 99);
    if (bookSpace.healine[0] >= 'a' && bookSpace.healine[0] <= 'z')
    {
        bookSpace.healine[0] += 'A' - 'a';
    }
    //cin.ignore();
    cin>>bookSpace.ISBN;
    cout<<"added "<<bookSpace.healine <<" by "<<bookSpace.author<<" isbn:"<<bookSpace.ISBN<<endl;
    return;
}

bool areStringsEqual(char *string1, char *string2)
{
    cout<<"Comparing "<<string1<<" and "<<string2<<endl;
    int index = 0;
    while (string1[index] != '\0')
    {
        if (string1[index] != string2[index])
        {
            return false;
        }
        index++;
    }
    if (string2[index] == '\0')
    {
        return true;
    }
    return false;
}

void copyString(char *string1, char *string2)
{
    int i = 0;
    while (string1[i] != '\0')
    {
        string2[i] = string1[i];
        i++;
    }
    return;
}

bool removeBoook(Library *&books, char *ISBNtoRemove, const int size)
{
    int searchedIndex = 0;
    bool isFound=false;
    for (searchedIndex = 0; searchedIndex < size; searchedIndex++)
    {
        if (areStringsEqual(books[searchedIndex].ISBN, ISBNtoRemove))
        {
            isFound=true;
            break;
        }
    }
    if(isFound){
    cout<<"Removed "<<books[searchedIndex].healine<<endl;
    }
    else {
        cout<<"No such book found ."<<endl;
        return false;
    }

    for (int i = searchedIndex + 1; i < size; i++)
    {
        copyString(books[searchedIndex].author, books[searchedIndex - 1].author);
        copyString(books[searchedIndex].healine, books[searchedIndex - 1].healine);
        copyString(books[searchedIndex].ISBN, books[searchedIndex - 1].ISBN);
    }
    return true;
}



int main()
{
    Library *books = new (std::nothrow) Library[1000];
    if (!books)
    {
        std::cerr << "Could not allocate enough memory . :( ";
        return 1;
    }

    int choice;
    int size = 0;
    char ISBNtoRemove[20];

    while (true)
    {
        cout << "Input 1 for add + author + healine + ISBN. Input 2 for remove + ISBN." << endl;
        cout << "Input 3 to see how many books are in the library. 4 to stop program .\n";

        cin >> choice;
        if (choice == 1)
        {
            if (size >= 999)
            {
                cout << "No place for more books in the library\n";
                continue;
            }
            addBook(books[size]);
            size++;
            //cout << "added size " << size << endl;
        }
        else if (choice == 2)
        {
            if (size <= 0)
            {
                cout << "No books in the library\n";
                continue;
            }
            cin >> ISBNtoRemove;
            if(removeBoook(books, ISBNtoRemove, size))
            {
             size--;
            }
        }
        else if (choice == 3)
        {
            cout << size << endl;
        }
        else if (choice == 4)
        {
            break;
        }
    }

    /* for (int i=0;i<numOfBooks;i++)
   {
       addBook(books[i]);
   }
    for (int i=0;i<numOfBooks;i++)
   {
       cout<<books[i].healine<<endl;
   }
   int deleteNum;
   cin>>deleteNum;
   for (int i=0;i<deleteNum;i++)
   {

   }
*/
    delete[] books;
    return 0;
}