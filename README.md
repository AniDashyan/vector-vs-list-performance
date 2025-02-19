# vector-vs-list-performance
# Performance Comparison of `std::vector` and `std::list` for Insertion and Deletion Operations

## Table of Contents
1. [Introduction](#1-introduction)
2. [Build & Run](#2-build--run)
   - [Requirements](#requirements)
   - [Steps to Build and Run](#steps-to-build-and-run)
3. [Example Output](#3-example-output)
   - [Interpretation of the Output](#interpretation-of-the-output)
4. [Why is `std::vector` Faster?](#4-why-is-stdvector-faster)
   - [4.1 Memory Layout](#41-memory-layout)
   - [4.2 Cache Prefetching](#42-cache-prefetching)
   - [4.3 Shifting Elements in `std::vector`](#43-shifting-elements-in-stdvector)
   - [4.4 Complexity Considerations](#44-complexity-considerations)
5. [Conclusion](#5-conclusion)

---

## 1. Introduction

This program provides a performance comparison between two fundamental C++ container types, `std::vector` and `std::list`. Both containers serve different purposes and have different internal structures, making them suitable for various use cases.

The code compares the time taken to perform two key operations:
- **Insertion**: Random integers are inserted in a sorted order.
- **Deletion**: Elements are deleted from random positions in the containers.

The goal is to demonstrate which container is faster for these operations, particularly when a large number of elements are involved (`N = 50,000` by default). The results are displayed in milliseconds, and the program also calculates how much faster one container is compared to the other.

### Containers Overview
- **`std::vector`**: A dynamic array that stores elements in contiguous memory locations. It supports efficient access by index but has slower insertions/deletions in the middle of the array since all subsequent elements need to be shifted.
- **`std::list`**: A doubly linked list where each element (node) contains pointers to the previous and next elements. This allows for efficient insertions/deletions at arbitrary positions, but accessing elements by index requires linear traversal.

This program shows that despite `std::list` being optimized for insertions and deletions, `std::vector` is often faster due to memory locality and cache prefetching.

---

## 2. Build & Run

### Requirements
- **C++ compiler**: A modern C++ compiler that supports the C++11 standard or later (e.g., GCC, Clang, or MSVC).
- **Git**: To clone the repository (optional if you have the source code)

### Steps

1. **Clone the Repository and Navigate to the Directory**:
   ```bash
   git clone https://github.com/AniDashyan/vector-vs-list-performance.git && cd vector-vs-list-performance
   ```

2. **Compile the Code**:
   ```bash
   g++ -std=c++17 -O2 main.cpp -o perf
   ```

3. **Run the Program in Terninal**: 
   ```bash
   ./perf
   ```

The output will compare `std::vector` and `std::list` performance for insertion and deletion operations.

---

## 3. Example Output

After running the program with `N = 50,000`, you will see an output similar to this:

```
Vector vs List performance when N= 50000

+------------------+------------+
| Operation        | Time (ms)  |
+------------------+------------+
| Vector Insertion |        274 |
| Vector Deletion  |        717 |
| Vector Total     |        991 |
+------------------+------------+
| List Insertion   |       4295 |
| List Deletion    |       4439 |
| List Total       |       8734 |
+------------------+------------+
| Vector is Faster |          8x|
+------------------+------------+
```

### Interpretation of the Output:

1. **Vector Insertion (274 ms)**: Inserting 50,000 random integers into a sorted vector took 274 milliseconds. Despite the need to shift elements during insertion, the contiguous memory layout and cache efficiency make `std::vector` faster.

2. **Vector Deletion (717 ms)**: Deleting all elements from the vector took 717 milliseconds. While vector deletions require shifting elements, the total time remains relatively low due to cache efficiency.

3. **Vector Total (991 ms)**: The total time for both insertion and deletion operations in the vector was 991 milliseconds.

4. **List Insertion (4295 ms)**: Inserting the same 50,000 random integers into a sorted list took significantly longer (4295 milliseconds). The scattered memory layout of `std::list` and pointer traversals reduce insertion efficiency.

5. **List Deletion (4439 ms)**: Deleting elements from the list took 4439 milliseconds, which is much slower than `std::vector`, mainly due to the overhead of navigating pointers between nodes in the list.

6. **List Total (8734 ms)**: The combined time for both insertion and deletion in `std::list` was 8734 milliseconds, significantly longer than `std::vector`.

7. **Vector is Faster (8x)**: The vector is 8 times faster overall compared to the list. This highlights the importance of memory layout and cache prefetching, as `std::vector` benefits from contiguous memory storage, while `std::list` suffers from pointer indirection and scattered memory.
---

## 4. Why is `std::vector` Faster?

While it might seem that `std::list` should be faster for insertions and deletions (because it doesn't require shifting elements), `std::vector` often outperforms `std::list` due to several important factors:

### 4.1 Memory Layout
- **Contiguous Memory in `std::vector`**: `std::vector` stores its elements in contiguous memory blocks. This allows for faster access to elements because when the processor loads one element into the cache, it also loads nearby elements. This behavior, known as **cache locality**, improves access speed dramatically, especially for large containers.
  
- **Scattered Memory in `std::list`**: `std::list`, on the other hand, stores elements in nodes that are scattered throughout memory. Each node points to the next and previous node. This means that accessing or modifying elements involves following pointers, which can cause cache misses and slow down performance. The lack of **contiguous memory** reduces the efficiency of `std::list`.

### 4.2 Cache Prefetching
- **Prefetching**: Modern CPUs are designed to predict which memory locations will be needed next and load them into the cache ahead of time. This process, called **prefetching**, works well with containers like `std::vector` because the elements are stored contiguously. As a result, when accessing an element in a vector, nearby elements are often already in the cache, making access faster.
  
- **`std::list` Prefetching Inefficiency**: Prefetching doesn't work well with `std::list` because its elements are not stored contiguously in memory. The processor cannot predict where the next element is located, leading to more cache misses and slower performance.

### 4.3 Shifting Elements in `std::vector`
- One potential downside of `std::vector` is that when elements are inserted or deleted in the middle, it may require shifting the elements after the insertion or deletion point. This could seem like a major overhead.
  
- However, even with this overhead, the contiguous memory layout and efficient cache usage make `std::vector` perform better in many cases than `std::list`, which has to follow pointers and cannot take advantage of cache locality.

### 4.4 Complexity Considerations
- **Insertion in `std::vector`**: Inserting into a sorted vector involves searching for the correct position (O(n) complexity) and then shifting elements to make space. However, the actual insertion into the contiguous memory is efficient.
  
- **Insertion in `std::list`**: Inserting into a sorted list involves finding the correct position (O(n) complexity), but once the position is found, the insertion itself is O(1) since elements don’t need to be shifted. Despite this, the scattered memory layout and pointer traversal negate the theoretical advantage.

---

## 5. Conclusion

While `std::list` is designed for efficient insertions and deletions, it is often outperformed by `std::vector` in practice for the following reasons:
- `std::vector` benefits from **contiguous memory layout** and **cache prefetching**.
- `std::list` suffers from **pointer indirection** and **cache misses** due to its scattered memory layout.

For large datasets, the performance of `std::vector` is generally superior to that of `std::list`, even for insertion and deletion operations, making `std::vector` the preferred choice in many cases where performance is critical.
