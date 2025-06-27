#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "hash_table.hpp"
#include <unordered_map>
#include <vector>
#include <string>

class BookGraph {
private:
    HashTable& bookTable;

    // Weighted adjacency list: ISBN -> (neighbor ISBN -> weight)
    std::unordered_map<std::string, std::unordered_map<std::string, int>> adjList;

    // Compute similarity weight between two books
    int computeSimilarityWeight(const Book& a, const Book& b) const;

public:
    BookGraph(HashTable& table);

    // Build graph by connecting similar books
    void buildGraph();

    // Add an edge between two ISBNs with given weight
    void addEdge(const std::string& isbn1, const std::string& isbn2, int weight);

    // Recommend similar books based on weighted similarity
    std::vector<Book> recommend(const std::string& isbn, int limit = 5) const;

    // Display the full graph (for debug/visualization)
    void displayGraph() const;
};

#endif
