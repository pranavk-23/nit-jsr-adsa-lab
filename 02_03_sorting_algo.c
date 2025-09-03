#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 100

// Utility function to swap
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

/* =========================
   (i) Insertion Sort
   ========================= */
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}

/* =========================
   (ii) Bubble Sort
   ========================= */
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) swap(&arr[j], &arr[j+1]);
        }
    }
}

/* =========================
   (iii) Selection Sort
   ========================= */
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;
        swap(&arr[minIdx], &arr[i]);
    }
}

/* =========================
   (iv) Shell Sort
   ========================= */
void shellSort(int arr[], int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j-gap] > temp; j -= gap) {
                arr[j] = arr[j-gap];
            }
            arr[j] = temp;
        }
    }
}

/* =========================
   (v) Quick Sort
   ========================= */
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low-1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return i+1;
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi-1);
        quickSort(arr, pi+1, high);
    }
}

/* =========================
   (vi) Merge Sort
   ========================= */
void merge(int arr[], int l, int m, int r) {
    int n1 = m-l+1, n2 = r-m;
    int L[n1], R[n2];
    for (int i=0; i<n1; i++) L[i] = arr[l+i];
    for (int j=0; j<n2; j++) R[j] = arr[m+1+j];
    int i=0, j=0, k=l;
    while (i<n1 && j<n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i<n1) arr[k++] = L[i++];
    while (j<n2) arr[k++] = R[j++];
}
void mergeSort(int arr[], int l, int r) {
    if (l<r) {
        int m = l+(r-l)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/* =========================
   (vii) Heap Sort
   ========================= */
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2*i+1, r = 2*i+2;
    if (l<n && arr[l]>arr[largest]) largest = l;
    if (r<n && arr[r]>arr[largest]) largest = r;
    if (largest!=i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}
void heapSort(int arr[], int n) {
    for (int i=n/2-1; i>=0; i--) heapify(arr, n, i);
    for (int i=n-1; i>=0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/* =========================
   (viii) Radix Sort
   ========================= */
int getMax(int arr[], int n) {
    int mx = arr[0];
    for (int i=1; i<n; i++)
        if (arr[i]>mx) mx = arr[i];
    return mx;
}
void countSortRadix(int arr[], int n, int exp) {
    int output[n];
    int count[10]={0};
    for (int i=0; i<n; i++) count[(arr[i]/exp)%10]++;
    for (int i=1; i<10; i++) count[i]+=count[i-1];
    for (int i=n-1; i>=0; i--) {
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for (int i=0; i<n; i++) arr[i]=output[i];
}
void radixSort(int arr[], int n) {
    int m = getMax(arr,n);
    for (int exp=1; m/exp>0; exp*=10)
        countSortRadix(arr, n, exp);
}

/* =========================
   (ix) Counting Sort
   ========================= */
void countingSort(int arr[], int n) {
    int max = getMax(arr,n);
    int count[max+1];
    memset(count,0,sizeof(count));
    for (int i=0; i<n; i++) count[arr[i]]++;
    int idx=0;
    for (int i=0; i<=max; i++)
        while (count[i]--) arr[idx++]=i;
}

/* =========================
   (x) Bucket Sort
   ========================= */
void bucketSort(int arr[], int n) {
    int max = getMax(arr,n);
    int bucket[max+1];
    memset(bucket,0,sizeof(bucket));
    for (int i=0; i<n; i++) bucket[arr[i]]++;
    int idx=0;
    for (int i=0; i<=max; i++)
        while (bucket[i]--) arr[idx++]=i;
}

/* =========================
   (xi) Radix Exchange Sort
   =========================
   (Binary MSD radix sort: partitions based on most significant bit)
*/
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0) return;
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((arr[i]>>bit)&1)==0) i++;
        while (i <= j && ((arr[j]>>bit)&1)==1) j--;
        if (i < j) swap(&arr[i], &arr[j]);
    }
    radixExchangeSort(arr, left, j, bit-1);
    radixExchangeSort(arr, j+1, right, bit-1);
}

/* =========================
   (xii) Address Calculation Sort
   =========================
   (Scatter sort / hashing-based; here implemented as bucket hashing)
*/
void addressCalculationSort(int arr[], int n) {
    int max = getMax(arr,n);
    int table[max+1];
    memset(table,0,sizeof(table));
    for (int i=0; i<n; i++) table[arr[i]]++;
    int idx=0;
    for (int i=0; i<=max; i++)
        while (table[i]--) arr[idx++]=i;
}

/* =========================
   Main Menu
   ========================= */
int main() {
    int arr[MAX], n, choice;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i=0; i<n; i++) scanf("%d", &arr[i]);

    printf("\nChoose sorting method:\n");
    printf("1. Insertion Sort\n2. Bubble Sort\n3. Selection Sort\n4. Shell Sort\n");
    printf("5. Quick Sort\n6. Merge Sort\n7. Heap Sort\n8. Radix Sort\n");
    printf("9. Counting Sort\n10. Bucket Sort\n11. Radix Exchange Sort\n12. Address Calculation Sort\n");
    scanf("%d", &choice);

    switch(choice) {
        case 1: insertionSort(arr,n); break;
        case 2: bubbleSort(arr,n); break;
        case 3: selectionSort(arr,n); break;
        case 4: shellSort(arr,n); break;
        case 5: quickSort(arr,0,n-1); break;
        case 6: mergeSort(arr,0,n-1); break;
        case 7: heapSort(arr,n); break;
        case 8: radixSort(arr,n); break;
        case 9: countingSort(arr,n); break;
        case 10: bucketSort(arr,n); break;
        case 11: radixExchangeSort(arr,0,n-1,31); break;
        case 12: addressCalculationSort(arr,n); break;
        default: printf("Invalid choice\n"); return 0;
    }

    printf("Sorted array: ");
    printArray(arr,n);

    return 0;
}
