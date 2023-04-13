#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

void push(Node** head_ref, int new_data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = new_data;
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

Node* merge(Node* l1, Node* l2) {
    Node* result = NULL;
    if (l1 == NULL) return l2;
    if (l2 == NULL) return l1;
    if (l1->data <= l2->data) {
        result = l1;
        result->next = merge(l1->next, l2);
    } else {
        result = l2;
        result->next = merge(l1, l2->next);
    }
    return result;
}

void split(Node* source, Node** frontRef, Node** backRef) {
    Node* fast;
    Node* slow;
    slow = source;
    fast = source->next;
    while (fast != NULL) {
        fast = fast->next;
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }
    *frontRef = source;
    *backRef = slow->next;
    slow->next = NULL;
}

void mergeSort(Node** headRef) {
    Node* head = *headRef;
    Node* a;
    Node* b;
    if ((head == NULL) || (head->next == NULL)) {
        return;
    }
    split(head, &a, &b);
    mergeSort(&a);
    mergeSort(&b);
    *headRef = merge(a, b);
}

int main() {
    Node* head = NULL;
    push(&head, 5);
    push(&head, 20);
    push(&head, 4);
    push(&head, 3);
    push(&head, 30);
    printf("Original list: ");
    printList(head);
    mergeSort(&head);
    printf("Sorted list: ");
    printList(head);
    return 0;
}
