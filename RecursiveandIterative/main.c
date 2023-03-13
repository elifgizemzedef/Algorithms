#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** headRef, int newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = newData;
    newNode->next = (*headRef);
    (*headRef) = newNode;// changing the head this is the way list's head shows last element of list. kinda like stack
}
int isPrimenumber(int n) {//works like everyone knows :)
    if (n <= 1) {
        return 0;
    }
    for (int i = 2; i <= (n/2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void printPrimes(struct Node* head) {
    printf("Prime numbers in the list: ");
    struct Node* current = head;
    while (current != NULL) { //we need it, just like in arrays but be reach next data with pointers
        if (isPrimenumber(current->data)) {
            printf("%d ", current->data);
        }
        current = current->next;
    }
    printf("\n");
}

int isHarshad(int n) {
    int sum = 0;
    int temp = n;
    while (temp >= 1) {//this way it doesn't matter how many number it has in it eventually ı get all of them
        sum += temp % 10;
        temp /= 10;
    }
    return n % sum == 0;
}

void printHarshads(struct Node* head) {
    printf("Harshad numbers in the list: ");
    struct Node* current = head;
    while (current != NULL) {
        if (isHarshad(current->data)) {
            printf("%d ", current->data);
        }
        current = current->next;
    }
    printf("\n");
}
int isSortedIterative(struct Node* head) {
    // check if list is null or next node of head doesn't exist
    if (head == NULL || head->next == NULL) {
        return 1;
    }
    struct Node* current = head;
    while (current->next != NULL) {//we don't use recursive here so continue to do that until next is null
        if (current->data < current->next->data) {//one element eneough to be not sortet so return 0 then
            printf("List is not sorted,you added numbers from smallest to biggest \n");
            return 0;
        }
        current = current->next;//we need to continue with next node
    }
    printf("List is sorted, no worries. Everyone makes mistakes\n");
    return 1;
}

int isSortedRecursive(struct Node* head) {
    // check if list is null or next node doesn't exist
    if (head == NULL || head->next == NULL) {
        printf("we can say yes you added numbers from smallest to biggest \n");
        return 1;
    }
    //if list not sorted it will go into that if
    if (head->data < head->next->data) {
        printf("ops, everyone makes mistakes\n");
        return 0;
    }
    //we look list two by two
    return isSortedRecursive(head->next);
}



int main() {
    struct Node* head = NULL;
    //For the consider head points the last element (just saying to make all of it clear for you)
    int n, num;
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("~ ~ ~ ~ Please Enter the elements: ~ ~ ~ ~\n");
    //Take numbers like it is given
    for (int i = 0; i < n; i++) {
        printf("element %d is : ",(i+1));
        scanf("%d", &num);
        push(&head, num);
    }
    int sortwith;
    printf("~ ~ ~ ~ How do you want to check if list is sorted or not. Recursively or iteratively ~ ~ ~ ~  \n");
    printf("~ ~ ~ ~ 1 is Recursive 0 is iterative ~ ~ ~ ~  \n");
    scanf("%d",&sortwith);
    //printf("%d",sortwith);
    if(sortwith){
        printf("-------- Checking with recursive --------\n");
        if (isSortedRecursive(head)) {
            printPrimes(head);
        } else {
            printHarshads(head);
        }
    }
    else{
        printf("-------- Checking with Iterative --------\n");
        if (isSortedIterative(head)) {
            printPrimes(head);
        } else {
            printHarshads(head);
        }
    }


    return 0;
}
