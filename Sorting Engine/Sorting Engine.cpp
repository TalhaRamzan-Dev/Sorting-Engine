#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <chrono>
#include <random>
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <unordered_set>

// ============================================================================
// SORTING ALGORITHMS
// ============================================================================

class SortingAlgorithms {
public:
    static void mergeSort(std::vector<int>& arr) {
        if (arr.size() <= 1) return;
        mergeSortHelper(arr, 0, static_cast<int>(arr.size() - 1));
    }

    static void quickSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        quickSortHelper(arr, 0, static_cast<int>(arr.size() - 1));
    }

    static void heapSort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            std::swap(arr[0], arr[i]);
            heapify(arr, i, 0);
        }
    }

    static void bubbleSort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int i = 0; i < n - 1; i++) {
            bool swapped = false;
            for (int j = 0; j < n - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    std::swap(arr[j], arr[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped) break;
        }
    }

    static void insertionSort(std::vector<int>& arr) {
        for (int i = 1; i < static_cast<int>(arr.size()); i++) {
            auto key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    static void selectionSort(std::vector<int>& arr) {
        for (int i = 0; i < static_cast<int>(arr.size()) - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < static_cast<int>(arr.size()); j++) {
                if (arr[j] < arr[minIndex]) minIndex = j;
            }
            if (minIndex != i) std::swap(arr[i], arr[minIndex]);
        }
    }

    static void shellSort(std::vector<int>& arr) {
        int n = static_cast<int>(arr.size());
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }

    static void countingSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        int maxVal = *std::max_element(arr.begin(), arr.end());
        int minVal = *std::min_element(arr.begin(), arr.end());
        int range = maxVal - minVal + 1;

        std::vector<int> count(range, 0), output(arr.size());

        for (int num : arr) count[num - minVal]++;
        for (int i = 1; i < range; i++) count[i] += count[i - 1];

        for (int i = static_cast<int>(arr.size()) - 1; i >= 0; i--) {
            output[count[arr[i] - minVal] - 1] = arr[i];
            count[arr[i] - minVal]--;
        }
        arr.swap(output);
    }

    static void radixSort(std::vector<int>& arr) {
        if (arr.empty()) return;
        int maxVal = *std::max_element(arr.begin(), arr.end());
        for (int exp = 1; maxVal / exp > 0; exp *= 10) countingSortRadix(arr, exp);
    }

    static bool isSorted(const std::vector<int>& arr) {
        for (size_t i = 1; i < arr.size(); i++) {
            if (arr[i] < arr[i - 1]) return false;
        }
        return true;
    }

    static void displayArray(const std::vector<int>& arr, size_t maxDisplay = 20) {
        std::cout << "[";
        size_t displayCount = std::min(arr.size(), maxDisplay);
        for (size_t i = 0; i < displayCount; i++) {
            std::cout << arr[i];
            if (i < displayCount - 1) std::cout << ", ";
        }
        if (arr.size() > maxDisplay) {
            std::cout << "... (" << arr.size() - maxDisplay << " more)";
        }
        std::cout << "]" << std::endl;
    }

private:
    static void mergeSortHelper(std::vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid);
            mergeSortHelper(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    static void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1, n2 = right - mid;
        std::vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
        std::vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) arr[k++] = (leftArr[i] <= rightArr[j]) ? leftArr[i++] : rightArr[j++];
        while (i < n1) arr[k++] = leftArr[i++];
        while (j < n2) arr[k++] = rightArr[j++];
    }

    static void quickSortHelper(std::vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            quickSortHelper(arr, low, pivotIndex - 1);
            quickSortHelper(arr, pivotIndex + 1, high);
        }
    }

    static int partition(std::vector<int>& arr, int low, int high) {
        int pivot = arr[high], i = low;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) std::swap(arr[i++], arr[j]);
        }
        std::swap(arr[i], arr[high]);
        return i;
    }

    static void heapify(std::vector<int>& arr, int n, int i) {
        int largest = i, left = 2 * i + 1, right = 2 * i + 2;
        if (left < n && arr[left] > arr[largest]) largest = left;
        if (right < n && arr[right] > arr[largest]) largest = right;
        if (largest != i) {
            std::swap(arr[i], arr[largest]);
            heapify(arr, n, largest);
        }
    }

    static void countingSortRadix(std::vector<int>& arr, int exp) {
        std::vector<int> output(arr.size());
        std::vector<int> count(10, 0);
        for (int num : arr) count[(num / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = static_cast<int>(arr.size()) - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }
        arr.swap(output);
    }
};

