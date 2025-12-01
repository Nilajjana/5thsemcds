#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; 
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    FILE *file;
    int arr[1000];
    int count = 0;
    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    while (fscanf(file, "%d", &arr[count]) != EOF) {
        count++;
    }
    fclose(file);
    printf("Unsorted Data:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    quickSort(arr, 0, count - 1);
    printf("\nSorted Data:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
