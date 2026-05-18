#include <stdio.h>
#include <stdlib.h>

#define SPACE 5

struct Node {
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

struct Node *root = NULL;

/* Create Node */
struct Node* createNode(int data) {
    struct Node *n = (struct Node*)malloc(sizeof(struct Node));

    n->data = data;
    n->left = n->right = NULL;
    n->height = 1;

    return n;
}

/* Height */
int height(struct Node *n) {
    if (n == NULL)
        return 0;

    return n->height;
}

/* Maximum */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Balance Factor */
int balanceFactor(struct Node *n) {
    if (n == NULL)
        return 0;

    return height(n->left) - height(n->right);
}

/* Right Rotation */
struct Node* rightRotate(struct Node *y) {

    struct Node *x = y->left;
    struct Node *t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

/* Left Rotation */
struct Node* leftRotate(struct Node *x) {

    struct Node *y = x->right;
    struct Node *t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* Insert */
struct Node* insert(struct Node *node, int data) {

    if (node == NULL)
        return createNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);

    else if (data > node->data)
        node->right = insert(node->right, data);

    else
        return node;

    node->height = 1 + max(height(node->left),
                            height(node->right));

    int bf = balanceFactor(node);

    /* LL */
    if (bf > 1 && data < node->left->data)
        return rightRotate(node);

    /* RR */
    if (bf < -1 && data > node->right->data)
        return leftRotate(node);

    /* LR */
    if (bf > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    /* RL */
    if (bf < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/* Minimum Node */
struct Node* minValueNode(struct Node *node) {

    struct Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

/* Delete */
struct Node* deleteNode(struct Node *root, int key) {

    if (root == NULL)
        return root;

    /* BST Delete */
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else {

        /* One child or no child */
        if (root->left == NULL || root->right == NULL) {

            struct Node *temp;

            if (root->left)
                temp = root->left;
            else
                temp = root->right;

            /* No child */
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }

            /* One child */
            else {
                *root = *temp;
            }

            free(temp);
        }

        /* Two children */
        else {

            struct Node *temp =
                minValueNode(root->right);

            root->data = temp->data;

            root->right =
                deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    /* Update height */
    root->height = 1 + max(height(root->left),
                            height(root->right));

    int bf = balanceFactor(root);

    /* LL */
    if (bf > 1 &&
        balanceFactor(root->left) >= 0)
        return rightRotate(root);

    /* LR */
    if (bf > 1 &&
        balanceFactor(root->left) < 0) {

        root->left = leftRotate(root->left);

        return rightRotate(root);
    }

    /* RR */
    if (bf < -1 &&
        balanceFactor(root->right) <= 0)
        return leftRotate(root);

    /* RL */
    if (bf < -1 &&
        balanceFactor(root->right) > 0) {

        root->right = rightRotate(root->right);

        return leftRotate(root);
    }

    return root;
}

/* Inorder */
void inorder(struct Node *root) {

    if (root != NULL) {

        inorder(root->left);

        printf("%d ", root->data);

        inorder(root->right);
    }
}

/* Print Tree */
void printTree(struct Node *root, int space) {

    if (root == NULL)
        return;

    space += SPACE;

    printTree(root->right, space);

    printf("\n");

    for (int i = SPACE; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    printTree(root->left, space);
}

/* Main */
int main() {

    int ch, data;

    while (1) {

        printf("\n1.Insert");
        printf("\n2.Delete");
        printf("\n3.Inorder");
        printf("\n4.Print Tree");
        printf("\n5.Exit");

        printf("\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {

            case 1:

                printf("Enter data: ");
                scanf("%d", &data);

                root = insert(root, data);

                break;

            case 2:

                printf("Enter data: ");
                scanf("%d", &data);

                root = deleteNode(root, data);

                break;

            case 3:

                printf("Inorder: ");
                inorder(root);

                printf("\n");

                break;

            case 4:

                printTree(root, 0);

                printf("\n");

                break;

            case 5:

                exit(0);

            default:

                printf("Invalid Choice");
        }
    }

    return 0;
}
