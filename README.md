````markdown
# 🔍 Multi-Structure Search & Sort Engine (C++)

A comprehensive C++ application that implements and benchmarks multiple **sorting** and **searching** algorithms with performance analysis.  
Designed for learning, comparison, and experimentation in **Data Structures & Algorithms (DSA)**.

---

## ✨ Features
- ✅ 9 Sorting Algorithms:
  - Merge Sort
  - Quick Sort
  - Heap Sort
  - Insertion Sort
  - Selection Sort
  - Bubble Sort
  - Shell Sort
  - Counting Sort
  - Radix Sort

- ✅ 7 Searching Algorithms:
  - Linear Search
  - Binary Search
  - Interpolation Search
  - Exponential Search
  - Jump Search
  - Fibonacci Search
  - Hash Search (optimized with `unordered_set`)

- ✅ Data Generators:
  - Random integers
  - Sorted integers
  - Reverse sorted integers
  - Nearly sorted integers
  - Duplicate values

- ✅ Performance Analyzer:
  - Measures execution time in **microseconds (µs)**
  - Validates correctness
  - Generates detailed reports with success rates & average times

- ✅ Interactive Menu:
  - Run individual algorithms
  - Compare all algorithms side by side
  - Generate new datasets
  - View performance results & reports
  - Run comprehensive benchmarks

---

## 🛠️ Installation & Usage

### 1. Clone the Repository
```bash
git clone https://github.com/yourusername/SortingEngine.git
cd SortingEngine
````
### 2. Compile
Use `g++` or any C++17+ compiler:
```bash
g++ -std=c++17 SortingEngine.cpp -o SortingEngine
```

### 3. Run

```bash
./SortingEngine
```

---

## 📊 Sample Output

```
============================================================
           MULTI-STRUCTURE SEARCH & SORT ENGINE - C++ (DSA)
============================================================
Current Data Size: 1000 elements
------------------------------------------------------------
1. Generate New Data
2. Sorting Algorithms
3. Search Algorithms
4. Run Comprehensive Benchmark
5. Display Current Data
6. Display Performance Results
7. Generate Performance Report
8. Clear Results
9. Exit
============================================================
```

Performance results example:

```
Algorithm                 Time (µs)       Success   Data Size
----------------------------------------------------------------
Merge Sort                1523            ✓         10000
Quick Sort                987             ✓         10000
Heap Sort                 1722            ✓         10000
Bubble Sort               67219           ✓         10000
============================================================
```

---

## 📂 Project Structure

```
SortingEngine.cpp    # Main source file with all algorithms and menu
README.md            # Project documentation
```

---

## 🚀 Future Improvements

* Add **visualization support** for sorting steps
* Export performance results to **CSV/JSON**
* Add more search/sort variants (e.g., TimSort, B-tree search)

---

## 📜 License

This project is licensed under the **MIT License** – free to use, modify, and distribute.

---

## 🙌 Acknowledgements

* Built for practicing **Data Structures & Algorithms**
* Uses C++17 STL for randomness, timing, and utilities

