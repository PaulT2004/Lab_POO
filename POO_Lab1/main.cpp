#include <iostream>
#include <cstring>

using namespace std;

const int MAX_STRING = 30;

class Book {
public:
    Book() {}
    Book(char title[], char writer[], char ISBN[]) {
        strcpy(this->title, title);
        strcpy(this->writer, writer);
        strcpy(this->ISBN, ISBN);
    }

    char* returnTitle(){
        return title;
    }

    void PrintBook() {
        cout << "Book: " << title << "\nWriter: " << writer << "\nISBN: " << ISBN << "\n" << endl;
    }

private:
    char title[MAX_STRING];
    char writer[MAX_STRING];
    char ISBN[MAX_STRING];
};

class Library {
private:
    Book library[MAX_STRING];
    int countBooks;

public:
    Library():countBooks(0) {}

    friend void PrintListBooks(Library& library);
    friend void AddBook(Library& library, Book& book);
    friend void RemoveBook(Library& library);
};

void PrintListBooks(Library& library) {
    if(library.countBooks==0) {
        cout << "Library empty" << endl;
    }
    else{
        for(int i=0;i<library.countBooks;i++) {
            library.library[i].PrintBook();
        }
    }
}

void AddBook(Library& library, Book& book) {
    library.library[library.countBooks] = book;
    library.countBooks++;
}

void RemoveBook(Library& library) {
    char searchBook[MAX_STRING];
    cout << "Insert the book title: ";
    cin >> searchBook;

    for (int i=0; i<library.countBooks; i++) {
        if (strcmp(library.library[i].returnTitle(), searchBook) == 0) {
            for (int j=i; j<library.countBooks-1; j++) {
                library.library[j]=library.library[j+1];
            }
            library.countBooks--;
            cout << "Book removed" << endl;
        }
    }
}

Book CreateBook() {
    char title[MAX_STRING];
    char writer[MAX_STRING];
    char ISBN[MAX_STRING];

    cout << "Enter the book title: ";
    cin >> title;
    cout << "Enter the writer's name: ";
    cin >> writer;
    cout << "Enter the ISBN: ";
    cin >> ISBN;

    return Book(title, writer, ISBN);
}

void menu(Library& library) {
    int menuNumber;

    cout << "1: Print the books\n2: Add a book\n3: Remove a book\n4: Quit" << endl;
    cin >> menuNumber;

    if(menuNumber==1){
        PrintListBooks(library);
        menu(library);
    }
    else if(menuNumber==2){
        Book newBook = CreateBook();
        AddBook(library, newBook);
        menu(library);
    }
    else if(menuNumber==3){
        RemoveBook(library);
        menu(library);
    }
    else if(menuNumber==4){
        //*ends*
    }
    else{
        cout << "You inserted another number\n" << endl;
        menu(library);
    }
}

int main() {
    Library library;

    menu(library);

    return 0;
}


