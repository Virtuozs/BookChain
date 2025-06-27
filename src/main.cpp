#include "graph.hpp"
#include "hash_table.hpp"
#include <iostream>

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

int main() {
    HashTable books;

    books.insert(Book("001", "C++ Primer", "Stanley Lippman", "Programming", 10, 45.99));
    books.insert(Book("002", "Effective C++", "Scott Meyers", "Programming", 5, 39.99));
    books.insert(Book("003", "Dune", "Frank Herbert", "Sci-Fi", 3, 29.99));
    books.insert(Book("004", "Foundation", "Isaac Asimov", "Sci-Fi", 4, 32.50));
    books.insert(Book("005", "C++ Concurrency", "Anthony Williams", "Programming", 6, 49.99));
    books.insert(Book("006", "Children of Dune", "Frank Herbert", "Sci-Fi", 2, 27.99));

    BookGraph graph(books);
    graph.buildGraph();

    std::cout << "\n--- Book Graph ---\n";
    graph.displayGraph();

    std::cout << "\n--- Recommendations for ISBN '003' (Dune) ---\n";
    for (const Book& rec : graph.recommend("003")) {
        rec.display();
        std::cout << "-----\n";
    }

    return 0;
}
