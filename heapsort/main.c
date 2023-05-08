#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *left, *right;
};

struct Node* createNode(int val) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int val) {
    if (root == NULL) return createNode(val);
    if (val < root->val)
        root->left = insert(root->left, val);
    else if (val > root->val)
        root->right = insert(root->right, val);
    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d\n", root->val);
        inorder(root->right);
    }
}
void heapify(struct Node* root) {
    if (root == NULL) return;
    if (root->left != NULL && root->left->val < root->val) {
        int temp = root->val;
        root->val = root->left->val;
        root->left->val = temp;
        heapify(root->left);
    }
    if (root->right != NULL && root->right->val < root->val) {
        int temp = root->val;
        root->val = root->right->val;
        root->right->val = temp;
        heapify(root->right);
    }
}

void convertToMinHeap(struct Node* root) {
    if (root == NULL) return;
    convertToMinHeap(root->left);
    convertToMinHeap(root->right);
    heapify(root);
}

void convertToMaxHeap(struct Node* root) {
    if (root == NULL) return;
    convertToMaxHeap(root->left);
    convertToMaxHeap(root->right);
    if (root->left != NULL && root->left->val > root->val) {
        int temp = root->val;
        root->val = root->left->val;
        root->left->val = temp;
        convertToMaxHeap(root->left);
    }
    if (root->right != NULL && root->right->val > root->val) {
        int temp = root->val;
        root->val = root->right->val;
        root->right->val = temp;
        convertToMaxHeap(root->right);
    }
}


int main() {
    struct Node* root = NULL;
    int val;
    int heap_type;

    printf("Heap tipini secin (1: min-heap, 2: max-heap): ");
    scanf("%d", &heap_type);

    while (1) {
        printf("Lutfen bir sayi girin (cikmak icin q): ");
        if (scanf("%d", &val) != 1) break;
        root = insert(root, val);
    }

    printf("Ikili arama agaci: ");
    inorder(root);
    printf("\n");

    if (heap_type == 1) {
        convertToMinHeap(root);
        printf("Min-heap: ");
    } else {
        convertToMaxHeap(root);
        printf("Max-heap: ");
    }

    inorder(root);
    printf("\n");

    return 0;
}


