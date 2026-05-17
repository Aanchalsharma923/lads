#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

struct Node
{
    int data, color;
    struct Node *left, *right, *parent;
};
struct Node *root = NULL;

struct Node *newNode(int data){
    struct Node *p = (struct Node *)malloc(sizeof(struct Node));
    p->data = data;
    p->color = RED;
    p->left = p->right = NULL;
    p->parent = NULL;
    return (p);
}

void leftRotation(struct Node *y){
    struct Node *z = y->parent, *x = y->right, *t = y->right->left;
    y->right = t;
    x->left = y;
    x->parent = z;
    y->parent = x;

    if (t != NULL){
        t->parent = y;
    }
    if (z == NULL){
        root = x;
    }else if (z->right == y){
        z->right = x;
    }else{
        z->left = x;
    }
}

void rightRotation(struct Node *y){
    struct Node *z = y->parent, *x = y->left, *t = y->left->right;

    y->left = t;
    x->right = y;

    x->parent = z;
    y->parent = x;
    if (t != NULL){
        t->parent = y;
    }

    if (z == NULL){
        root = x;
    }else if (z->right == y){
        z->right = x;
    }else{
        z->left = x;
    }
}

void fixInsert(struct Node *z){
    while (z != root && z->parent->color == RED){

        struct Node *P = z->parent;
        struct Node *GP = z->parent->parent;
        struct Node *U = NULL;

        if (GP == NULL){
            break;
        }
        if (P == GP->right){
            U = GP->left;
        }else{
            U = GP->right;
        }
        // check uncle
        if (U != NULL && U->color == RED){
            P->color = BLACK;
            U->color = BLACK;
            GP->color = RED;
        }else{
            
            if (z == P->left && P == GP->right){ // logic for LR Roatation
                z->color = BLACK;
                GP->color = RED;
                rightRotation(P);
                
                leftRotation(GP);
            }else if (z == P->right && P == GP->right){ // logic for LL Rotation
                P->color = BLACK;
                GP->color = RED;
                leftRotation(GP);
            }else if (z == P->left && P == GP->left){ // logic for RR rotation
                P->color = BLACK;
                GP->color = RED;
                rightRotation(GP);
            }else{ // logic for RL Rotation
                z->color = BLACK;
                GP->color = RED;
                leftRotation(P);
                rightRotation(GP);
            }
        }
        z = GP;
    }
    root->color = BLACK;
}
void insert(int data){

    struct Node *z = newNode(data);
    struct Node *y = NULL;
    struct Node *x = root;

    if (x == NULL){
        root = z;
        z->parent = NULL;
    }else{
        while (x != NULL)
        {
            y = x;
            if (data < x->data)
                x = x->left;
            else
                x = x->right;
        }
        if (y->data > data)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->parent = y;
    }
    fixInsert(z);
}
void inorder(struct Node *q){
    if (q != NULL){
        inorder(q->left);
        printf("%d (%d)", q->data, q->color);
        inorder(q->right);
    }
}
int main(){
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    insert(50);
    insert(60);
    insert(70);
    insert(80);
    inorder(root);
}