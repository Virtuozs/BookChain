#ifndef BOOK_HPP
#define BOOK_HPP
#include <string>

class Book {
    private:
        std::string isbn;
        std::string title;
        std::string author;
        std::string genre;
        int stock;
        double price;

    public:
        Book(std::string isbn, std::string title, std::string author, std::string genre, int stock, double price);

        std::string getIsbn() const;
        std::string getTitle() const;
        std::string getGenre() const;
        std::string getAuthor() const;
        int getStock() const;
        double getPrice() const;

        bool operator==(const Book &other) const { return isbn == other.isbn; }
        void display() const;
};

#endif
