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
void insertionSort(Node* head);
void selectionSort(Node* head);
int isTauNumber(int n);
int countTauNumbers(Node* head);
int isPrime(int num);
int reverse(int num);
int isLasaNumber(int num);
int countLasaNumbers(Node* head);

#define MAX_NUMS 1000

int main() {
    FILE *fp;
    char filename[] = "C://Users//elifg//CLionProjects//Lab5//Sayilar.txt";
    int nums[MAX_NUMS];
    int num_count = 0;
    int num;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Dosya açılamadı\n");
        exit(1);
    }

    while (fscanf(fp, "%d", &num) == 1 && num_count < MAX_NUMS) {
        nums[num_count++] = num;
    }

    fclose(fp);
    int i;
    for (i = 0; i < num_count; i++) {
        printf("%d ", nums[i]);
    }

    Node* head = NULL;


    for (i = 0; i < num_count; i++) {
        insertNode(&head, nums[num_count-i-1]);
    }
    printf("\n~~~~ List Before Sorted ~~~~\n");
    printf("!!! .txt file has been modified to see if sorting is working correctly.\n\n");
    printList(head);
    printf("\n\n List printed");
    int TauNumbers = countTauNumbers(head);
    int LasaNumbers = countLasaNumbers(head);
    printf("\n Tau Numbers: %d\n", TauNumbers);
    printf(" Lasa Numbers: %d\n\n", LasaNumbers);

    if(TauNumbers>=LasaNumbers){
        printf("~~~~ Sorted with Insertion ~~~~\n");
        insertionSort(head);
    }
    else if(TauNumbers<LasaNumbers){
        printf("~~~~ Sorted with Bubble ~~~~\n");
        bubbleSort(head);
    }
    else if(TauNumbers  == 0 && LasaNumbers == 0){
        printf("~~~~ Sorted with Selection ~~~~\n");
        selectionSort(head);
    }
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
void insertionSort(Node* head) {
    Node* ptr1;
    Node* ptr2;
    int temp;

    for (ptr1 = head->next; ptr1 != NULL; ptr1 = ptr1->next) {
        temp = ptr1->data;
        for (ptr2 = ptr1->prev; ptr2 != NULL && ptr2->data > temp; ptr2 = ptr2->prev) {
            ptr2->next->data = ptr2->data;
        }
        if(ptr2 != NULL) {
            ptr2->next->data = temp;
        } else {
            head->data = temp;
        }
    }
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

int isTauNumber(int n) {
    int divisors = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            divisors++;
        }
    }
    if (n % divisors == 0) {
        return 1;
    }
    return 0;
}

int countTauNumbers(Node* head) {
    int count = 0;
    while (head != NULL) {
        if (isTauNumber(head->data)) {
            count++;
        }
        head = head->next;
    }
    return count;
}

int isPrime(int num){
    if(num<=1){
        return 0;
    }
    for(int i=2;i<num/2;i++){
        if(num % i == 0){
            return 0;
        }
    }
    return 1;
}
int reverse(int num){
    int reverse=0;
    while(num > 0){
        reverse = reverse * 10 + (num%10);
        num = num /10;
    }
    return reverse;
}
int isLasaNumber(int num){
    int reversedNumber= reverse(num);
    if (num == reverse){
        return 0;
    }
    else if(isPrime(num), isPrime(reversedNumber)){
        return 1;
    }
    else{
        return 0;
    }
}

int countLasaNumbers(Node* head){
    int count=0;
    while (head != NULL){
        if(isLasaNumber(head->data)){
            count++;
        }
        head = head ->next;
    }
    return count;
}