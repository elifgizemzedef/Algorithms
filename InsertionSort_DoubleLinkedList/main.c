#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
  struct node* prev;
} Node;

void insertNode(Node** head, int data);
void printList(Node* head);
void insertionSort(Node* head);

int main() {
  Node* head = NULL;
  int n, i, data;

  printf("Enter the number of elements in the linked list: ");
  scanf("%d", &n);

  printf("Enter %d elements:\n", n);
  for (i = 0; i < n; i++) {
    scanf("%d", &data);
    insertNode(&head, data);
  }

  insertionSort(head);

  printf("Sorted linked list in ascending order:\n");
  printList(head);

  return 0;
}

void insertNode(Node** head, int data) {
  Node* newNode = (Node*)malloc(sizeof(Node));
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = *head;

  if (*head != NULL) {
    (*head)->prev = newNode;
  }

  *head = newNode;
}

void printList(Node* head) {
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

void insertionSort(Node* head) {
  Node* ptr1;
  Node* ptr2;
  int temp;

  for (ptr1 = head->next; ptr1 != NULL; ptr1 = ptr1->next) {
    temp = ptr1->data;
    for (ptr2 = ptr1->prev; ptr2 != NULL && ptr2->data > temp; ptr2 = ptr2->prev) {
      ptr2->next->data = ptr2->data;
    }
    ptr2->next->data = temp;
  }
}
