#include<stdio.h>
#include<stdlib.h>
#define SPACE 5
struct Node{
    struct Node *left;
    int data;
    struct Node *right;
    int h;
};
struct Node *root=NULL;
struct Node * STACK[50];
int top=-1;
void PUSH(struct Node *q){
    STACK[++top]=q;
}
struct Node * POP(){
    return(STACK[top--]);
}
struct Node *peep(){
    return(STACK[top]);
}
int maximum(struct Node *left, struct Node *right){
    int a=left!=NULL?left->h:0;
    int b=right!=NULL?right->h:0;
    return (a>b?a:b);
}
int balanceFactor(struct Node *q){
    int a=q->left!=NULL?q->left->h:0;
    int b=q->right!=NULL?q->right->h:0;
    return (a-b);
}
struct Node * leftRotation(struct Node *q){
    struct Node *t=q->right;
    struct Node *s=t->left;
    t->left=q;
    q->right=s;
    q->h=1+maximum(q->left, q->right);
    t->h=1+maximum(t->left, t->right);
    return(t);
}
struct Node * rightRotation(struct Node *q){
    struct Node *t=q->left;
    struct Node *s=t->right;
    t->right=q;
    q->left=s;
    q->h=1+maximum(q->left, q->right);
    t->h=1+maximum(t->left, t->right);
    return(t);
}
struct Node *insert(struct Node *N, int data){
    if(N==NULL){
        struct Node *p=(struct Node *)malloc(sizeof(struct Node));
        p->left=p->right=NULL;
        p->h=1;
        p->data=data;
        return p;
    }
    else{
        if(N->data>data){
            N->left=insert(N->left, data);
        }
        else{
            N->right=insert(N->right, data);
        }
    }
    N->h=1+maximum(N->left, N->right);
    int bf= balanceFactor(N);
    if(bf<-1 && data>N->right->data){
        N=leftRotation(N);
    }
    if(bf<-1 && data<N->right->data){
        N->right=rightRotation(N->right);
        N=leftRotation(N);
    }
    if(bf>1 && data<N->left->data){
        N=rightRotation(N);
    }
    if(bf>1 && data>N->left->data){
        N->left=leftRotation(N->left);
        N=rightRotation(N);
    }
    return N;
}
void delete(struct Node *q, int data){
    struct Node *parent = NULL;
    while(q!=NULL){
        if(q->data==data){
            //two child
            if(q->left!=NULL && q->right!=NULL){
                struct Node *t=q->right;
                PUSH(q);
                while(t->left!=NULL){
                    PUSH(t);
                    parent=t;
                    t=t->left;
                }
                q->data=t->data;
                q=t;
            }
            if(q->left!=NULL && q->right==NULL){//left child only
                if(parent==NULL){
                    root=q->left;
                }
                else{
                    if(parent->left==q){
                        parent->left=q->left;
                    }
                    else{
                        parent->right=q->left;
                    }
                }
            }
            if(q->left==NULL && q->right!=NULL){//right child only
                if(parent==NULL){
                    root=q->right;
                }
                else{
                    if(parent->left==q){
                        parent->left=q->right;
                    }
                    else{
                        parent->right=q->right;
                    }
                }
            }
            if(q->left==NULL && q->right==NULL){//No child only
                if(parent==NULL){
                    root=NULL;
                }
                else{
                    if(parent->left==q){
                        parent->left=NULL;
                    }
                    else{
                        parent->right=NULL;
                    }
                }
            }
            free(q); // delete the node q
            while(top!=-1){
                struct Node *p = POP();
                int bf = balanceFactor(p);
                int flag=0;
                p->h = 1+maximum(p->left,p->right);
                if(bf<-1 && balanceFactor(p->right)<=0){
                    p=leftRotation(p);
                    flag=1;
                }
                if(bf<-1 && balanceFactor(p->right)>0){
                    p->right=rightRotation(p->right);
                    p=leftRotation(p);
                    flag=1;
                }
                if(bf>1 && balanceFactor(p->left)>=0){
                    p=rightRotation(p);
                    flag=1;
                }
                if(bf>1 && balanceFactor(p->left)<0){
                    p->left=leftRotation(p->left);
                    p=rightRotation(p);
                    flag=1;
                }
                if(flag==1){
                    struct Node *parent = peep();
                    if(parent==NULL){
                        return;
                    }
                    if(parent->data<p->data){
                        parent->right=p;
                    }
                    else{
                        parent->left=p;
                    }
                }
            }
            printf("\nData Deleted Successfully");
            return;
        }
        else if(q->data>data){
            PUSH(q);
            parent=q;
            q=q->left;
        }
        else{
            PUSH(q);
            parent=q;
            q=q->right;
        }
    }
    printf("\nData Not found");
    top=-1; // empty stack;
    return;
}
void inorder(struct Node *q){
    if(q!=NULL){
        inorder(q->left);
        printf(" %d",q->data);
        inorder(q->right);
    }
}
/* Print BST like tree (sideways) */
void printTree(struct Node* root, int space) {
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
int main(){
    int ch, data;
    while(1){
        printf("\n1: Insert \n2: delete \n3: Inorder \n4: Print Tree\n5: Exit");
        printf("\n Enter Your choice");
        scanf("%d",&ch);
        switch(ch){
            case 1:
                printf("Enter The data to be Inserted");
                scanf("%d", &data);
                root = insert(root,data);
                break;
            case 2:
                printf("Enter The data to be deleted");
                scanf("%d", &data);
                delete(root,data);
                break;
            case 3:
                inorder(root);
                break;
            case 4:
                printTree(root, 0);
                break;
            case 5:
                exit(1);
            default:
                printf("Unrecognized command...");
        }
    }
    return 1;
}



// #include<stdio.h>
// #include <stdlib.h>


// struct node{
//     struct node *left;
//     struct node *right;
//     int data;
//     int h;
// };

// struct node *root = NULL;

// int maxx(struct node*a ,struct node* b){
//     int x = a!=NULL ? a->h:0;
//     int y = b!=NULL ? b->h:0;
//     return x>y?x:y;
// }

// int balancefactor(struct node*a ,struct node* b){
//     int x = a!=NULL ? a->h:0; 
//     int y = b!=NULL ? b->h:0 ;
//     return x-y;
// }

// struct node* leftRotation(struct node* q){
//     struct node * t = q -> right;
//     struct node * s = t -> left;
//     t -> left = q;
//     q -> right = s;
//     q->h=1+maxx(q->left,q->right);
//     t->h=1+maxx(t->left,t->right);
//     return t;
// }
// struct node* rightRotation(struct node* q){
//     struct node * t = q -> left;
//     struct node * s = t -> right;
//     t -> right = q;
//     q -> left = s;
//     q->h=1+maxx(q->left,q->right);
//     t->h=1+maxx(t->left,t->right);
//     return t;
// }

// struct node* insert(struct node* N,int data){

//     if(N==NULL){
//     struct node* p = (struct node *)(malloc(sizeof(struct node)));
//     p->data = data;
//     p->left = p->right = NULL;
//     p->h = 1;   
//     return p;
//     }
//     else {
//         if(data>N->data){
//         N->right = insert(N->right,data);
//         }
//         else{
//             N->left = insert(N->left,data);
//         }
//     }
//     N->h = 1+maxx(N->left,N->right);

//     // balance factor 
//     int bf = balancefactor(N->left,N->right);  
//     //avl rule hold or not 
//     if(bf<-1 && data < N->right->data){     //lr rotation
//         N -> right = rightRotation(N -> right);
//         N = leftRotation(N);
//     }
//     if(bf<-1 && data > N->right->data){       //ll rotatin
//         N = leftRotation(N);
        
//     }
//     if(bf>1 && data < N->left->data){       //rr rotatin
//         N = rightRotation(N);

//     }
//     if(bf>1 && data > N->left->data){       //rl rotatin
//         N -> left = leftRotation(N -> left);
//         N = rightRotation(N);
//     }
//     return N;
// }

// void inorder(struct node* root){
//     if(root != NULL){
//         inorder(root -> left);
//         printf("%d ",root-> data);
//         inorder(root -> right);
//     }
// }
// int main(){
//     root = insert(root,10);
//     root = insert(root,20);
//     root = insert(root,30);
//     root = insert(root,15);
//     root = insert(root,40);
//     inorder(root);
//     return 0;
// }