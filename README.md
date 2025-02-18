# Cache Effect on Container Performance

This repository contains a simple program that compares the performance of `std::vector` and `std::list` when performing sorted insertions and random deletions. The goal is to explore how the different underlying memory structures of these containers affect performance, particularly in terms of CPU cache efficiency.

## Problem Statement

The program compares the performance of `std::vector` and `std::list` when inserting and deleting elements while keeping the container sorted.  

### Steps:  
1. **Insertion:**  
   - Random integers are generated and inserted into both a `std::vector` and a `std::list` while maintaining sorted order.  

2. **Deletion:**  
   - A random index is generated, and the element at that index is removed.  
   - To ensure fair comparison, the element in both `std::vector` and `std::list` is found through linear iteration before removal, avoiding direct indexing in the vector.  

All algorithms are implemented with linear time complexity to maintain a fair comparison, ensuring that std::vector does not gain an advantage due to direct indexing during element removal.

## Example

Here is an example of how the code works:

### Output:
```
Insertion Time: Vector = 867.639ms, List = 1557.21ms
Deletion Time: Vector = 192.868ms, List = 820.498ms
Vector is 4.25419 times faster than List in total operations.
```

This output shows that for both insertions and deletions, the `std::vector` container performs better than `std::list`.

## Explanation of Results

In this code, we compare the performance of `std::vector` and `std::list` when performing sorted insertions and random deletions. The primary reasons for the observed performance differences are:

### 1. CPU Caches

The CPU cache plays a crucial role in the performance of programs, especially when accessing memory. Modern processors have multiple levels of cache (L1, L2, L3) that are much faster than main memory (RAM). These caches store copies of frequently accessed data to minimize the time it takes to retrieve it. 

- **Vector**: `std::vector` stores its elements contiguously in memory, meaning that when the CPU accesses an element, the next element is very close in memory. This allows for efficient caching because the CPU can load several consecutive elements into the cache at once. Since `std::vector` is cache-friendly, operations on vectors tend to be faster, as the CPU can make good use of the cache.

- **List**: On the other hand, `std::list` uses a doubly linked list structure where each element (node) is stored separately in memory. When the CPU needs to access the next element, it has to jump to a completely different location in memory, resulting in poor cache locality. This is less efficient, as the CPU cache is less effective when it cannot preload multiple elements in a single fetch.

### 2. Cache Line

A **cache line** is a small, fixed-size chunk of memory that the CPU fetches into the cache in one operation. The size of a cache line typically ranges from 32 to 128 bytes, depending on the CPU architecture. When accessing memory, the CPU fetches a whole cache line, not just a single byte or word. 

- **Vector**: Because `std::vector` elements are stored contiguously, multiple adjacent elements often fit into a single cache line. As a result, when the CPU loads an element from the vector, it may also load nearby elements into the cache, which can be reused during future accesses. This maximizes the efficiency of the cache and reduces memory access time.

- **List**: In `std::list`, each element is a separate node, often scattered across different locations in memory. As the CPU accesses a node, it may not benefit from loading nearby elements into the cache, because the next element is likely to be located far away in memory. This results in cache misses and inefficient memory access patterns, which slow down the program.

### 3. Prefetching

**Prefetching** is a technique used by modern CPUs to improve memory access speed. The CPU tries to predict which memory locations it will need next and preemptively loads them into the cache before they are actually needed. This reduces the time spent waiting for data to be fetched from slower main memory.

- **Vector**: Since the elements in a `std::vector` are stored contiguously, the CPU can predict the next memory location to access with high accuracy. This allows the CPU to preload adjacent elements into the cache before they are requested, improving performance. 

- **List**: With `std::list`, each node is typically scattered in memory. The CPU's prefetching mechanism struggles to predict which node will be accessed next because the memory locations are not sequential. This results in poor prefetching efficiency, as the CPU may not preemptively load the next required node into the cache, leading to slower memory access times.

### Why Does This Happen?

- **Cache Locality**: Vectors benefit from contiguous memory storage, meaning that adjacent elements are stored near each other, which improves cache efficiency. Lists suffer from poor cache locality due to scattered memory locations for each element.
  
- **Cache Line Efficiency**: Vectors make better use of cache lines by storing elements next to each other, allowing the CPU to load several elements in a single fetch. Lists, with scattered elements, can't take full advantage of cache lines.
  
- **Prefetching Accuracy**: Vectors enable the CPU to accurately predict the next memory access location, improving prefetching. Lists, on the other hand, have unpredictable memory access patterns, which makes prefetching less effective.

---

## How to Compile and Run the Code

1. **Install a C++ Compiler:**
   - If you're using Linux or macOS, you can install `g++` by running:
     ```bash
     sudo apt install g++
     ```
   - On Windows, you can use MinGW or Microsoft Visual Studio.

2. **Clone the repository:**
   If you haven't cloned the repository yet, do so by running:
   ```bash
   git clone https://github.com/LyudmilaKostanyan/vector-vs-list-performance.git
   cd vector-vs-list-performance
   ```

3. **Compile the code:**
   Once you're in the project directory, compile the code with:
   ```bash
   g++ -o benchmark main.cpp
   ```

4. **Run the compiled executable:**
   After compiling, you can run the program:
   ```bash
   ./benchmark
   ```

5. **View the Results:**
   The program will output the performance comparison between `std::vector` and `std::list` for sorted insertions and random deletions.
