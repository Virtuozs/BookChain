#include "graph.hpp"
#include <iostream>
#include <algorithm>

BookGraph::BookGraph(HashTable& table) : bookTable(table) {}

int BookGraph::computeSimilarityWeight(const Book& a, const Book& b) const {
    int weight = 0;
    if (a.getAuthor() == b.getAuthor()) weight += 2;
    if (a.getGenre() == b.getGenre()) weight += 1;
    return weight;
}

void BookGraph::addEdge(const std::string& isbn1, const std::string& isbn2, int weight) {
    if (isbn1 == isbn2 || weight <= 0) return;
    adjList[isbn1][isbn2] = weight;
    adjList[isbn2][isbn1] = weight; // undirected graph
}

void BookGraph::buildGraph() {
    std::vector<Book> books = bookTable.getAllBooks();

    for (size_t i = 0; i < books.size(); ++i) {
        for (size_t j = i + 1; j < books.size(); ++j) {
            const Book& b1 = books[i];
            const Book& b2 = books[j];

            int weight = computeSimilarityWeight(b1, b2);
            if (weight > 0) {
                addEdge(b1.getIsbn(), b2.getIsbn(), weight);
            }
        }
    }
}

std::vector<Book> BookGraph::recommend(const std::string& isbn, int limit) const {
    std::vector<std::pair<int, Book>> scoredBooks;

    auto it = adjList.find(isbn);
    if (it == adjList.end()) return {};

    for (const auto& [neighborIsbn, weight] : it->second) {
        Book* neighbor = bookTable.find(neighborIsbn);
        if (neighbor != nullptr) {
            scoredBooks.emplace_back(weight, *neighbor);
        }
    }

    std::sort(scoredBooks.begin(), scoredBooks.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    std::vector<Book> result;
    for (size_t i = 0; i < scoredBooks.size() && result.size() < static_cast<size_t>(limit); ++i) {
        result.push_back(scoredBooks[i].second);
    }

    return result;
}

void BookGraph::displayGraph() const {
    for (const auto& [isbn, neighbors] : adjList) {
        std::cout << "Book ISBN: " << isbn << " connections:\n";
        for (const auto& [neighborIsbn, weight] : neighbors) {
            Book* b = bookTable.find(neighborIsbn);
            if (b) {
                std::cout << "  -> " << neighborIsbn
                          << " (" << b->getTitle() << "), weight: " << weight << "\n";
            }
        }
    }
}
