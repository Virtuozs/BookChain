#ifndef HASH_TABLE
#define HASH_TABLE

#include "book.hpp"
#include <vector>
#include <list>
#include <functional>

class HashTable {
    private:
        std::vector<std::list<Book>> table;
        size_t capacity, count;
        const double max_load = 0.5;

        size_t hash_function(const std::string &key) const;

        void rehash(size_t new_capacity);

    public:
        HashTable(size_t initial = 25);

        void insert(const Book &book);

        Book* find(const std::string &isbn);

        void displayAll() const;

        size_t getCapacity() const;
        
        const std::list<Book>& getBucket(size_t index) const;

        bool erase(const std::string &isbn);

        std::vector<Book> getAllBooks() const;
};

#endif