// ============================================================================
// SEARCH ALGORITHMS
// ============================================================================

class SearchAlgorithms {
public:
    static int linearSearch(const std::vector<int>& arr, int target) {
        for (int i = 0; i < static_cast<int>(arr.size()); i++) {
            if (arr[i] == target) return i;
        }
        return -1;
    }

    static int binarySearch(const std::vector<int>& arr, int target) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    static int interpolationSearch(const std::vector<int>& arr, int target) {
        int left = 0, right = static_cast<int>(arr.size()) - 1;
        while (left <= right && target >= arr[left] && target <= arr[right]) {
            if (arr[left] == arr[right]) {
                return (arr[left] == target) ? left : -1;
            }
            int pos = left + ((target - arr[left]) * (right - left)) / (arr[right] - arr[left]);
            if (arr[pos] == target) return pos;
            else if (arr[pos] < target) left = pos + 1;
            else right = pos - 1;
        }
        return -1;
    }

    static int exponentialSearch(const std::vector<int>& arr, int target) {
        if (arr.empty()) return -1;
        if (arr[0] == target) return 0;
        int i = 1;
        while (i < static_cast<int>(arr.size()) && arr[i] <= target) i *= 2;
        return binarySearchHelper(arr, target, i / 2, std::min(i, static_cast<int>(arr.size()) - 1));
    }

    static int jumpSearch(const std::vector<int>& arr, int target) {
        int n = static_cast<int>(arr.size());
        int step = static_cast<int>(sqrt(n)), prev = 0;
        while (prev < n && arr[std::min(step, n) - 1] < target) {
            prev = step; step += static_cast<int>(sqrt(n));
            if (prev >= n) return -1;
        }
        while (prev < n && arr[prev] < target) prev++;
        return (prev < n && arr[prev] == target) ? prev : -1;
    }

    static int fibonacciSearch(const std::vector<int>& arr, int target) {
        int n = static_cast<int>(arr.size());
        std::vector<int> fib; generateFibonacciNumbers(fib, n);
        int fibM = static_cast<int>(fib.size()) - 1, offset = -1;
        while (fibM > 1) {
            int i = std::min(offset + fib[fibM - 2], n - 1);
            if (arr[i] < target) { fibM -= 1; offset = i; }
            else if (arr[i] > target) fibM -= 2;
            else return i;
        }
        if (fibM&& offset + 1 < n && arr[offset + 1] == target) return offset + 1;
        return -1;
    }

    static bool hashSearch(const std::vector<int>& arr, int target) {
        std::unordered_set<int> hashTable(arr.begin(), arr.end());
        return hashTable.count(target) > 0;
    }

private:
    static int binarySearchHelper(const std::vector<int>& arr, int target, int left, int right) {
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) return mid;
            else if (arr[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        return -1;
    }

    static void generateFibonacciNumbers(std::vector<int>& fib, int n) {
        fib = { 0, 1 };
        while (fib.back() < n) fib.push_back(fib[fib.size() - 1] + fib[fib.size() - 2]);
    }
};
// ============================================================================
// DATA GENERATOR
// ============================================================================

class DataGenerator {
public:
    static std::vector<int> generateRandomIntegers(size_t size, int min = 1, int max = 10000) {
        std::vector<int> data(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);

        for (size_t i = 0; i < size; i++) {
            data[i] = dis(gen);
        }
        return data;
    }

    static std::vector<int> generateSortedIntegers(size_t size, int min = 1, int max = 10000) {
        auto data = generateRandomIntegers(size, min, max);
        std::sort(data.begin(), data.end());
        return data;
    }

    static std::vector<int> generateReverseSortedIntegers(size_t size, int min = 1, int max = 10000) {
        auto data = generateSortedIntegers(size, min, max);
        std::reverse(data.begin(), data.end());
        return data;
    }

