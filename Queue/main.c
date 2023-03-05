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
void dequeue(Queue* q){//use pointer otherwise queue won't change the way you want to
    if(isNull(q)){//check front first
        return;
    }
    //what if there is then it follows like that :
    Node* temp=q->front; //keep front node in a temp node you'll free it soon
    q->front = q->front->next; //next front is next node
    //what if it was the last node that we dequeued, Let's Check
    if(q->front==NULL){
        //ups if it is here it means rear needs to me null too
        q->rear=NULL;
    }
    //time to free the memory from node
    free(temp);
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
int main() {
    Queue q;// create our queue
    q.front=q.rear=NULL;//we need to do it at first, you know because it is empty
    //we can add some values here
    enqueue(&q,34);//& is to send adress
    enqueue(&q,234);
    enqueue(&q,93);
    enqueue(&q,13);
    enqueue(&q,26);
    enqueue(&q,33369);
    display(&q);
    dequeue(&q);
    dequeue(&q);
    display(&q);
    printf("Let's test getFront function this is the result : %d\n", getFront(&q));
    return 0;
}
