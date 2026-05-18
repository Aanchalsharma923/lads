#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

/* Structure of Suffix Tree Node */
struct node {
    struct node *child[MAX_CHAR];
    int index;      // stores suffix index
};

/* Create a new node */
struct node* createNode() {

    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    for(int i=0;i<MAX_CHAR;i++)
        newNode->child[i] = NULL;

    newNode->index = -1;

    return newNode;
}

/* Insert suffix into tree */
void insertSuffix(struct node* root, char* suffix, int index){

    struct node* current = root;

    for(int i=0;suffix[i]!='\0';i++){

        int c = suffix[i];

        if(current->child[c] == NULL)
            current->child[c] = createNode();

        current = current->child[c];
    }

    /* store suffix index at leaf */
    current->index = index;
}

/* Build suffix tree */
void buildSuffixTree(struct node* root, char* text){

    int n = strlen(text);

    for(int i=0;i<n;i++)
        insertSuffix(root,text+i,i);
}

/* Display tree structure like Trie */
void display(struct node* root,int level){

    for(int i=0;i<MAX_CHAR;i++){

        if(root->child[i]!=NULL){

            /* indentation */
            for(int j=0;j<level;j++)
                printf("   ");

            printf("|----%c",i);

            /* print suffix index */
            if(root->child[i]->index!=-1)
                printf(" (%d)",root->child[i]->index);

            printf("\n");

            display(root->child[i],level+1);
        }
    }
}

/* print all suffix indexes below node */
void printIndexes(struct node* root){

    if(root==NULL)
        return;

    if(root->index!=-1)
        printf("%d ",root->index);

    for(int i=0;i<MAX_CHAR;i++)
        if(root->child[i]!=NULL)
            printIndexes(root->child[i]);
}

/* Pattern search */
void searchPattern(struct node* root,char* pattern){

    struct node* current=root;

    for(int i=0;pattern[i]!='\0';i++){

        int c = pattern[i];

        if(current->child[c]==NULL){
            printf("Pattern not found\n");
            return;
        }

        current=current->child[c];
    }

    printf("Pattern found at indexes: ");
    printIndexes(current);
    printf("\n");
}

int main(){

    char text[1000];
    char pattern[100];

    struct node* root=createNode();

    printf("Enter string: ");
    scanf("%s",text);

    buildSuffixTree(root,text);

    printf("\nSuffix Tree Structure:\n");
    display(root,0);
  
    printf("\nEnter pattern: ");
    scanf("%s",pattern);

    searchPattern(root,pattern);

    return 0;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// struct Node{
//     struct Node *child[26];
//     int eow;
// };
// struct Node *root = NULL;

// struct Node *createNode(){
//     struct Node *p = (struct Node*)malloc(sizeof(struct Node));
//     for(int i =0;i<26;i++){
//         p -> child[i] = NULL;
//     }
//     p -> eow = 0;
//     return p;
// }

// void suffix(char *word){
//     struct Node *p = root;
//     for(int i=0; word[i] != '\0';i++){
//         int idx = word[i] - 'a'; 
//         if(p->child[idx] == NULL){
//             p->child[idx] = createNode();
//         }
//         p = p->child[idx];
//     }
//     p -> eow = 1;
// }

// void insert(char word[]){
//     int n = strlen(word);
//     for(int i=0;i<n;i++){
//         suffix(word + i);
//     }
// }

// void displayyy(struct Node *q, int level,char word[]){
//     int n = strlen(word);
//     for(int i=0;i<26;i++){
//         if(q->child[i]!=NULL){
//             for(int j=0;j<level;j++){
//                 printf(" ");
//         }
//         printf("|--%c",i+'a');
//         if(q->child[i]->eow==1){
//             printf(" (%d)",n-level-1);
//         }
//         printf("\n");
//         displayyy(q->child[i], level+1,word);
//     }
// }
// }

// int main(){
//     root = createNode();
//     insert("coco");
//     displayyy(root, 0,"coco");
//     return 0;
// }
