#include <stdio.h>
#include <stdlib.h>

struct Node {
    int k1, k2;
    struct Node *l, *m, *r;
    int c;   // number of keys (1 or 2)
};

struct Node *root = NULL;

/* Create new node */
struct Node *newNode(int key) {
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->k1 = key;
    p->c = 1;
    p->k2 = 0;
    p->l = p->m = p->r = NULL;
    return p;
}

/* Insert key into a leaf with space */
void insertIntoNode(struct Node *p, int key, struct Node *child) {
    if (key < p->k1) {
        p->k2 = p->k1;
        p->k1 = key;
        p->r = p->m;
        p->m = child;
    } else {
        p->k2 = key;
        p->r = child;
    }
    p->c = 2;
}

/* Split a node */
struct Node *split(struct Node *p, int key, struct Node *child, int *upKey) {
    struct Node *newRight;
    int a, b, c;

    a = p->k1;
    b = p->k2;
    c = key;

    /* Sort keys */
    if (a > b) { int t=a; a=b; b=t; }
    if (a > c) { int t=a; a=c; c=t; }
    if (b > c) { int t=b; b=c; c=t; }

    *upKey = b;

    /* Left node keeps smallest key */
    p->k1 = a;
    p->c = 1;

    /* Right node */
    newRight = newNode(c);

    /* Fix children */
    if (child != NULL) {
        newRight->l = p->r;
        newRight->m = child;
        p->r = NULL;
    }

    return newRight;
}

/* Recursive insert */
struct Node *insertRec(struct Node *p, int key, int *upKey, int *splitFlag) {
    struct Node *newChild = NULL;

    /* Leaf */
    if (p->l == NULL) {
        if (p->c == 1) {
            insertIntoNode(p, key, NULL);
            *splitFlag = 0;
            return NULL;
        } else {
            *splitFlag = 1;
            return split(p, key, NULL, upKey);
        }
    }

    /* Internal node */
    if (key < p->k1)
        newChild = insertRec(p->l, key, upKey, splitFlag);
    else if (p->c == 2 && key > p->k2)
        newChild = insertRec(p->r, key, upKey, splitFlag);
    else
        newChild = insertRec(p->m, key, upKey, splitFlag);

    if (*splitFlag) {
        if (p->c == 1) {
            insertIntoNode(p, *upKey, newChild);
            *splitFlag = 0;
            return NULL;
        } else {
            return split(p, *upKey, newChild, upKey);
        }
    }
    return NULL;
}

/* Insert wrapper */
void insert(int key) {
    int upKey, splitFlag = 0;
    struct Node *newChild;

    if (root == NULL) {
        root = newNode(key);
        return;
    }

    newChild = insertRec(root, key, &upKey, &splitFlag);

    if (splitFlag) {
        struct Node *newRoot = newNode(upKey);
        newRoot->l = root;
        newRoot->m = newChild;
        root = newRoot;
    }
}

/* Correct inorder traversal */
void inorder(struct Node *p) {
    if (p == NULL) return;

    inorder(p->l);
    printf("%d ", p->k1);
    inorder(p->m);
    if (p->c == 2) {
        printf("%d ", p->k2);
        inorder(p->r);
    }
}

int main() {
    int keys[] = {10, 20, 30, 5, 35, 40, 1};
    int i;

    for (i = 0; i < 7; i++)
        insert(keys[i]);

    inorder(root);
    return 0;
}