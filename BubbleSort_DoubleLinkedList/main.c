#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
  struct node* prev;
} Node;

void insertNode(Node** head, int data);
void printList(Node* head);
void bubbleSort(Node* head);

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

  bubbleSort(head);

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

void bubbleSort(Node* head) {
  int swapped;
  Node* ptr1;
  Node* lptr = NULL;

  if (head == NULL)
    return;

  do {
    swapped = 0;
    ptr1 = head;

    while (ptr1->next != lptr) {
      if (ptr1->data > ptr1->next->data) {
        int temp = ptr1->data;
        ptr1->data = ptr1->next->data;
        ptr1->next->data = temp;
        swapped = 1;
      }
      ptr1 = ptr1->next;
    }
    lptr = ptr1;
  } while (swapped);
}
