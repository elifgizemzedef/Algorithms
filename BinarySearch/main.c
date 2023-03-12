#include <stdio.h>
#include <stdlib.h>

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

// Function to perform a preorder traversal of the binary search tree recursively
void preorder(struct node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    preorder(node->left);
    preorder(node->right);
}

// Function to perform a postorder traversal of the binary search tree recursively
void postorder(struct node* node) {
    if (node == NULL) {
        return;
    }
    postorder(node->left);
    postorder(node->right);
    printf("%d ", node->data);
}

// Function to search for a value in the binary search tree recursively
struct node* binary_search(struct node* node, int key) {
    if (node == NULL || node->data == key) {
        return node;
    }
    //recursive + if it is not in right then it must be in left
    if (node->data < key) {
        return binary_search(node->right, key);
    }

    return binary_search(node->left, key);
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

// Function to find the successor of a node in the binary search tree recursively
struct node* find_successor(struct node* node, struct node* root) {
    //one right and go left as much as possible
    if (node->right != NULL) {
        return find_min(node->right);
    }

    struct node* successor = NULL;
    while (root != NULL) {
        if (node->data < root->data) {
            successor = root;
            root = root->left;
        }
        else if (node->data > root->data) {
            root = root->right;
        }
        else {
            break;
        }
    }

    return successor;
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


// Main function to test the binary search tree functions
int main() {
    struct node* root = NULL;

    // Insert values into the binary search tree
    root = insert(root, 15);
    insert(root, 5);
    insert(root, 3);
    insert(root, 12);
    insert(root, 10);
    insert(root, 13);
    insert(root, 16);
    insert(root, 20);
    insert(root, 18);
    insert(root, 23);
    insert(root, 6);
    insert(root, 7);

    // Print the inorder traversal of the binary search tree
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");

    // Print the preorder traversal of the binary search tree
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");

    // Print the postorder traversal of the binary search tree
    printf("Postorder traversal: ");
    postorder(root);
    printf("\n");

    // Search for a value in the binary search tree
    int key = 1456;
    struct node* result = binary_search(root, key);
    if (result == NULL) {
        printf("Value %d not found in the tree\n", key);
    }
    else {
        printf("Value %d found in the tree\n", key);
    }

    // Find the minimum value in the binary search tree
    struct node* min_node = find_min(root);
    printf("Minimum value in the tree: %d\n", min_node->data);

    // Find the successor of a node in the binary search tree
    int successor_key = 5;
    struct node* node = binary_search(root, successor_key);
    if (node == NULL) {
        printf("Value %d not found in the tree\n", successor_key);
    }
    else {
        struct node* successor = find_successor(node, root);
        if (successor == NULL) {
            printf("Value %d does not have a successor\n", successor_key);
        }
        else {
            printf("Successor of value %d: %d\n", successor_key, successor->data);
        }
    }

    // Delete a key from the binary search tree
    int delete_key = 5;
    root = delete_node(root, delete_key);

    // Print the inorder traversal of the binary search tree after the deletion
    printf("Inorder traversal after deleting %d: ", delete_key);
    inorder(root);
    printf("\n");

    delete_key = 15;
    root = delete_node(root, delete_key);

    // Print the inorder traversal of the binary search tree after the deletion
    printf("Inorder traversal after deleting %d: ", delete_key);
    inorder(root);
    printf("\n");
    printf("%d",root->data);
    return 0;
}

