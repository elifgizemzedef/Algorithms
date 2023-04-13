#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

void insertNode(Node **head, int data) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}


void deleteNode(Node **head, int data) {
    Node *temp = *head, *prev = NULL;
    if (temp != NULL && temp->data == data) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return;
    }
    prev->next = temp->next;
    free(temp);
}

int length(Node *head) {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void printList(Node *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node *temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}


Node* getMiddleNode(Node* start, Node* end) {
    Node* slow = start;
    Node* fast = start;
    while (fast != end && fast->next != end) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void quickSort(Node **head, Node *start, Node *end) {
    if (start == NULL || end == NULL || start == end) {
        return;
    }
    Node *pivotNode = start;
    int pivot = pivotNode->data;
    Node *left = start;
    Node *right = end;
    while (left != right) {
        while (left != pivotNode && left->data < pivot) {
            left = left->next;
        }
        while (right != pivotNode && right->data >= pivot) {
            right = right->next;
        }
        if (left != right) {
            int temp = left->data;
            left->data = right->data;
            right->data = temp;
        }
    }
    int temp = pivotNode->data;
    pivotNode->data = right->data;
    right->data = temp;
    pivotNode = right;
    quickSort(head, start, pivotNode->next);
    quickSort(head, pivotNode->next, end);
}


int main() {
    Node *head = NULL;
    insertNode(&head, INT_MAX);
    insertNode(&head, 5);
    insertNode(&head, 9);
    insertNode(&head, 2);
    insertNode(&head, 1);
    insertNode(&head, 7);
    insertNode(&head, 6);
    insertNode(&head, 8);
    insertNode(&head, 3);
    insertNode(&head, 4);
    printf("Original list: ");
    printList(head);
    quickSort(&head, head->next, NULL);
    printf("Sorted list: ");
    printList(head);
    return 0;
}
