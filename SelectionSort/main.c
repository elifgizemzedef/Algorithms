#include <stdio.h>

void selectionSort(int arr[], int n);

int main() {
  int n, i;
  printf("Enter the number of elements in the array: ");
  scanf("%d", &n);

  int arr[n];

  printf("Enter %d elements:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &arr[i]);
  }

  selectionSort(arr, n);

  printf("Sorted array in ascending order:\n");
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");

  return 0;
}

void selectionSort(int arr[], int n) {
  int i, j, minIndex, temp;
  for (i = 0; i < n - 1; i++) {
    minIndex = i;
    for (j = i + 1; j < n; j++) {
      if (arr[j] < arr[minIndex]) {
        minIndex = j;
      }
    }
    if (minIndex != i) {
      temp = arr[i];
      arr[i] = arr[minIndex];
      arr[minIndex] = temp;
    }
  }
}
