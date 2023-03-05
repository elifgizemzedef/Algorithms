#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a single node of the stack
//LIFO=Stack
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Define a structure for the stack
typedef struct Stack {
    Node* top; //we will need only top element so just top is eneough
} Stack;
//to check isEmpty
bool isEmpty(Stack* stack){
    if(stack->top==NULL){
        //printf("Soryy stack is empty\n");
        return true;
    }
    return false;
}
void push(Stack* stack, int data) {
    Node* node= (Node*)malloc(sizeof (Node));
    node->data = data;
    if(isEmpty(stack)){//what if it is null
        node->next=NULL;
        stack->top = node;
        return;
    }
    node->next = stack->top;
    stack->top = node;
}

// Pop the top element off the stack and return its value
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("It returns -1\n");
        return -1;
    }
    Node* node = stack->top;
    int data = node->data;
    stack->top = node->next;//to don't lose the next data we need this
    free(node);
    return data;
}
// Print the elements of the stack
void printStack(Stack* stack) {
    if(isEmpty(stack)){
        return;
    }
    Node* node = stack->top;
    printf("~ ~ ~ ~ ~ Stack's elements ~ ~ ~ ~ \n");
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
int main() {
    Stack stack;
    stack.top=NULL;
    printf("is stack Empty? (1 is yes 0 is no) ~~ %d\n",isEmpty(&stack));
    push(&stack,532);
    push(&stack,53);
    push(&stack,52);
    push(&stack,32);
    push(&stack,222);
    printStack(&stack);
    int poped_data=pop(&stack);
    printf("poped data = %d",poped_data);
    poped_data=pop(&stack);
    printf("poped data = %d",poped_data);
    printStack(&stack);
    return 0;
}
