#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct Node {
    int data;
    struct Node *left, *right;
    bool lthread, rthread;
};

struct Node *root = NULL;

void insertTBT(int key) {
    struct Node *ptr = root;
    struct Node *parent = NULL;

    while (ptr != NULL) {
        if (key == ptr->data)
            return;

        parent = ptr;

        if (key < ptr->data) {
            if (ptr->lthread == 0)
                ptr = ptr->left;
            else
                break;
        } else {
            if (ptr->rthread == 0)
                ptr = ptr->right;
            else
                break;
        }
    }

    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = key;
    newNode->lthread = 1;
    newNode->rthread = 1;

    if (parent == NULL) {
        root = newNode;
        newNode->left = NULL;
        newNode->right = NULL;
    }
    else if (key < parent->data) {
        newNode->left = parent->left;
        newNode->right = parent;
        parent->lthread = 0;
        parent->left = newNode;
    }
    else {
        newNode->left = parent;
        newNode->right = parent->right;
        parent->rthread = 0;
        parent->right = newNode;
    }
}

struct Node* leftMost(struct Node *n) {
    while (n != NULL && n->lthread == 0)
        n = n->left;
    return n;
}

void inorderTBT() {
    struct Node *cur = leftMost(root);

    while (cur != NULL) {
        printf("%d ", cur->data);

        if (cur->rthread == 1)
            cur = cur->right;
        else
            cur = leftMost(cur->right);
    }
}

void preorderTBT() {
    struct Node *cur = root;

    while (cur != NULL) {
        printf("%d ", cur->data);

        if (cur->lthread == 0)
            cur = cur->left;
        else if (cur->rthread == 0)
            cur = cur->right;
        else {
            while (cur != NULL && cur->rthread == 1)
                cur = cur->right;

            if (cur != NULL)
                cur = cur->right;
        }
    }
}

void inorderRecursive(struct Node *node) {
    if (node == NULL)
        return;

    if (node->lthread == 0)
        inorderRecursive(node->left);

    printf("%d ", node->data);

    if (node->rthread == 0)
        inorderRecursive(node->right);
}

void preorderRecursive(struct Node *node) {
    if (node == NULL)
        return;

    printf("%d ", node->data);

    if (node->lthread == 0)
        preorderRecursive(node->left);

    if (node->rthread == 0)
        preorderRecursive(node->right);
}


int main() {
    int n;
    printf("Enter number of nodes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int val = rand() % 1000;
        insertTBT(val);
    }

    clock_t start, end;

    printf("\nRecursive Inorder Traversal:\n");
    start = clock();
    inorderRecursive(root);
    end = clock();
    printf("\nTime (Recursive Inorder): %lf seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    printf("\nStackless Inorder Traversal:\n");
    start = clock();
    inorderTBT();
    end = clock();
    printf("\nTime (Non-Recursive Inorder): %lf seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    printf("\n\nRecursive Preorder Traversal:\n");
    start = clock();
    preorderRecursive(root);
    end = clock();
    printf("\nTime (Recursive Preorder): %lf seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    printf("\nStackless Preorder Traversal:\n");
    start = clock();
    preorderTBT();
    end = clock();
    printf("\nTime (Non-Recursive Preorder): %lf seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}
