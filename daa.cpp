#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

// ------------------- MERGE SORT -------------------
void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ------------------- QUICK SORT -------------------
int partitionArray(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionArray(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ------------------- BINARY SEARCH -------------------
int binarySearch(vector<int>& arr, int key) {
    int low = 0, high = arr.size() - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

// ------------------- MAIN FUNCTION -------------------
int main() {
    int n = 10000;
    vector<int> data(n);

    // Generate random data
    for (int i = 0; i < n; i++)
        data[i] = rand() % 100000;

    int key = data[n/2];  // element to search

    // ----------- TIME: MERGE SORT + BINARY SEARCH -------------
    vector<int> arr1 = data;
    auto start1 = high_resolution_clock::now();
    mergeSort(arr1, 0, n - 1);
    int index1 = binarySearch(arr1, key);
    auto end1 = high_resolution_clock::now();
    auto time_merge = duration_cast<milliseconds>(end1 - start1).count();

    // ----------- TIME: QUICK SORT + BINARY SEARCH -------------
    vector<int> arr2 = data;
    auto start2 = high_resolution_clock::now();
    quickSort(arr2, 0, n - 1);
    int index2 = binarySearch(arr2, key);
    auto end2 = high_resolution_clock::now();
    auto time_quick = duration_cast<milliseconds>(end2 - start2).count();

    // ----------- TIME: UNSORTED + LINEAR SEARCH -------------
    auto start3 = high_resolution_clock::now();
    int index3 = -1;
    for (int i = 0; i < n; i++) {
        if (data[i] == key) {
            index3 = i;
            break;
        }
    }
    auto end3 = high_resolution_clock::now();
    auto time_linear = duration_cast<milliseconds>(end3 - start3).count();

    // -------------------- OUTPUT ---------------------
    cout << "Merge Sort + Binary Search Time: " << time_merge << " ms\n";
    cout << "Quick Sort  + Binary Search Time: " << time_quick << " ms\n";
    cout << "Unsorted + Linear Search Time: " << time_linear << " ms\n";

    return 0;
}