    static std::vector<int> generateNearlySortedIntegers(size_t size, int min = 1, int max = 10000, double disorderRatio = 0.1) {
        auto data = generateSortedIntegers(size, min, max);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, size - 1);

        size_t swaps = static_cast<size_t>(size * disorderRatio);
        for (size_t i = 0; i < swaps; i++) {
            size_t idx1 = dis(gen);
            size_t idx2 = dis(gen);
            std::swap(data[idx1], data[idx2]);
        }
        return data;
    }

    static std::vector<int> generateDuplicates(size_t size, int uniqueValues = 10) {
        std::vector<int> data(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(1, uniqueValues);

        for (size_t i = 0; i < size; i++) {
            data[i] = dis(gen);
        }
        return data;
    }
};

// ============================================================================
// PERFORMANCE ANALYZER
// ============================================================================

struct PerformanceResult {
    std::chrono::microseconds time;
    bool success;
    size_t dataSize;
    std::string algorithmName;
};

class PerformanceAnalyzer {
private:
    std::vector<PerformanceResult> results;

public:
    void measureSorting(const std::vector<int>& data, const std::string& algorithmName, void (*sortFunc)(std::vector<int>&)) {
        std::vector<int> testData = data;

        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(testData);
        auto end = std::chrono::high_resolution_clock::now();

        PerformanceResult result;
        result.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        result.success = SortingAlgorithms::isSorted(testData);
        result.dataSize = data.size();
        result.algorithmName = algorithmName;

        results.push_back(result);
    }

    void measureSortingDirect(const std::vector<int>& data, const std::string& algorithmName, int algorithmType) {
        std::vector<int> testData = data;

        auto start = std::chrono::high_resolution_clock::now();

        switch (algorithmType) {
        case 1: SortingAlgorithms::mergeSort(testData); break;
        case 2: SortingAlgorithms::quickSort(testData); break;
        case 3: SortingAlgorithms::heapSort(testData); break;
        case 4: SortingAlgorithms::insertionSort(testData); break;
        case 5: SortingAlgorithms::selectionSort(testData); break;
        case 6: SortingAlgorithms::bubbleSort(testData); break;
        case 7: SortingAlgorithms::shellSort(testData); break;
        case 8: SortingAlgorithms::countingSort(testData); break;
        case 9: SortingAlgorithms::radixSort(testData); break;
        }

        auto end = std::chrono::high_resolution_clock::now();

        PerformanceResult result;
        result.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        result.success = SortingAlgorithms::isSorted(testData);
        result.dataSize = data.size();
        result.algorithmName = algorithmName;

        results.push_back(result);
    }

    void measureSearch(const std::vector<int>& data, int target, const std::string& algorithmName, int (*searchFunc)(const std::vector<int>&, int)) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = searchFunc(data, target);
        auto end = std::chrono::high_resolution_clock::now();

        PerformanceResult perfResult;
        perfResult.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        perfResult.success = (result != -1);
        perfResult.dataSize = data.size();
        perfResult.algorithmName = algorithmName;

        results.push_back(perfResult);
    }

    void measureSearchDirect(const std::vector<int>& data, int target, const std::string& algorithmName, int algorithmType) {
        auto start = std::chrono::high_resolution_clock::now();
        int result = -1;

        switch (algorithmType) {
        case 1: result = SearchAlgorithms::linearSearch(data, target); break;
        case 2: result = SearchAlgorithms::binarySearch(data, target); break;
        case 3: result = SearchAlgorithms::interpolationSearch(data, target); break;
        case 4: result = SearchAlgorithms::exponentialSearch(data, target); break;
        case 5: result = SearchAlgorithms::jumpSearch(data, target); break;
        case 6: result = SearchAlgorithms::fibonacciSearch(data, target); break;
        case 7: result = SearchAlgorithms::hashSearch(data, target) ? 0 : -1; break;
        }

        auto end = std::chrono::high_resolution_clock::now();

        PerformanceResult perfResult;
        perfResult.time = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        perfResult.success = (result != -1);
        perfResult.dataSize = data.size();
        perfResult.algorithmName = algorithmName;

        results.push_back(perfResult);
    }

