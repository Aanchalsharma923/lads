#include <stdio.h>
#include <stdlib.h>

struct node{
    int data ;
    struct node *left;
    struct node *right;
    int rthread;
};

struct node *root= NULL;

struct node* createnode(int data){
    struct node* newnode= (struct node*)malloc(sizeof(struct node));
    newnode->data=data;
    newnode->left = newnode->right= NULL;
    newnode->rthread=1;
    return newnode;
}

void insert(int key)
{
    struct node *ptr=root;
    struct node *parent=NULL;

    while(ptr!=NULL)
    {
        parent=ptr;
        if(key<ptr->data)
        ptr=ptr->left;
        else{
            if(ptr->rthread==0)
            ptr=ptr->right;
            else break;
            
        }
    }
    struct node *newnode= createnode(key);
    if(parent==NULL)
    {
        root=newnode;
    }
    else if(key<parent->data)
    {
        parent->left=newnode;
        newnode->right=parent;
    }
    else{
        newnode->right=parent->right;
        parent->right=newnode;
        parent->rthread=0;
         
    }

        
}

struct node *leftmost(struct node *node){
    while(node!=NULL && node->left!=NULL)
    node= node->left;
    return node;
}

void inorder(){
    struct node *cur=leftmost(root);
    while(cur!=NULL)
    {
        printf("%d ", cur->data);
        if(cur->rthread==1)
        cur=cur->right;
        else
        cur=leftmost(cur->right);
    }       
}
void preorder()
{
    struct node *cur = root;

    while (cur != NULL)
    {
        // Visit the node
        printf("%d ", cur->data);

        // If left child exists, go left
        if (cur->left != NULL)
        {
            cur = cur->left;
        }
        else
        {
            // Follow threads until a real right child is found
            while (cur != NULL && cur->rthread == 1)
                cur = cur->right;

            if (cur != NULL)
                cur = cur->right;
        }
    }
}


void main(){
    printf("no.of nodes to be inserted: ");
    int n; scanf("%d", &n);
    printf("enter the nodes: ");    
    for(int i=0;i<n;i++){
        int data; scanf("%d", &data);
        insert(data);
    }  
    printf("inorder traversal: ");  
    inorder();                      
    printf("\npreorder traversal: ");  
    preorder(); 
    return;
}
