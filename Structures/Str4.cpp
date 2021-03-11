#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;

struct Library
{
    char headline[100];
    char author[100];
    unsigned int ISBN;
};

void inputBook(Library &book)
{
    cout << "Author: " << endl;
    cin.sync();
    cin.getline(book.author, 99);
    cout << "Healine:" << endl;
    cin.sync();
    cin.getline(book.headline, 99);
    cout << "ISBN : \n";
    cin >> book.ISBN;
    return;
}

void strCopy(char *string1, const char *string2)
{
    int i = 0;
    while (string2[i] != '\0')
    {
        string1[i] = string2[i];
        i++;
    }
    string1[i] = '\0';
    return;
}

Library *removeBook(Library *books, int &n, const int ISBN)
{
    int g = 0;
    Library *newBook = new (nothrow) Library[--n];
    if (!newBook)
    {
        cout << "problem allocating memory!";
        return nullptr;
    }
    for (int i = 0; i <= n; i++)
    {
        if (books[i].ISBN != ISBN)
        {
            strCopy(newBook[g].author, books[i].author);
            newBook[g].ISBN = books[i].ISBN;
            strCopy(newBook[g++].headline, books[i].headline);
        }
    }
    delete[] books;
    return newBook;
}

int main()
{
    
    int n;
    int numberToDelete;
    cin >> n;
    if (!cin || n<0)
    {
        cout<<"Bad input";
        return 1;
    }
    Library *books = new (nothrow) Library[n];
    if (!cin || !books)
    {
        cout << "Problem allocating memory .";
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        inputBook(books[i]);
    }

    cout << "ISBN to remove: ";
    cin >> numberToDelete;

    books = removeBook(books, n, numberToDelete);
    for (int i = 0; i < n; i++)
    {
        cout << books[i].author << " " << books[i].headline << endl;
    }

    cout << "Size: " << n << endl;

    delete[] books;
    return 0;
}
