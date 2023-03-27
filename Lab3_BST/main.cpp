#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Define the binary search tree node structure
struct node {
    int data;
    struct node* left;
    struct node* right;
};

// Function to create a new binary search tree node
struct node* new_node(int data) {
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a value into the binary search tree recursively
struct node* insert(struct node* node, int data) {
    // If the tree is empty, return a new node
    if (node == NULL) {
        return new_node(data);
    }
    //recursive is here
    // Otherwise, recur down the tree
    if (data < node->data) {
        node->left = insert(node->left, data);
    }
    else if (data > node->data) {
        node->right = insert(node->right, data);
    }
    //doesn't add a number twice
    else {
        printf("Value already exists in the tree\n");
        return node;
    }

    // Return the unchanged node pointer
    return node;
}

// Function to perform an inorder traversal of the binary search tree recursively
void inorder(struct node* node) {
    if (node == NULL) {
        return;
    }
    inorder(node->left);
    printf("%d ", node->data);
    inorder(node->right);
}


// Function to search for a value in the binary search tree recursively
int  binary_search(struct node* node, int min,int max) {
    int result=0;
    if (node == NULL ) {
        return 0;
    }
    //recursive + if it is not in right then it must be in left
    if ( node->data > max) {
        result=1;
        return result+binary_search(node->right, min,max);
    }
    else if(min> node->data ) {
        result=1;
        return result+binary_search(node->left, min,max);
    }
    binary_search(node->right, min,max);
    binary_search(node->left, min,max);
    return 0;
}

// Function to find the minimum value in the binary search tree recursively
struct node* find_min(struct node* node) {
    //go left until there is no place to go :')
    if (node == NULL) {
        return NULL;
    }

    if (node->left == NULL) {
        return node;
    }

    return find_min(node->left);
}


struct node* delete_node(struct node* root, int key) {
    // Base case: if the tree is empty or the key is not found, return null
    if (root == NULL) {
        return NULL;
    }
    else if (key < root->data) {
        // If the key is smaller than the root's data, move to the left subtree
        root->left = delete_node(root->left, key);
    }
    else if (key > root->data) {
        // If the key is larger than the root's data, move to the right subtree
        root->right = delete_node(root->right, key);
    }
    else {
        // If the key is found, delete the node and replace it with its successor
        if (root->left == NULL && root->right == NULL) {
            // Case 1: if the node to be deleted has no children, simply free the node
            free(root);
            root = NULL;
        }
        else if (root->left == NULL) {
            // Case 2: if the node to be deleted has only a right child, replace the node with its right child
            struct node* temp = root;
            root = root->right;
            free(temp);
        }
        else if (root->right == NULL) {
            // Case 2: if the node to be deleted has only a left child, replace the node with its left child
            struct node* temp = root;
            root = root->left;
            free(temp);
        }
        else {
            // Case 3: if the node to be deleted has both left and right children, replace the node with its successor
            struct node* temp = find_min(root->right);
            root->data = temp->data;
            root->right = delete_node(root->right, temp->data);
        }
    }
    return root;
}
struct node* binary_search_delete(struct node* node, int min,int max,struct node* root) {
    if (node == NULL ) {
        return NULL;
    }
    //recursive + if it is not in right then it must be in left
    if (node->data < min) {
        struct node* temp= node;



        while(node->left->data==NULL){
            delete_node(root,node->left->data);
            delete_node(root,node->data);
            node=node->left;
        }

    }
    else if(node->data > max){
        delete_node(root,node->data);
        return binary_search_delete(node->right, min,max,root);
    }
    binary_search_delete(node->right, min,max,root);
    binary_search_delete(node->left, min,max,root);
    return NULL;
}

// Main function to test the binary search tree functions
int main() {
    struct node* root = NULL;

    int arraylenght;
    printf("Please enter a number that defines your array leght\n");
    scanf("%d",&arraylenght);
    int array[arraylenght];
    srand(time(0));
    int i;
    for(i = 0; i < arraylenght; i++) {
       array[i] = rand() % 2001 - 1000;
    }

    // Diziyi yazdır
    printf("Dizi elemanları: ");
    for(i = 0; i < arraylenght; i++) {
        printf("%d ", array[i]);
    }
    // Insert values into the binary search tree
    for(i = 0; i < arraylenght; i++) {
        if(i==0){
            root = insert(root, array[i]);
        }
        insert(root, array[i]);;
    }



    // Print the inorder traversal of the binary search tree
    printf("-------------------- Inorder traversal: -------------------------\n");
    inorder(root);
    printf("\n");

    int min,max=0;
    printf("please enter the number that will be min value in BST\n");
    scanf("%d",&min);
    printf("please enter the number that will be max value in BST\n");
    scanf("%d",&max);
    printf("%d is min, %d is max \n",min,max);
    // Print the inorder traversal of the binary search tree after the deletion
    printf("--------------------- Inorder traversal: Before -------------------------\n");
    inorder(root);
    printf("\n");
    int numbersOufbound;

    numbersOufbound= binary_search(root,min,max);

    printf("!!!!!!!!!! %d numbers are out of your boundaries and will be deleted !!!!!!!!!!!!!!!\n",numbersOufbound);

    // Print the inorder traversal of the binary search tree after the deletion
    printf("--------------------- Inorder traversal: continue -------------------------\n");
    inorder(root);
    printf("\n");

    binary_search_delete(root,min,max,root);

    // Print the inorder traversal of the binary search tree after the deletion
    printf("--------------------- Inorder traversal: after-------------------------\n");
    inorder(root);
    printf("\n");

    printf("root : %d",root->data);
    return 0;
}

