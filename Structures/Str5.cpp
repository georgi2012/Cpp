#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::nothrow;
using std::swap;

struct Library
{
    char headline[100];
    char author[100];
    long price;
};

void inputBook(Library &book)
{
    cout << "Author: " << endl;
    cin.sync();
    cin.getline(book.author, 99);
    cout << "Healine:" << endl;
    cin.sync();
    cin.getline(book.headline, 99);
    cout << "Price : \n";
    cin >> book.price;
    return;
}

void sortByAuthor(Library *books, const int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int index = 0;
            while (books[i].author[index] != '\0')
            {
                if (books[i].author[index] < books[j].author[index])
                {
                    swap(books[i], books[j]);
                    break;
                }
                index++;
            }
        }
    }
    return;
}

void sortByTitle(Library *books, const int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int index = 0;
            while (books[i].headline[index] != '\0')
            {
                if (books[i].headline[index] < books[j].headline[index])
                {
                    swap(books[i], books[j]);
                    break;
                }
                index++;
            }
        }
    }
    return;
}

void sortByPrice(Library *books, const int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (books[i].price > books[j].price)
            {
                swap(books[i], books[j]);
            }
        }
    }
    return;
}

void printAns(const Library *books, const int n)
{
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << books[i].author << " ";
        cout << books[i].headline << " ";
        cout << books[i].price << "\n";
    }
    return;
}

int main()
{

    long long n;
    int sortingOrder;
    cin >> n;
    if (!cin || n < 0)
    {
        cout << "Bad input";
        return 1;
    }
    /*try
    {
    Library *books = new (nothrow) Library[n];
    }
    catch (std::exception &e)
    {
        cout << "Exception";
        return 2;
    }*/
    Library *books = new (nothrow) Library[n];

    if (books == nullptr)
    {
        cout << "Problem allocating memory .";
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        inputBook(books[i]);
    }
    cout << "1 for sorting by Author \n2 for sorting by Title \n3 for sorting by Price\n";
    cin >> sortingOrder;
    switch (sortingOrder)
    {
    case 1:
        sortByAuthor(books, n);
        break;
    case 2:
        sortByTitle(books, n);
        break;
    case 3:
        sortByPrice(books, n);
        break;
    default:
        cout << "No such sorting index!\n";
        break;
    }

    printAns(books, n);

    delete[] books;
    return 0;
}
