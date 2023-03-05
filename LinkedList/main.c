#include <stdio.h>
#include <stdlib.h>

// Define a structure for a single node in the linked list
typedef struct Node {
  int data;
  struct Node* next;
} Node;

// Create a new node with the given data
Node* createNode(int data) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  node->next = NULL;
  return node;
}

// Insert a new node with the given data at the beginning of the list
void insertAtBeginning(Node** head, int data) {
  Node* node = createNode(data);
  node->next = *head;
  *head = node;
}

// Insert a new node with the given data at the end of the list
void insertAtEnd(Node** head, int data) {
  Node* node = createNode(data);
  if (*head == NULL) {
    *head = node;
  } else {
    Node* curr = *head;
    while (curr->next != NULL) {
      curr = curr->next;
    }
    curr->next = node;
  }
}

// Delete the first occurrence of a node with the given data from the list
void deleteNode(Node** head, int data) {
  if (*head == NULL) {
    printf("Error: list is empty.\n");
    return;
  }
  if ((*head)->data == data) {
    Node* temp = *head;
    *head = (*head)->next;
    free(temp);
    return;
  }
  Node* prev = *head;
  Node* curr = (*head)->next;
  while (curr != NULL) {
    if (curr->data == data) {
      prev->next = curr->next;
      free(curr);
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  printf("Error: node with data %d not found.\n", data);
}

// Print the elements of the list
void printList(Node* head) {
  printf("List: ");
  while (head != NULL) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

// Test the linked list implementation
int main() {
  Node* head = NULL;

  insertAtBeginning(&head, 10);
  insertAtBeginning(&head, 20);
  insertAtEnd(&head, 30);
  insertAtEnd(&head, 40);
  printList(head);

  deleteNode(&head, 20);
  printList(head);

  deleteNode(&head, 50);

  return 0;
}
