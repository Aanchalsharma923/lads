#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void suffix(char *word){
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

void insert(char word[]){
    int n = strlen(word);
    for(int i=0;i<n;i++){
        suffix(word + i);
    }
}

void displayyy(struct Node *q, int level,char word[]){
    int n = strlen(word);
    for(int i=0;i<26;i++){
        if(q->child[i]!=NULL){
            for(int j=0;j<level;j++){
                printf(" ");
        }
        printf("|--%c",i+'a');
        if(q->child[i]->eow==1){
            printf(" (%d)",n-level-1);
        }
        printf("\n");
        displayyy(q->child[i], level+1,word);
    }
}
}

int main(){
    root = createNode();
    insert("coco");
    displayyy(root, 0,"coco");
    return 0;
}
