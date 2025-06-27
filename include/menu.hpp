#ifndef MENU
#define MENU

#include "book_manager.hpp"

class Menu {
private:
    BookManager& bookManager;

    void addBook();
    void deleteBook();
    void viewBook();
    void viewAllBooks();
    void sortBooksByPrice();
    void sortBooksByStock();

public:
    Menu(BookManager& manager);
    void show();
};

#endif
