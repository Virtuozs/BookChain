#include "graph.hpp"
#include "hash_table.hpp"
#include <iostream>
#include <limits>
#include <iomanip>

// Sorting
void insertionSortByStock(std::vector<Book>& books, bool ascending = true){
    for (size_t i = 1; i < books.size(); ++i) {
        Book key = books[i];
        int j = i - 1;

        while (j >= 0 && (
            ascending ? books[j].getStock() > key.getStock()
                      : books[j].getStock() < key.getStock()
        )) {
            books[j + 1] = books[j];
            --j;
        }
        books[j + 1] = key;
    }
}

void insertionSortByPrice(std::vector<Book>& books, bool ascending = true){
        for (size_t i = 1; i < books.size(); ++i) {
        Book key = books[i];
        int j = i - 1;

        while (j >= 0 && (
            ascending ? books[j].getPrice() > key.getPrice()
                      : books[j].getPrice() < key.getPrice()
        )) {
            books[j + 1] = books[j];
            --j;
        }
        books[j + 1] = key;
    }
}

void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void addBook(HashTable& books) {
    std::string isbn, title, author, genre;
    int stock;
    double price;

    std::cout << "Enter ISBN: ";
    std::getline(std::cin, isbn);
    std::cout << "Enter Title: ";
    std::getline(std::cin, title);
    std::cout << "Enter Author: ";
    std::getline(std::cin, author);
    std::cout << "Enter Genre: ";
    std::getline(std::cin, genre);
    std::cout << "Enter Stock: ";
    std::cin >> stock;
    std::cout << "Enter Price: ";
    std::cin >> price;
    clearInput();

    books.insert(Book(isbn, title, author, genre, stock, price));
}

/// View Book Hash Table with Paginated View
void printTableHeader() {
    std::cout << std::left
              << std::setw(20) << "ISBN"
              << std::setw(25) << "Title"
              << std::setw(20) << "Author"
              << std::setw(15) << "Genre"
              << std::setw(8) << "Stock"
              << std::setw(10) << "Price"
              << "\n";
    std::cout << std::string(98, '-') << "\n";
}

void printBookRow(const Book& book) {
    std::cout << std::left
              << std::setw(20) << book.getIsbn()
              << std::setw(25) << book.getTitle()
              << std::setw(20) << book.getAuthor()
              << std::setw(15) << book.getGenre()
              << std::setw(8)  << book.getStock()
              << std::setw(10) << book.getPrice()
              << "\n";
}

bool displayPaginatedBooks(const std::vector<Book>& books, size_t perPage = 5) {
    size_t total = books.size();
    size_t pages = (total + perPage - 1) / perPage;
    size_t currentPage = 0;
    char command;

    do {
        system("clear"); // or "CLS" for Windows
        size_t start = currentPage * perPage;
        size_t end = std::min(start + perPage, total);

        std::cout << "Page " << (currentPage + 1) << " of " << pages << "\n\n";
        printTableHeader();
        for (size_t i = start; i < end; ++i) {
            printBookRow(books[i]);
        }

        std::cout << "\n[n] Next | [p] Prev | [c] Continue | [q] Cancel: ";
        std::cin >> command;
        command = std::tolower(command);

        if (command == 'n' && currentPage + 1 < pages) ++currentPage;
        else if (command == 'p' && currentPage > 0) --currentPage;
        else if (command == 'c') return true;
        else if (command == 'q') return false;

    } while (true);
}

void viewBooks(HashTable& books) {
    std::vector<Book> all = books.getAllBooks();
    if (all.empty()) {
        std::cout << "No books found.\n";
        return;
    }
    displayPaginatedBooks(all);
}

void deleteBook(HashTable& books) {
    std::vector<Book> all = books.getAllBooks();

    if (all.empty()) {
        std::cout << "No books available to delete.\n";
        return;
    }

    if (!displayPaginatedBooks(all)) {
        std::cout << "Delete cancelled.\n";
        return;
    }

    std::string isbn;
    std::cin.ignore();
    std::cout << "\nEnter ISBN to delete: ";
    std::getline(std::cin, isbn);
    

    if (books.erase(isbn)) {
        std::cout << "Book with ISBN " << isbn << " deleted successfully.\n";
    } else {
        std::cout << "Book with ISBN " << isbn << " not found.\n";
    }
}

void recommendBook(HashTable& books) {
    std::vector<Book> all = books.getAllBooks();

    if (all.empty()) {
        std::cout << "No books available to recommend from.\n";
        return;
    }

    if (!displayPaginatedBooks(all)) {
        std::cout << "Recommendation cancelled.\n";
        return;
    }

    std::string isbn;
    std::cin.ignore();
    std::cout << "\nEnter ISBN to get recommendations: ";
    std::getline(std::cin, isbn);

    BookGraph graph(books);
    graph.buildGraph();
    std::vector<Book> recs = graph.recommend(isbn);

    if (recs.empty()) {
        std::cout << "No recommendations found for ISBN: " << isbn << "\n";
    } else {
        std::cout << "\nRecommended books based on " << isbn << ":\n";
        displayPaginatedBooks(recs);
    }
}

void sortBooks(HashTable& books) {
    std::vector<Book> all = books.getAllBooks();

    if (all.empty()) {
        std::cout << "No books available to sort.\n";
        return;
    }

    std::cout << "\nSort books by:\n";
    std::cout << "1. Stock Ascending\n";
    std::cout << "2. Stock Descending\n";
    std::cout << "3. Price Ascending\n";
    std::cout << "4. Price Descending\n";
    std::cout << "Choose option (1-4): ";

    int option;
    std::cin >> option;
    std::cin.ignore();

    switch (option) {
        case 1:
            insertionSortByStock(all, true);
            break;
        case 2:
            insertionSortByStock(all, false);
            break;
        case 3:
            insertionSortByPrice(all, true);
            break;
        case 4:
            insertionSortByPrice(all, false);
            break;
        default:
            std::cout << "Invalid option.\n";
            return;
    }

    displayPaginatedBooks(all);
}

int main() {
    HashTable books;

    books.insert(Book("978-1-945209-05-5", "C++ Primer", "Stanley Lippman", "Programming", 10, 45.99));
    books.insert(Book("978-1-945219-05-5", "Effective C++", "Scott Meyers", "Programming", 5, 39.99));
    books.insert(Book("978-1-945999-05-5", "Dune", "Frank Herbert", "Sci-Fi", 3, 29.99));
    books.insert(Book("978-1-945249-05-5", "Foundation", "Isaac Asimov", "Sci-Fi", 4, 32.50));
    books.insert(Book("978-1-945539-05-5", "C++ Concurrency", "Anthony Williams", "Programming", 6, 49.99));
    books.insert(Book("978-1-945679-05-5", "Children of Dune", "Frank Herbert", "Sci-Fi", 2, 27.99));

    int choice;
    do {
        std::cout << "\n====== Book Manager ======\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Delete Book\n";
        std::cout << "3. View All Books\n";
        std::cout << "4. Recommend Based on Book\n";
        std::cout << "5. Sort Books (Price/Stock)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose option: ";
        std::cin >> choice;
        clearInput();

        switch (choice) {
            case 1: addBook(books); break;
            case 2: deleteBook(books); break;
            case 3: viewBooks(books); break;
            case 4: recommendBook(books); break;
            case 5: sortBooks(books); break;
            case 0: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n"; break;
        }

    } while (choice != 0);

    return 0;
}