    void displayResults() {
        if (results.empty()) {
            std::cout << "No performance data available." << std::endl;
            return;
        }

        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "PERFORMANCE ANALYSIS RESULTS" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        std::cout << std::left << std::setw(25) << "Algorithm"
            << std::setw(15) << "Time (μs)"
            << std::setw(10) << "Success"
            << std::setw(15) << "Data Size" << std::endl;
        std::cout << std::string(80, '-') << std::endl;

        for (const auto& result : results) {
            std::cout << std::left << std::setw(25) << result.algorithmName
                << std::setw(15) << result.time.count()
                << std::setw(10) << (result.success ? "✓" : "✗")
                << std::setw(15) << result.dataSize << std::endl;
        }
        std::cout << std::string(80, '=') << std::endl;
    }

    void clearResults() {
        results.clear();
    }

    void generateReport() {
        if (results.empty()) {
            std::cout << "No performance data to report." << std::endl;
            return;
        }

        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "COMPREHENSIVE PERFORMANCE REPORT" << std::endl;
        std::cout << std::string(80, '=') << std::endl;

        // Group by algorithm type
        std::map<std::string, std::vector<PerformanceResult>> groupedResults;
        for (const auto& result : results) {
            groupedResults[result.algorithmName].push_back(result);
        }

        for (const auto& group : groupedResults) {
            std::cout << "\n" << group.first << ":" << std::endl;
            std::cout << std::string(40, '-') << std::endl;

            long long totalTime = 0;
            int successCount = 0;

            for (const auto& result : group.second) {
                totalTime += result.time.count();
                if (result.success) successCount++;
            }

            double avgTime = static_cast<double>(totalTime) / group.second.size();
            double successRate = (static_cast<double>(successCount) / group.second.size()) * 100.0;

            std::cout << "Average Time: " << std::fixed << std::setprecision(2) << avgTime << " μs" << std::endl;
            std::cout << "Success Rate: " << std::fixed << std::setprecision(1) << successRate << "%" << std::endl;
            std::cout << "Tests Run: " << group.second.size() << std::endl;
        }

        std::cout << "\n" << std::string(80, '=') << std::endl;
    }
};

// ============================================================================
// MAIN APPLICATION
// ============================================================================

class SortingAlgorithmDemo {
private:
    PerformanceAnalyzer analyzer;
    std::vector<int> currentData;
    size_t dataSize;

public:
    SortingAlgorithmDemo() : dataSize(1000) {
        generateNewData();
    }

    void run() {
        while (true) {
            displayMainMenu();
            int choice = getChoice(1, 9);

            switch (choice) {
            case 1: generateDataMenu(); break;
            case 2: sortingAlgorithmsMenu(); break;
            case 3: searchAlgorithmsMenu(); break;
            case 4: runBenchmark(); break;
            case 5: displayCurrentData(); break;
            case 6: analyzer.displayResults(); break;
            case 7: analyzer.generateReport(); break;
            case 8: analyzer.clearResults(); break;
            case 9: return;
            }
        }
    }

private:
    void displayMainMenu() {
        std::cout << "\n" << std::string(80, '=') << std::endl;
        std::cout << "           MULTI-STRUCTURE SEARCH & SORT ENGINE - C++ (DSA)" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        std::cout << "Current Data Size: " << dataSize << " elements" << std::endl;
        std::cout << std::string(80, '-') << std::endl;
        std::cout << "1. Generate New Data" << std::endl;
        std::cout << "2. Sorting Algorithms" << std::endl;
        std::cout << "3. Search Algorithms" << std::endl;
        std::cout << "4. Run Comprehensive Benchmark" << std::endl;
        std::cout << "5. Display Current Data" << std::endl;
        std::cout << "6. Display Performance Results" << std::endl;
        std::cout << "7. Generate Performance Report" << std::endl;
        std::cout << "8. Clear Results" << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << std::string(80, '=') << std::endl;
    }

