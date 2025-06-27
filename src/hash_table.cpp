#include "hash_table.hpp"
#include <iostream>

HashTable::HashTable(size_t initial)
    : table(initial), capacity(initial), count(0) {}

/// DJB2 Hash (http://www.cse.yorku.ca/~oz/hash.html)
size_t HashTable::hash_function(const std::string &key) const {
    size_t hash = 5381;
    for (char c : key) {
        hash = ((hash << 5) + hash) + static_cast<unsigned char>(c); // hash * 33 + c
    }
    return hash % capacity;
}

void HashTable::rehash(size_t new_capacity) {
    std::vector<std::list<Book>> old_table = std::move(table);
    table.clear();
    table.resize(new_capacity);
    capacity = new_capacity;
    count = 0;

    for (auto &bucket : old_table) {
        for (auto &book : bucket) {
            insert(book);
        }
    }
}

void HashTable::insert(const Book &book) {
    if ((count + 1.0) / capacity > max_load) {
        rehash(capacity * 2);
    }

    size_t idx = hash_function(book.getIsbn());

    // DEBUG to Check hash distribution
    // std::cout << "Inserting ISBN: " << book.getIsbn() << " to bucket " << idx << "\n";

    for (const auto &b : table[idx]) {
        if (b.getIsbn() == book.getIsbn()) {
            std::cout << "Insert rejected: duplicate ISBN \"" << book.getIsbn() << "\"\n";
            return;
        }
    }

    table[idx].push_front(book);
    ++count;
}

bool HashTable::erase(const std::string &isbn) {
    size_t idx = hash_function(isbn);
    auto &bucket = table[idx];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->getIsbn() == isbn) {
            bucket.erase(it);
            --count;

            if (capacity > 20 && (count / (double)capacity) < (max_load / 4.0)) {
                rehash(capacity / 2);
            }
            return true;
        }
    }
    return false;
}

Book* HashTable::find(const std::string &isbn) {
    size_t idx = hash_function(isbn);
    for (auto &b : table[idx]) {
        if (b.getIsbn() == isbn)
            return &b;
    }
    return nullptr;
}

void HashTable::displayAll() const {
    for (size_t i = 0; i < table.size(); ++i) {
        if (!table[i].empty()) {
            std::cout << "Bucket [" << i << "]:" << std::endl;
            for (const auto &book : table[i]) {
                book.display();
                std::cout << "------------------\n";
            }
        }
    }
}

size_t HashTable::getCapacity() const {
    return capacity;
}

const std::list<Book>& HashTable::getBucket(size_t index) const {
    return table[index];
}

std::vector<Book> HashTable::getAllBooks() const {
    std::vector<Book> result;
    for (const auto &bucket : table) {
        for (const auto &book : bucket) {
            result.push_back(book);
        }
    }
    return result;
}