#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//creating a node structure
//Queue = FIFO

typedef struct Node{
    int data;
    struct Node* next; //bir sonraki noda point eder //keeps next node's adress
}Node;

typedef struct {
    Node* front;//ilk element //points first node in queue
    Node* rear;//son element //point last element in queue
}Queue;

void enqueue(Queue* q, int data){
    Node* newNode = (Node*) malloc(sizeof (Node));//Node büyüklüğü kadar bellekte yer aç//open some space for new node
    newNode->data=data;//value of that node keeps
    newNode->next=NULL;//sonrasında bir element yok //no node after that one so it is null
    if(q->rear==NULL){
        q->front=newNode;
        q->rear=newNode;//both of them refers to new node because there weren't any node before in this case
        return;
    }
    q->rear->next=newNode;//connecting last two nodes
    q->rear=newNode;//new node is last node now, rear points it
}
bool isNull(Queue* q){
    if(q->front==NULL){//check front first
        printf("Sorry, There is no node here!");
        return true;
    }
    return false;
}
int dequeue(Queue* q){//use pointer otherwise queue won't change the way you want to
    if(isNull(q)){//check front first
        return -1;
    }
    //what if there is then it follows like that :
    Node* temp=q->front; //keep front node in a temp node you'll free it soon
    q->front = q->front->next; //next front is next node
    //what if it was the last node that we dequeued, Let's Check
    if(q->front==NULL){
        //ups if it is here it means rear needs to me null too
        q->rear=NULL;
    }
    int data = temp->data;
    //time to free the memory from node
    free(temp);
    return data;
}
int getFront(Queue* q){
    //for in case we need to same if front is null control
    if(isNull(q)){
        printf("I am returning -1 :)");
        return -1;
    }

    return q->front->data;//That is the way how we reach the front's data
}

void display(Queue* q){
    if(isNull(q)){//check front first
        return;
    }
    printf("~ ~ ~ ~ Queue elements ~ ~ ~ ~\n");
    Node* temp = q->front;//we will need it for the loop below
    while(temp != NULL){
        printf("%d ",temp->data);
        temp = temp->next; //it is like i=i+1; point to next node
    }
    printf("\n");
}

//Linkedlist

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

// Insert a new node with the given data at the end of the list
void insertAtEnd(Node** head, int data) {
    Node* node = createNode(data);
    node->next = *head;
    *head = node;
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
        printf("%d \n", head->data);
        head = head->next;
    }
    printf("\n");
}
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
    int array[]={1,3,4,6,11,8,13};
    Node *head = NULL;
    int i =0;
    //sıralı bir şekilde bağlı liste koyma
    for(i;i<=6;i++){
        printf("%d\n",array[i]);
        insertAtBeginning(&head, array[i]);
    }
    printf("~ ~ ~ ~Linked List ~ ~ ~ ~");
    printList(head);
    //ters sırada queue ye koyma
    Stack stack;
    stack.top=NULL;
    while (head != NULL) {
        push(&stack, head->data);
        head = head->next;
    }
    printStack(&stack);
    Queue q;// create our queue
    q.front=q.rear=NULL;//we need to do it at first, you know because it is empty

    while (!isEmpty(&stack)){
        //printf("ı am here");
        int value = pop(&stack); // pop the top element of the stack
        enqueue(&q,value);

    }
    display(&q);
    i=3;
    Stack stack_new;
    stack_new.top=NULL;
    int data;
    while (i!=0){
        data= dequeue(&q);
        push(&stack_new,data);
        i--;
    }
    printStack(&stack_new);
    int tek=0,cift=0;
    while(q.front==NULL){
        if(q.front->data%2==0){
            continue;
        }
        else{
            tek++;
        }
        q.front=q.front->next;
    }
    

    while(stack_new.top==NULL){
        if(stack_new.top->data%2==0){
            cift++;
        }
        else{
            continue;
        }
        stack_new.top=stack_new.top->next;
    }
    printf("%d queueu de tek var %d stackde cift var",tek,cift );

    return 0;
}
