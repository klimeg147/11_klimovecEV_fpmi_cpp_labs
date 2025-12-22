#include <iostream>
#include <iostream>
#include <fstream>
#include <list>
#include <set>
#include <string>
#include <locale>

using namespace std;

struct Author {
    string surname;


    bool operator<(const Author& other) const {
        return surname < other.surname;
    }
};


struct Book {
    int udk;
    set<Author> authors;
    string title;
    int year;


    bool operator<(const Book& other) const {
        return title < other.title;
    }

    void print() {
        cout << "\"" << title << "\" (" << year << ")\n";
        cout << "UDK: " << udk << "\n";
        cout << "Authors: ";
        for (const Author& a : authors) {
            cout << a.surname << " ";
        }
        cout << "\n";
    }
};

int main() {
    
    list<Book> library;

    ifstream file("books.txt");

    if (file.is_open()) {
        Book book;
        int authorCount;

        while (file >> book.udk >> authorCount) {
            book.authors.clear();

            for (int i = 0; i < authorCount; i++) {
                Author a;
                file >> a.surname;
                book.authors.insert(a);
            }

            file.ignore();
            getline(file, book.title);
            file >> book.year;

            library.push_back(book);
        }

        library.sort();

        cout << "Downloaded " << library.size() << " books\n";
        file.close();
    }
    else {
        cout << "File books.txt not found\n";
    }

    cout << "\nAll books (sorted by names)\n";
    for (Book& b : library) {
        b.print();
    }

    cout << "\n=== Adding new book ===\n";
    Book newBook;

    cout << "Enter UDK: ";
    cin >> newBook.udk;

    cout << "Enter book's name: ";
    cin.ignore();
    getline(cin, newBook.title);

    cout << "Enter year: ";
    cin >> newBook.year;

    int n;
    cout << "Enter number of authors: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Author a;
        cout << "Author's surname " << i + 1 << ": ";
        cin >> a.surname;
        newBook.authors.insert(a);
    }

    auto it = library.begin();
    while (it != library.end() && it->title < newBook.title) {
        it++;
    }
    library.insert(it, newBook);

    cout << "\n=== All books after adding ===\n";
    for (Book& b : library) {
        b.print();
    }

    cout << "\n=== Book deleting ===\n";
    string delTitle;
    cout << "Enter book's name to delete: ";
    cin.ignore();
    getline(cin, delTitle);

    for (auto it = library.begin(); it != library.end(); it++) {
        if (it->title == delTitle) {
            library.erase(it);
            cout << "Book deleted\n";
            break;
        }
    }

    cout << "\n=== Seeking books by author ===\n";
    string authorSurname;
    cout << "Enter author's surname: ";
    cin >> authorSurname;

    cout << "Author's book " << authorSurname << ":\n";
    bool found = false;
    for (Book& b : library) {
        for (const Author& a : b.authors) {
            if (a.surname == authorSurname) {
                b.print();
                found = true;
                break;
            }
        }
    }
    if (!found) {
        cout << "Books wasn't found\n";
    }

    cout << "\n=== Adding author to book ===\n";
    string bookTitle;
    cout << "Enter book's name: ";
    cin.ignore();
    getline(cin, bookTitle);

    for (Book& b : library) {
        if (b.title == bookTitle) {
            Author newAuthor;
            cout << "Enter new authors surname: ";
            cin >> newAuthor.surname;
            b.authors.insert(newAuthor);
            cout << "Author added\n";
            cout << "Ubdated book info:\n";
            b.print();
            break;
        }
    }

    cout << "\n=== Deleting author from book ===\n";
    cout << "Enter books name: ";
    cin.ignore();
    getline(cin, bookTitle);

    string delAuthor;
    cout << "Enter authors surname to delete: ";
    cin >> delAuthor;

    for (Book& b : library) {
        if (b.title == bookTitle) {
            for (auto it = b.authors.begin(); it != b.authors.end(); it++) {
                if (it->surname == delAuthor) {
                    b.authors.erase(it);
                    cout << "Author deleted\n";
                    cout << "Updated books info:\n";
                    b.print();
                    break;
                }
            }
            break;
        }
    }

    cout << "\n=== Final book list ===\n";
    for (Book& b : library) {
        b.print();
    }

    return 0;
}