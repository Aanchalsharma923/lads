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
    p->k2 = 0;
    p->c = 1;
    p->l = p->m = p->r = NULL;
    return p;
}

/* Insert key into node with one key */
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
    int keys[3];
    struct Node *children[4];

    /* Collect keys */
    keys[0] = p->k1;
    keys[1] = p->k2;
    keys[2] = key;

    /* Sort keys */
    for (int i = 0; i < 3; i++)
        for (int j = i + 1; j < 3; j++)
            if (keys[i] > keys[j]) {
                int t = keys[i];
                keys[i] = keys[j];
                keys[j] = t;
            }

    *upKey = keys[1];

    /* Collect children */
    children[0] = p->l;
    children[1] = p->m;
    children[2] = p->r;
    children[3] = child;

    /* Left node */
    p->k1 = keys[0];
    p->c = 1;
    p->k2 = 0;

    /* Right node */
    struct Node *newRight = newNode(keys[2]);

    if (p->l != NULL) {
        p->l = children[0];
        p->m = children[1];

        newRight->l = children[2];
        newRight->m = children[3];
    }

    return newRight;
}

/* Recursive insert */
struct Node *insertRec(struct Node *p, int key, int *upKey, int *splitFlag) {
    struct Node *newChild = NULL;

    /* Leaf node */
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

/* Inorder traversal */
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
    int keys[] = {10, 20, 30, 5, 35, 40};
    int i;

    for (i = 0; i < 6; i++)
        insert(keys[i]);

    printf("Inorder traversal: ");
    inorder(root);

    return 0;
}
