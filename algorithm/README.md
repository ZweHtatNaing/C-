# Algorithms in C++

A beginner-friendly collection of common algorithms implemented in C++.
Each file includes line-by-line comments to help you understand how the algorithm works.

---

## Files Overview

| File | Algorithm | Category | Time Complexity |
|------|-----------|----------|----------------|
| `bubble_sort.cpp` | Bubble Sort | Sorting | O(n²) |
| `selection_sort.cpp` | Selection Sort | Sorting | O(n²) |
| `insertion_sort.cpp` | Insertion Sort | Sorting | O(n²) |
| `merge_sort.cpp` | Merge Sort | Sorting | O(n log n) |
| `quick_sort.cpp` | Quick Sort | Sorting | O(n log n) avg |
| `counting_sort.cpp` | Counting Sort | Sorting | O(n + k) |
| `linear_search.cpp` | Linear Search | Searching | O(n) |
| `binary_search.cpp` | Binary Search | Searching | O(log n) |
| `factorial.cpp` | Factorial | Recursion | O(n) |
| `fibonacci.cpp` | Fibonacci | Recursion / DP | O(n) |

---

## Sorting Algorithms

### Bubble Sort — `bubble_sort.cpp`
Repeatedly compares and swaps adjacent elements until the array is sorted.
The largest element "bubbles up" to the end on each pass.
- **Best for:** Learning the concept of sorting
- **Avoid when:** Working with large datasets

### Selection Sort — `selection_sort.cpp`
Divides the array into a sorted and unsorted part.
On each pass, finds the minimum element in the unsorted part and places it at the end of the sorted part.
- **Best for:** Simple implementation with minimal swaps
- **Avoid when:** Working with large datasets

### Insertion Sort — `insertion_sort.cpp`
Builds the sorted array one element at a time, inserting each new element into its correct position.
Similar to how you sort playing cards in your hand.
- **Best for:** Small arrays or nearly sorted data
- **Avoid when:** Working with large, random datasets

### Merge Sort — `merge_sort.cpp`
A divide-and-conquer algorithm. Splits the array in half recursively, sorts each half, then merges them back together in sorted order.
- **Best for:** Large datasets, guaranteed O(n log n) performance
- **Note:** Uses extra memory for the temporary arrays

### Quick Sort — `quick_sort.cpp`
Picks a "pivot" element and partitions the array so smaller elements go left and larger go right. Recursively sorts each side.
- **Best for:** General-purpose sorting, very fast in practice
- **Note:** Worst case is O(n²) if the pivot is always the smallest/largest element

### Counting Sort — `counting_sort.cpp`
Counts occurrences of each value, then rebuilds the sorted array from the counts.
- **Best for:** Integers with a small, known range of values
- **Avoid when:** Values are floats, negative, or have a very large range

---

## Searching Algorithms

### Linear Search — `linear_search.cpp`
Checks each element one by one from left to right until the target is found.
- **Best for:** Small or unsorted arrays
- **Avoid when:** The array is large (use Binary Search instead)

### Binary Search — `binary_search.cpp`
Repeatedly cuts the search range in half by comparing the target with the middle element.
**Requires a sorted array.**
- **Best for:** Large sorted arrays
- **Much faster** than Linear Search for large data

---

## Recursion

### Factorial — `factorial.cpp`
Calculates `n! = n * (n-1) * ... * 1` using recursion.
A classic example of how a function can call itself with a simpler input.

### Fibonacci — `fibonacci.cpp`
Computes Fibonacci numbers `(0, 1, 1, 2, 3, 5, 8, ...)` using an iterative loop.
Each number is the sum of the two before it.

---

## How to Compile and Run

Make sure you have `g++` installed. Then in your terminal:

```bash
g++ bubble_sort.cpp -o bubble_sort
./bubble_sort
```

Replace `bubble_sort` with the name of any file you want to run.

---

## Key Concepts for Beginners

| Term | Meaning |
|------|---------|
| **Time Complexity** | How fast an algorithm runs as input grows |
| **O(n)** | Time grows linearly with input size |
| **O(n²)** | Time grows quadratically — gets slow for large data |
| **O(n log n)** | Very efficient — most fast sorting algorithms are here |
| **O(log n)** | Extremely fast — cuts the problem in half each step |
| **Recursion** | A function that calls itself with a smaller version of the problem |
| **Divide and Conquer** | Split the problem into smaller parts, solve each, combine results |
