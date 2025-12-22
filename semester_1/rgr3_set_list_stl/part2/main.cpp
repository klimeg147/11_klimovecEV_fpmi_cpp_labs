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
        cout << "УДК: " << udk << "\n";
        cout << "Авторы: ";
        for (const Author& a : authors) {
            cout << a.surname << " ";
        }
        cout << "\n";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

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

        cout << "Загружено " << library.size() << " книг\n";
        file.close();
    }
    else {
        cout << "Файл books.txt не найден\n";
    }

    cout << "\nВсе книги (отсортированы по названию)\n";
    for (Book& b : library) {
        b.print();
    }

    cout << "\n=== Добавление новой книги ===\n";
    Book newBook;

    cout << "Введите УДК: ";
    cin >> newBook.udk;

    cout << "Введите название: ";
    cin.ignore();
    getline(cin, newBook.title);

    cout << "Введите год: ";
    cin >> newBook.year;

    int n;
    cout << "Сколько авторов? ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        Author a;
        cout << "Фамилия автора " << i + 1 << ": ";
        cin >> a.surname;
        newBook.authors.insert(a);
    }

    auto it = library.begin();
    while (it != library.end() && it->title < newBook.title) {
        it++;
    }
    library.insert(it, newBook);

    cout << "\n=== Все книги после добавления ===\n";
    for (Book& b : library) {
        b.print();
    }

    cout << "\n=== Удаление книги ===\n";
    string delTitle;
    cout << "Введите название книги для удаления: ";
    cin.ignore();
    getline(cin, delTitle);

    for (auto it = library.begin(); it != library.end(); it++) {
        if (it->title == delTitle) {
            library.erase(it);
            cout << "Книга удалена\n";
            break;
        }
    }

    cout << "\n=== Поиск книг по автору ===\n";
    string authorSurname;
    cout << "Введите фамилию автора: ";
    cin >> authorSurname;

    cout << "Книги автора " << authorSurname << ":\n";
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
        cout << "Книги не найдены\n";
    }

    cout << "\n=== Добавление автора к книге ===\n";
    string bookTitle;
    cout << "Введите название книги: ";
    cin.ignore();
    getline(cin, bookTitle);

    for (Book& b : library) {
        if (b.title == bookTitle) {
            Author newAuthor;
            cout << "Введите фамилию нового автора: ";
            cin >> newAuthor.surname;
            b.authors.insert(newAuthor);
            cout << "Автор добавлен\n";
            cout << "Обновленная информация о книге:\n";
            b.print();
            break;
        }
    }

    cout << "\n=== Удаление автора из книги ===\n";
    cout << "Введите название книги: ";
    cin.ignore();
    getline(cin, bookTitle);

    string delAuthor;
    cout << "Введите фамилию автора для удаления: ";
    cin >> delAuthor;

    for (Book& b : library) {
        if (b.title == bookTitle) {
            for (auto it = b.authors.begin(); it != b.authors.end(); it++) {
                if (it->surname == delAuthor) {
                    b.authors.erase(it);
                    cout << "Автор удален\n";
                    cout << "Обновленная информация о книге:\n";
                    b.print();
                    break;
                }
            }
            break;
        }
    }

    cout << "\n=== Финальный список книг ===\n";
    for (Book& b : library) {
        b.print();
    }

    return 0;
}