#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

typedef struct Queue {
    Node** items;
    int front;
    int rear;
    int size;
} Queue;

Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert(Node** root, int data) {
    if (*root == NULL) {
        *root = create_node(data);
        return;
    }
    if (data > (*root)->data) {
        insert(&((*root)->left), data);
    } else if (data < (*root)->data) {
        insert(&((*root)->right), data);
    }
}

bool is_prime(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i <= (num/2); i++) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

Queue* create_queue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->items = (Node**)malloc(100 * sizeof(Node*));
    queue->front = -1;
    queue->rear = -1;
    queue->size = 100;
    return queue;
}

bool is_empty(Queue* queue) {
    return queue->front == -1 || queue->front > queue->rear;
}

void enqueue(Queue* queue, Node* node) {
    if (queue->rear == queue->size - 1) {
        printf("Queue overflow\n");
        return;
    }
    if (queue->front == -1) {
        queue->front = 0;
    }
    queue->rear++;
    queue->items[queue->rear] = node;
}

Node* dequeue(Queue* queue) {
    if (is_empty(queue)) {
        printf("Queue underflow\n");
        return NULL;
    }
    Node* node = queue->items[queue->front];
    queue->front++;
    return node;
}

int get_size(Queue* queue) {
    return queue->rear - queue->front + 1;
}
// Free memory allocated for binary tree
void free_tree(Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}
void print_bfs(Node* root) {
    Queue* queue = create_queue();
    enqueue(queue, root);
    while (!is_empty(queue)) {
        int size = get_size(queue);
        for (int i = 0; i < size; i++) {
            Node* current = dequeue(queue);
            printf("%d ", current->data);
            if (current->left != NULL) {
                enqueue(queue, current->left);
            }
            if (current->right != NULL) {
                enqueue(queue, current->right);
            }
        }
        printf("\n");
    }
}
void print_dfs(Node* root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->data);
    print_dfs(root->left);
    print_dfs(root->right);
}
void dfs(Node* node, int k, int level) {
    if (node == NULL) {
        return;
    }
    if (node->data ^ k) {
        if (is_prime(node->data ^ k)) {
            printf("Found prime number %d at level %d\n", node->data ^ k, level);
        }
    }
    dfs(node->left, k, level+1);
    dfs(node->right, k, level+1);
}
int main() {
    Node* root = NULL;

    // Insert positive integers into binary tree until 0 is entered
    int num;
    do {
        printf("Enter a positive integer (or 0 to stop): \n");
        scanf("%d", &num);
        if (num > 0) {
            insert(&root, num);
        }
    } while (num > 0);

    // Get k value from user
    int k;
    printf("Enter a value for k: \n");
    scanf("%d", &k);
    printf("~~~~ BFS ~~~~\n");
    print_bfs(root);

    // Traverse binary tree using BFS and perform XOR operation with k
    Queue* queue = create_queue();
    enqueue(queue, root);
    int level = 1;
    while (!is_empty(queue)) {
        int size = get_size(queue);
        for (int i = 0; i < size; i++) {
            Node* current = dequeue(queue);
            if (current->data ^ k) {
                if (is_prime(current->data ^ k)) {
                    printf("Found prime number %d at level %d\n", current->data ^ k, level);
                }
            }
            if (current->left != NULL) {
                enqueue(queue, current->left);
            }
            if (current->right != NULL) {
                enqueue(queue, current->right);
            }
            level++;
        }

    }
    printf("~~~~ DFS ~~~~\n");
    print_dfs(root);
    printf("\n");
    dfs(root,k,1);


    // Free memory allocated for binary tree
    free_tree(root);

    return 0;
}
