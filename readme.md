# 📚 BookChain — Book Distribution & Recommendation System

A C++ terminal-based book management application that allows users to manage books efficiently using custom data structures including a **hash table**, **graph-based recommendation**, and **insertion sort**.

---

## 🚀 Features

- ✅ Add, view, and delete books  
- 📦 Efficient hash table storage with rehashing  
- 📚 Graph-based book recommendations (by author & genre similarity)  
- 🔢 Sorting by **stock** or **price** (ascending/descending)  
- 📄 Paginated terminal output for easier navigation  
- ✅ Unit tested with Catch2  

---

## 🧠 Data Structures Used

### 1. **Hash Table**
- Used for storing and retrieving books using ISBN as the key.
- Implements **DJB2 hashing** and dynamic **rehashing** based on load factor.
- Efficient average-case operations:  
  `Insert / Find / Delete` → **O(1)**  
  Worst-case → **O(n)** (if heavily collided)

### 2. **Graph (Adjacency List)**
- Builds a similarity graph between books.
- Uses **weighted undirected edges** based on:
  - +2 if same author
  - +1 if same genre
- Enables recommendation using edge weight sorting.

### 3. **Sorting (Insertion Sort)**
- Sorts book lists by **stock** or **price**.
- Supports both ascending and descending order.
- In-place, stable sorting algorithm.  
  Time complexity → **O(n²)**, suitable for small datasets.

---

## 🧱 Build Instructions

### 🛠 Requirements
- C++17 compiler (e.g. `g++`, `clang++`)
- Terminal access (Linux/macOS/Windows)

### 🔧 Build & Run

```bash
make run
```

### 🧹 Clean Build Files

```bash
make clean
```

---

## 📁 Project Structure

```
.
├── include/
│   ├── book.hpp
│   ├── graph.hpp
│   └── hash_table.hpp
│   └── menu.hpp
├── src/
│   ├── book.cpp
│   ├── graph.cpp
│   └── hash_table.cpp
│   └── main.cpp
│   └── menu.cpp
├── makefile
└── readme.md
```

---

## 📸 Sample Terminal UI

```
====== Book Manager ======
1. Add Book
2. Delete Book
3. View All Books
4. Recommend Based on Book
5. Sort Books (Price/Stock)
0. Exit
Choose option:
```

---

## 🤝 Contributions

Pull requests and suggestions are welcome!  
Want to add JSON export, more complex graphs, or a GUI?  
Feel free to fork this project and build on top of it!

---
