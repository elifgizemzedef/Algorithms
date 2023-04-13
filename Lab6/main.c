#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int count;
    struct Node *next;
} Node;

Node* insert(Node *head, int data) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->data = data;
    newNode->count=0;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
    } else {
        Node *current = head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return head;
}

char* convertToBinary(int num) {
    char *binary = (char*) malloc(33 * sizeof(char)); // 32 bit + '\0'
    int i = 0;
    for (int j = 31; j >= 0; j--) {
        binary[i++] = (num & (1 << j)) ? '1' : '0';
    }
    binary[i] = '\0';
    return binary;
}

int countOnes(int num) {
    int count = 0;
    while (num > 0) {
        if (num & 1) {
            count++;
        }
        num = num >> 1;
    }
    return count;
}

Node* getTail(Node *head) {
    while (head != NULL && head->next != NULL) {
        head = head->next;
    }
    return head;
}



Node* partition(Node *low, Node *high) {
    int pivot = high->count;
    Node *i = low->prev;

    for (Node *j = low; j != high; j = j->next) {
        if (j->count <= pivot) {
            i = (i == NULL) ? low : i->next;
            if (i != j) {
                int tempData = i->data;
                int tempCount = i->count;
                i->data = j->data;
                i->count = j->count;
                j->data = tempData;
                j->count = tempCount;
            }
        }
    }
    i = (i == NULL) ? low : i->next;
    if (i != high) {
        int tempData = i->data;
        int tempCount = i->count;
        i->data = high->data;
        i->count = high->count;
        high->data = tempData;
        high->count = tempCount;
    }
    return i;
}

void quickSort(Node *low, Node *high) {
    if (low == NULL || high == NULL || low == high || low == high->next) {
        return;
    }
    Node *pivot = partition(low, high);
    quickSort(low, pivot->prev);
    quickSort(pivot->next, high);
    return;
}

void sortList(Node **head) {
    Node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }
    quickSort(*head, last);
}
}

void printList(Node *head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
int main() {
    Node *head = NULL;
    int input;
    printf("Enter positive integers to add to the linked list (enter 0 to stop):\n");
    do {
        scanf("%d", &input);
        if (input > 0) {
            head = insert(head, input);
        }
    } while (input != 0);
    printf("Sayıların ikili tabandaki karşılıkları:\n");
    Node *current = head;
    while (current != NULL) {
        printf("%d - ", current->data);
        int temp = current->data;

        while (temp != 0) {
            int ikilik = temp % 2;
            temp = temp / 2;
            printf("%d", ikilik);
            if(ikilik==1){
                current->count=current->count+1;
            }
        }
        printf("\n");
        current = current->next;
    }

    sortList(head);
    printf("Çıktı: ");
    current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    return 0;
}
