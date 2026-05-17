#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

struct node{
    int data;
    int color;
    struct node*left;
    struct node*right;
    struct node*parent;
};
struct node* root = NULL;

struct node* newNode(int data){
    struct node* p = (struct node*)malloc(sizeof(struct node));
    p->data = data;
    p->left = p->right = p->parent = NULL;
    p->color = RED;

    return p;
}
void leftRotation(struct node* y){
    struct node *z = y->parent, *x=y->right, *t=y->right->left;
    y->right = t;
    x->parent=z;
    x->left = y;
    y->parent =x;

    if(t!=NULL){
        t->parent = y;
    }
    if(z==NULL){
        root = x;
    }else if(z->right ==y){
        z->right =x;
    }else{
        z->left = x;
    }
}

void rightRotation(struct node *y){
    struct node *z = y->parent, *x = y->left, *t = y->left->right;
    y->left = t;
    x->parent = z;
    x->right = y;
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

void fixInsert(struct node*z){
    while(z!=root && z->parent->color == RED){
        struct node* P=z->parent;
        struct node* GP=z->parent->parent;
        struct node* U=NULL;
        if(GP==NULL){
            break;
        }
        if(P == GP->right){
            U= GP->left;
        }else{
            U = GP->right;
        }

        if(U!=NULL && U->color==RED ){
            // Recoloringgg
            P->color = BLACK;
            U->color = BLACK;
            GP->color = RED;
        }else{
            if(P == GP->right && z==P->right){
                // ll
                P->color = BLACK;
                GP->color = RED;
                leftRotation(GP);
            }else if(P == GP->right && z==P->left){
                // lr
                z->color = BLACK;
                GP->color = RED;
                rightRotation(P);
                leftRotation(GP);
            }else if(P==GP->left && z==P->left){
                // rr
                P->color = BLACK;
                GP->color = RED;
                rightRotation(GP);
            }else{
                // rl
                z->color =BLACK;
                GP->color=RED;
                leftRotation(P);
                rightRotation(GP);
            }
        }
        z = GP;
    }
    root->color = BLACK;
}

void insert(int data){
    struct node* z = newNode(data);
    struct node* y = NULL;
    struct node* x = root;
    if(x==NULL){
        root = z;
        z->parent = NULL;
    }else{
        while(x != NULL){
            y = x;
            if(x->data > data){
                x = x->left;
            }else{
                x = x->right;
            }
        }
        if(y->data > data){
            y->left =z;
        }else{
            y->right =z;
        }
        z->parent = y;
    }
    fixInsert(z);
}
void inorder(struct node*root){
    if(root!=NULL){
        inorder(root->left);
        printf("%d (%d)",root->data,root->color);
        inorder(root->right);

    }
}

int main(){
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    inorder(root);
    return 0;
}