    void generateDataMenu() {
        std::cout << "\n" << std::string(60, '-') << std::endl;
        std::cout << "DATA GENERATION MENU" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "1. Random Integers" << std::endl;
        std::cout << "2. Sorted Integers" << std::endl;
        std::cout << "3. Reverse Sorted Integers" << std::endl;
        std::cout << "4. Nearly Sorted Integers" << std::endl;
        std::cout << "5. Duplicate Values" << std::endl;
        std::cout << "6. Custom Size" << std::endl;
        std::cout << "7. Back to Main Menu" << std::endl;

        int choice = getChoice(1, 7);

        switch (choice) {
        case 1:
            generateNewData();
            std::cout << "Generated " << dataSize << " random integers." << std::endl;
            break;
        case 2:
            currentData = DataGenerator::generateSortedIntegers(dataSize);
            std::cout << "Generated " << dataSize << " sorted integers." << std::endl;
            break;
        case 3:
            currentData = DataGenerator::generateReverseSortedIntegers(dataSize);
            std::cout << "Generated " << dataSize << " reverse sorted integers." << std::endl;
            break;
        case 4:
            currentData = DataGenerator::generateNearlySortedIntegers(dataSize);
            std::cout << "Generated " << dataSize << " nearly sorted integers." << std::endl;
            break;
        case 5:
            currentData = DataGenerator::generateDuplicates(dataSize, 10);
            std::cout << "Generated " << dataSize << " integers with duplicates." << std::endl;
            break;
        case 6:
            std::cout << "Enter new data size: ";
            std::cin >> dataSize;
            generateNewData();
            std::cout << "Generated " << dataSize << " random integers." << std::endl;
            break;
        }
    }

    void sortingAlgorithmsMenu() {
        std::cout << "\n" << std::string(60, '-') << std::endl;
        std::cout << "SORTING ALGORITHMS MENU" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "1. Merge Sort" << std::endl;
        std::cout << "2. Quick Sort" << std::endl;
        std::cout << "3. Heap Sort" << std::endl;
        std::cout << "4. Insertion Sort" << std::endl;
        std::cout << "5. Selection Sort" << std::endl;
        std::cout << "6. Bubble Sort" << std::endl;
        std::cout << "7. Shell Sort" << std::endl;
        std::cout << "8. Counting Sort" << std::endl;
        std::cout << "9. Radix Sort" << std::endl;
        std::cout << "10. Compare All Sorting Algorithms" << std::endl;
        std::cout << "11. Back to Main Menu" << std::endl;

        int choice = getChoice(1, 11);

        if (choice >= 1 && choice <= 9) {
            runSingleSortingAlgorithm(choice);
        }
        else if (choice == 10) {
            compareAllSortingAlgorithms();
        }
    }

    void searchAlgorithmsMenu() {
        std::cout << "\n" << std::string(60, '-') << std::endl;
        std::cout << "SEARCH ALGORITHMS MENU" << std::endl;
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "1. Linear Search" << std::endl;
        std::cout << "2. Binary Search" << std::endl;
        std::cout << "3. Interpolation Search" << std::endl;
        std::cout << "4. Exponential Search" << std::endl;
        std::cout << "5. Jump Search" << std::endl;
        std::cout << "6. Fibonacci Search" << std::endl;
        std::cout << "7. Hash Search" << std::endl;
        std::cout << "8. Compare All Search Algorithms" << std::endl;
        std::cout << "9. Back to Main Menu" << std::endl;

        int choice = getChoice(1, 9);

        if (choice >= 1 && choice <= 7) {
            runSingleSearchAlgorithm(choice);
        }
        else if (choice == 8) {
            compareAllSearchAlgorithms();
        }
    }

