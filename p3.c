#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

/* Node structure */
struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *root = NULL;

/* Create new red node */
struct Node* newNode(int data) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = data;
    p->color = RED;
    p->left = p->right = p->parent = NULL;
    return p;
}

/* Left rotation */
void leftRotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/* Right rotation */
void rightRotate(struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

/* Fix Red-Black Tree after insertion */
void fixInsert(struct Node *z) {
    while (z != root && z->parent->color == RED) {
        struct Node *p = z->parent;
        struct Node *gp = p->parent;

        if (p == gp->left) {
            struct Node *u = gp->right;  // uncle

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == p->right) {
                    z = p;
                    leftRotate(z);
                }
                p->color = BLACK;
                gp->color = RED;
                rightRotate(gp);
            }
        } else {
            struct Node *u = gp->left;

            if (u != NULL && u->color == RED) {
                p->color = BLACK;
                u->color = BLACK;
                gp->color = RED;
                z = gp;
            } else {
                if (z == p->left) {
                    z = p;
                    rightRotate(z);
                }
                p->color = BLACK;
                gp->color = RED;
                leftRotate(gp);
            }
        }
    }
    root->color = BLACK;
}

/* Insert operation */
void insert(int data) {
    struct Node *z = newNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    while (x != NULL) {
        y = x;
        if (data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;

    if (y == NULL)
        root = z;
    else if (data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsert(z);
}

/* Find minimum */
struct Node* minimum(struct Node *x) {
    while (x->left != NULL)
        x = x->left;
    return x;
}

/* Fix after deletion */
void fixDelete(struct Node *x) {
    while (x != root && x->color == BLACK) {
        struct Node *s;

        if (x == x->parent->left) {
            s = x->parent->right;

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if ((s->left == NULL || s->left->color == BLACK) &&
                (s->right == NULL || s->right->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->right == NULL || s->right->color == BLACK) {
                    s->left->color = BLACK;
                    s->color = RED;
                    rightRotate(s);
                    s = x->parent->right;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->right)
                    s->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {
            s = x->parent->left;

            if (s->color == RED) {
                s->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if ((s->left == NULL || s->left->color == BLACK) &&
                (s->right == NULL || s->right->color == BLACK)) {
                s->color = RED;
                x = x->parent;
            } else {
                if (s->left == NULL || s->left->color == BLACK) {
                    s->right->color = BLACK;
                    s->color = RED;
                    leftRotate(s);
                    s = x->parent->left;
                }
                s->color = x->parent->color;
                x->parent->color = BLACK;
                if (s->left)
                    s->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

/* Delete node */
void deleteNode(int data) {
    struct Node *z = root, *x, *y;

    while (z != NULL && z->data != data) {
        if (data < z->data)
            z = z->left;
        else
            z = z->right;
    }

    if (z == NULL) return;

    y = z;
    int yOriginalColor = y->color;

    if (z->left == NULL) {
        x = z->right;
        if (z->parent == NULL)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        if (x) x->parent = z->parent;
    }
    else if (z->right == NULL) {
        x = z->left;
        if (z->parent == NULL)
            root = x;
        else if (z == z->parent->left)
            z->parent->left = x;
        else
            z->parent->right = x;
        if (x) x->parent = z->parent;
    }
    else {
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;
        z->data = y->data;
    }

    if (yOriginalColor == BLACK && x != NULL)
        fixDelete(x);

    free(y);
}

/* Inorder traversal */
void inorder(struct Node *r) {
    if (r != NULL) {
        inorder(r->left);
        printf("%d(%s) ", r->data, r->color == RED ? "R" : "B");
        inorder(r->right);
    }
}

/* Driver */
int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);

    printf("Inorder after insert:\n");
    inorder(root);

    deleteNode(30);
    printf("\n\nAfter deleting 30:\n");
    inorder(root);

    return 0;
}
