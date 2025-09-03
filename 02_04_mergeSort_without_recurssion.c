#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure for stack frame
typedef struct {
    int l, r, state;
} Frame;

// Stack implementation
Frame stack[MAX];
int top = -1;

void push(Frame f) {
    stack[++top] = f;
}

Frame pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

// Merge two halves
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative Merge Sort (top-down with stack)
void mergeSortIterative(int arr[], int n) {
    push((Frame){0, n - 1, 0}); // initial problem

    while (!isEmpty()) {
        Frame f = pop();

        if (f.l >= f.r) continue; // base case (1 element)

        int m = f.l + (f.r - f.l) / 2;

        if (f.state == 0) {
            // After dividing left and right, we need to merge
            push((Frame){f.l, f.r, 1});   // state 1 means merge later
            push((Frame){m + 1, f.r, 0}); // right subproblem
            push((Frame){f.l, m, 0});     // left subproblem
        } else if (f.state == 1) {
            // Now perform merge
            merge(arr, f.l, m, f.r);
        }
    }
}

// Utility: Print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}

// Main
int main() {
    int arr[MAX], n;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements: ");
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    mergeSortIterative(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