    void runSingleSortingAlgorithm(int algorithm) {
        std::vector<int> testData = currentData;
        std::string algorithmName;

        auto start = std::chrono::high_resolution_clock::now();

        switch (algorithm) {
        case 1:
            SortingAlgorithms::mergeSort(testData);
            algorithmName = "Merge Sort";
            break;
        case 2:
            SortingAlgorithms::quickSort(testData);
            algorithmName = "Quick Sort";
            break;
        case 3:
            SortingAlgorithms::heapSort(testData);
            algorithmName = "Heap Sort";
            break;
        case 4:
            SortingAlgorithms::insertionSort(testData);
            algorithmName = "Insertion Sort";
            break;
        case 5:
            SortingAlgorithms::selectionSort(testData);
            algorithmName = "Selection Sort";
            break;
        case 6:
            SortingAlgorithms::bubbleSort(testData);
            algorithmName = "Bubble Sort";
            break;
        case 7:
            SortingAlgorithms::shellSort(testData);
            algorithmName = "Shell Sort";
            break;
        case 8:
            SortingAlgorithms::countingSort(testData);
            algorithmName = "Counting Sort";
            break;
        case 9:
            SortingAlgorithms::radixSort(testData);
            algorithmName = "Radix Sort";
            break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "\n" << algorithmName << " Results:" << std::endl;
        std::cout << "Time: " << duration.count() << " μs" << std::endl;
        std::cout << "Sorted: " << (SortingAlgorithms::isSorted(testData) ? "Yes" : "No") << std::endl;

        // Add to performance analyzer
        analyzer.measureSortingDirect(currentData, algorithmName, algorithm);
    }

    void runSingleSearchAlgorithm(int algorithm) {
        if (currentData.empty()) {
            std::cout << "No data available for search!" << std::endl;
            return;
        }

        std::cout << "Enter target value to search: ";
        int target;
        std::cin >> target;

        std::vector<int> searchData = currentData;
        std::string algorithmName;
        int result = -1;

        // Sort data for binary search algorithms
        if (algorithm >= 2 && algorithm <= 6) {
            std::sort(searchData.begin(), searchData.end());
        }

        auto start = std::chrono::high_resolution_clock::now();

        switch (algorithm) {
        case 1:
            result = SearchAlgorithms::linearSearch(searchData, target);
            algorithmName = "Linear Search";
            break;
        case 2:
            result = SearchAlgorithms::binarySearch(searchData, target);
            algorithmName = "Binary Search";
            break;
        case 3:
            result = SearchAlgorithms::interpolationSearch(searchData, target);
            algorithmName = "Interpolation Search";
            break;
        case 4:
            result = SearchAlgorithms::exponentialSearch(searchData, target);
            algorithmName = "Exponential Search";
            break;
        case 5:
            result = SearchAlgorithms::jumpSearch(searchData, target);
            algorithmName = "Jump Search";
            break;
        case 6:
            result = SearchAlgorithms::fibonacciSearch(searchData, target);
            algorithmName = "Fibonacci Search";
            break;
        case 7:
            result = SearchAlgorithms::hashSearch(searchData, target) ? 0 : -1;
            algorithmName = "Hash Search";
            break;
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "\n" << algorithmName << " Results:" << std::endl;
        std::cout << "Target: " << target << std::endl;
        std::cout << "Found: " << (result != -1 ? "Yes" : "No") << std::endl;
        if (result != -1) {
            std::cout << "Index: " << result << std::endl;
        }
        std::cout << "Time: " << duration.count() << " μs" << std::endl;

        // Add to performance analyzer
        analyzer.measureSearchDirect(searchData, target, algorithmName, algorithm);
    }

    void compareAllSortingAlgorithms() {
        std::cout << "\nComparing all sorting algorithms..." << std::endl;

        std::vector<std::string> algorithms = {
            "Merge Sort", "Quick Sort", "Heap Sort", "Insertion Sort",
            "Selection Sort", "Bubble Sort", "Shell Sort", "Counting Sort", "Radix Sort"
        };

        for (size_t i = 0; i < algorithms.size(); i++) {
            std::vector<int> testData = currentData;
            auto start = std::chrono::high_resolution_clock::now();

            switch (i) {
            case 0: SortingAlgorithms::mergeSort(testData); break;
            case 1: SortingAlgorithms::quickSort(testData); break;
            case 2: SortingAlgorithms::heapSort(testData); break;
            case 3: SortingAlgorithms::insertionSort(testData); break;
            case 4: SortingAlgorithms::selectionSort(testData); break;
            case 5: SortingAlgorithms::bubbleSort(testData); break;
            case 6: SortingAlgorithms::shellSort(testData); break;
            case 7: SortingAlgorithms::countingSort(testData); break;
            case 8: SortingAlgorithms::radixSort(testData); break;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << std::left << std::setw(20) << algorithms[i]
                << std::setw(15) << duration.count() << " μs"
                << std::setw(10) << (SortingAlgorithms::isSorted(testData) ? "✓" : "✗") << std::endl;
        }
    }

    void compareAllSearchAlgorithms() {
        std::cout << "\nComparing all search algorithms..." << std::endl;
        std::cout << "Enter target value to search: ";
        int target;
        std::cin >> target;

        std::vector<int> searchData = currentData;
        std::sort(searchData.begin(), searchData.end());

        std::vector<std::string> algorithms = {
            "Linear Search", "Binary Search", "Interpolation Search",
            "Exponential Search", "Jump Search", "Fibonacci Search", "Hash Search"
        };

        for (size_t i = 0; i < algorithms.size(); i++) {
            auto start = std::chrono::high_resolution_clock::now();
            int result = -1;

            switch (i) {
            case 0: result = SearchAlgorithms::linearSearch(searchData, target); break;
            case 1: result = SearchAlgorithms::binarySearch(searchData, target); break;
            case 2: result = SearchAlgorithms::interpolationSearch(searchData, target); break;
            case 3: result = SearchAlgorithms::exponentialSearch(searchData, target); break;
            case 4: result = SearchAlgorithms::jumpSearch(searchData, target); break;
            case 5: result = SearchAlgorithms::fibonacciSearch(searchData, target); break;
            case 6: result = SearchAlgorithms::hashSearch(searchData, target) ? 0 : -1; break;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

            std::cout << std::left << std::setw(20) << algorithms[i]
                << std::setw(10) << (result != -1 ? "Found" : "Not Found")
                << std::setw(10) << result
                << std::setw(15) << duration.count() << " μs" << std::endl;
        }
    }

    void runBenchmark() {
        std::cout << "\nRunning comprehensive benchmark..." << std::endl;
        std::cout << "This will test algorithms with different data sizes and types." << std::endl;

        std::vector<size_t> sizes = { 1000, 5000, 10000 };
        std::vector<std::string> dataTypes = { "Random", "Sorted", "Reverse Sorted", "Nearly Sorted" };

        for (size_t size : sizes) {
            std::cout << "\nTesting with " << size << " elements:" << std::endl;

            for (const std::string& type : dataTypes) {
                std::vector<int> testData;
                if (type == "Random") {
                    testData = DataGenerator::generateRandomIntegers(size);
                }
                else if (type == "Sorted") {
                    testData = DataGenerator::generateSortedIntegers(size);
                }
                else if (type == "Reverse Sorted") {
                    testData = DataGenerator::generateReverseSortedIntegers(size);
                }
                else if (type == "Nearly Sorted") {
                    testData = DataGenerator::generateNearlySortedIntegers(size);
                }

                // Test merge sort
                auto start = std::chrono::high_resolution_clock::now();
                SortingAlgorithms::mergeSort(testData);
                auto end = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

                std::cout << "Merge Sort (" << type << "): " << duration.count() << " μs" << std::endl;
            }
        }
    }

    void displayCurrentData() {
        std::cout << "\nCurrent Data (" << currentData.size() << " elements):" << std::endl;
        SortingAlgorithms::displayArray(currentData);
    }

    void generateNewData() {
        currentData = DataGenerator::generateRandomIntegers(dataSize);
    }

    int getChoice(int min, int max) {
        int choice;
        while (true) {
            std::cout << "\nEnter your choice (" << min << "-" << max << "): ";
            if (std::cin >> choice) {
                if (choice >= min && choice <= max) {
                    std::cin.ignore();
                    return choice;
                }
                else {
                    std::cout << "Invalid choice! Please enter a number between " << min << " and " << max << "." << std::endl;
                }
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input! Please enter a valid number." << std::endl;
            }
        }
    }
};

// ============================================================================
// MAIN FUNCTION
// ============================================================================

int main() {
    try {
        std::cout << "Starting Multi-Structure Search & Sort Engine..." << std::endl;
        SortingAlgorithmDemo demo;
        demo.run();
        std::cout << "Thank you for using the Multi-Structure Search & Sort Engine!" << std::endl;
        return 0;
    }
    catch (const std::exception& e) {
        std::cout << "Fatal error: " << e.what() << std::endl;
        std::cout << "Press Enter to exit..." << std::endl;
        std::cin.get();
        return 1;
    }
}
