#include <stdio.h>
#include <stdlib.h>

struct Node{
    struct Node *child[26];
    int eow;
};
struct Node *root = NULL;

struct Node *createNode(){
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    for(int i =0;i<26;i++){
        p -> child[i] = NULL;
    }
    p -> eow = 0;
    return p;
}

void insert(char *word){
    struct Node *p = root;
    for(int i=0; word[i] != '\0';i++){
        int idx = word[i] - 'a';
        if(p->child[idx] == NULL){
            p->child[idx] = createNode();
        }
        p = p->child[idx];
    }
    p -> eow = 1;
}

void displayyy(struct Node *q, int level){
    for(int i=0;i<26;i++){
        if(q->child[i]!=NULL){
            for(int j=0;j<level;j++){
                printf(" ");
        }
        printf("|--%c",i+'a');
        if(q->child[i]->eow==1){
            printf("*");
        }
        printf("\n");
        displayyy(q->child[i], level+1);
    }
}
}


int main(){
    root = createNode();
    insert("cold");
    insert("coffee");
    insert("browine");
    insert("pizza");
    insert("fries");
    displayyy(root, 0);
    return 0;
}  