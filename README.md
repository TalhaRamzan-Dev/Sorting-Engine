# 🔍 Multi-Structure Search & Sort Engine (C++)

A **C++17 application** implementing and benchmarking multiple **sorting** and **searching** algorithms with performance analysis.
Designed for learning, experimentation, and comparison in **Data Structures & Algorithms (DSA)**.

---

## ✨ Features

### Sorting Algorithms (9)

* Merge, Quick, Heap, Insertion, Selection, Bubble, Shell, Counting, Radix

### Searching Algorithms (7)

* Linear, Binary, Interpolation, Exponential, Jump, Fibonacci, Hash (`unordered_set`)

### Data Generators

* Random, Sorted, Reverse Sorted, Nearly Sorted, Duplicate Values

### Performance Analysis

* Measures execution time in **microseconds (µs)**
* Validates correctness of results
* Generates detailed reports with success rates & averages

### Interactive Menu

* Run individual algorithms or compare all
* Generate new datasets
* View performance results and reports
* Run full benchmark tests

---

## 🛠️ Installation & Usage

### 1. Clone

```bash
git clone https://github.com/yourusername/SortingEngine.git
cd SortingEngine
```

### 2. Compile

```bash
g++ -std=c++17 SortingEngine.cpp -o SortingEngine
```

### 3. Run

```bash
./SortingEngine
```

---

## 📊 Sample Menu & Output

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

**Performance Example:**

```
Algorithm       Time (µs)   Success   Data Size
-----------------------------------------------
Merge Sort      1523        ✓         10000
Quick Sort      987         ✓         10000
Heap Sort       1722        ✓         10000
Bubble Sort     67219       ✓         10000
```

---

## 📂 Project Structure

```
SortingEngine.cpp   # All algorithms & interactive menu
README.md           # Documentation
```

