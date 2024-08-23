#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

const int MAX_SIZE = 1000; // Максимальный размер массива

void outputArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
}

void swap(int arr[], int a, int b) {
    int c = arr[a];
    arr[a] = arr[b];
    arr[b] = c;
}

int partition(int arr[], int low, int high, int pivot) {
    int i = low;
    int j = low;
    while (i < high + 1)
        if (arr[i] > pivot) i++;
        else {
            swap(arr, i, j);
            i++;
            j++;
        }
    return j - 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int pos = partition(arr, low, high, pivot);
        quickSort(arr, low, pos - 1);
        quickSort(arr, pos + 1, high);
    }
}

void merge(int arr[], int left[], int leftSize, int right[], int rightSize) {
    int i = 0, j = 0, k = 0;
    while (i < leftSize && j < rightSize) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < leftSize) {
        arr[k++] = left[i++];
    }
    while (j < rightSize) {
        arr[k++] = right[j++];
    }
}

void mergeSort(int arr[], int n) {
    for (int currSize = 1; currSize < n; currSize *= 2) {
        for (int leftStart = 0; leftStart < n - 1; leftStart += 2 * currSize) {
            int mid = min(leftStart + currSize - 1, n - 1);
            int rightEnd = min(leftStart + 2 * currSize - 1, n - 1);
            int left[MAX_SIZE], right[MAX_SIZE];
            for (int i = 0; i <= mid - leftStart; i++) {
                left[i] = arr[leftStart + i];
            }
            for (int i = 0; i < rightEnd - mid; i++) {
                right[i] = arr[mid + 1 + i];
            }
            merge(arr + leftStart, left, mid - leftStart + 1, right, rightEnd - mid);
        }
    }
}

void selectionSort(int arr[], int n) {
    int minIndex;
    for (int i = 0; i < n - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        swap(arr[minIndex], arr[i]);
    }
}

int main() {
    int n;
    cout << "Array's size: ";
    //cin >> n;
    n = 1000;
    if (n < 1) {
        cout << "Odumaysa, pupsik, ya uhoshu...";
        exit(0);
    }
    int arr[MAX_SIZE];
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) arr[i] = i;
        //cin >> arr[i];

    clock_t start_time = clock();
    quickSort(arr, 0, n - 1);
    cout << "QuickSorted array: ";
    //outputArray(arr, n);
    clock_t end_time = clock();
    double time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds\n";


    start_time = clock();
    mergeSort(arr, n);
    cout << "MergeSorted array: ";
    //outputArray(arr, n);
     end_time = clock();
     time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds\n";

    start_time = clock();
    selectionSort(arr, n);
    cout << "SelectionSorted array: ";
    //outputArray(arr, n);    
    end_time = clock();
    time_taken = double(end_time - start_time) / CLOCKS_PER_SEC;
    cout << "Time taken: " << time_taken << " seconds\n";


    return 0;
}
