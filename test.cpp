#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Book {
private:
    std::string title;
    std::string author;
    std::string isbn;
    bool checkedOut;

public:
    Book(std::string t, std::string a, std::string i)
        : title(t), author(a), isbn(i), checkedOut(false) {}

    void checkOut() {
        checkedOut = true;
    }

    void checkIn() {
        checkedOut = false;
    }

    bool isCheckedOut() const {
        return checkedOut;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    std::string getISBN() const {
        return isbn;
    }

    void display() const {
        std::cout << "Title: " << title << ", Author: " << author
                  << ", ISBN: " << isbn
                  << ", Status: " << (checkedOut ? "Checked Out" : "Available") << std::endl;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayBooks() const {
        for (const auto& book : books) {
            book.display();
        }
    }

    Book* findBookByISBN(const std::string& isbn) {
        for (auto& book : books) {
            if (book.getISBN() == isbn) {
                return &book;
            }
        }
        return nullptr;
    }

    void checkOutBook(const std::string& isbn) {
        Book* book = findBookByISBN(isbn);
        if (book && !book->isCheckedOut()) {
            book->checkOut();
            std::cout << "You have checked out: " << book->getTitle() << std::endl;
        } else {
            std::cout << "Book is either not found or already checked out." << std::endl;
        }
    }

    void checkInBook(const std::string& isbn) {
        Book* book = findBookByISBN(isbn);
        if (book && book->isCheckedOut()) {
            book->checkIn();
            std::cout << "You have checked in: " << book->getTitle() << std::endl;
        } else {
            std::cout << "Book is either not found or already available." << std::endl;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        for (const auto& book : books) {
            outFile << book.getTitle() << "|" << book.getAuthor() << "|"
                    << book.getISBN() << "|" << book.isCheckedOut() << std::endl;
        }
        outFile.close();
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        std::string line;
        while (std::getline(inFile, line)) {
            std::string title, author, isbn;
            bool checkedOut;
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);

            title = line.substr(0, pos1);
            author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            isbn = line.substr(pos2 + 1, pos3 - pos2 - 1);
            checkedOut = line.substr(pos3 + 1) == "1";

            Book book(title, author, isbn);
            if (checkedOut) {
                book.checkOut();
            }
            addBook(book);
        }
        inFile.close();
    }
};

int main() {
    Library library;

    // Load existing books from a file
    library.loadFromFile("library.txt");

    // Sample user interface
    int choice;
    do {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Display Books\n";
        std::cout << "3. Check Out Book\n";
        std::cout << "4. Check In Book\n";
        std::cout << "5. Save and Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string title, author, isbn;
            std::cout << "Enter title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter author: ";
            std::getline(std::cin, author);
            std::cout << "Enter ISBN: ";
            std::getline(std::cin, isbn);
            library.addBook(Book(title, author, isbn));
        } else if (choice == 2) {
            library.displayBooks();
        } else if (choice == 3) {
            std::string isbn;
            std::cout << "Enter ISBN of book to check out: ";
            std::cin >> isbn;
            library.checkOutBook(isbn);
        } else if (choice == 4) {
            std::string isbn;
            std::cout << "Enter ISBN of book to check in: ";
            std::cin >> isbn;
            library.checkInBook(isbn);
        } else if (choice == 5) {
            library.saveToFile("library.txt");
            std::cout << "Library data saved. Exiting." << std::endl;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 5);

    return 0;
}

