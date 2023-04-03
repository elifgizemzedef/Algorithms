#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int data;
  struct node* next;
  struct node* prev;
} Node;

void insertNode(Node** head, int data);
void printList(Node* head);
void selectionSort(Node* head);

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

  selectionSort(head);

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

void selectionSort(Node* head) {
  Node* ptr1;
  Node* ptr2;
  Node* minNode;

  for (ptr1 = head; ptr1->next != NULL; ptr1 = ptr1->next) {
    minNode = ptr1;
    for (ptr2 = ptr1->next; ptr2 != NULL; ptr2 = ptr2->next) {
      if (ptr2->data < minNode->data) {
        minNode = ptr2;
      }
    }
    if (minNode != ptr1) {
      int temp = ptr1->data;
      ptr1->data = minNode->data;
      minNode->data = temp;
    }
  }
}
