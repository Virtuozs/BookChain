#include "book.hpp"
#include <iostream>

Book::Book(std::string isbn, std::string title, std::string author, std::string genre, int stock, double price)
    : isbn(std::move(isbn)), title(std::move(title)), author(std::move(author)), genre(std::move(genre)), stock(stock), price(price) {}

void Book::display() const {
    std::cout << "ISBN: " << isbn << "\nTitle: " << title
              << "\nAuthor: " << author << "\nGenre: " << genre
              << "\nStock: " << stock << "\nPrice: $" << price << "\n";
}

std::string Book::getIsbn() const {
    return isbn;
}

std::string Book::getTitle() const {
    return title;
}

std::string Book::getGenre() const {
    return genre;
}

std::string Book::getAuthor() const {
    return author;
}

int Book::getStock() const {
    return stock;
}

double Book::getPrice() const {
    return price;
}