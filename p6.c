#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26
#define MAX_LENGTH 50

/* Trie Node Structure */
struct node {
    struct node *child[ALPHABET_SIZE];   // Pointers to children nodes (a-z)
    int isEndOfWord;                     // 1 if word ends here
};

/* Function to create a new Trie node */
struct node* createNode() {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->isEndOfWord = 0;

    // Initialize all children as NULL
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->child[i] = NULL;

    return newNode;
}

/* Function to insert a word into Trie */
void insert(struct node* root, char* word) {

    struct node* current = root;

    // Traverse each character of word
    for (int i = 0; word[i] != '\0'; i++) {

        int index = word[i] - 'a';

        // If node does not exist, create it
        if (current->child[index] == NULL)
            current->child[index] = createNode();

        current = current->child[index];
    }

    // Mark end of word
    current->isEndOfWord = 1;
}

/* Function to search a complete word in Trie */
int search(struct node* root, char* word) {

    struct node* current = root;

    for (int i = 0; word[i] != '\0'; i++) {

        int index = word[i] - 'a';

        // If path doesn't exist, word not present
        if (current->child[index] == NULL)
            return 0;

        current = current->child[index];
    }

    // Word found only if endOfWord is marked
    return current->isEndOfWord;
}

/* Function to check prefix matching */
int prefixSearch(struct node* root, char* prefix) {

    struct node* current = root;

    for (int i = 0; prefix[i] != '\0'; i++) {

        int index = prefix[i] - 'a';

        if (current->child[index] == NULL)
            return 0;

        current = current->child[index];
    }

    // If traversal successful, prefix exists
    return 1;
}

/* Function to display Trie structure */
void display(struct node *q, int level) {

    for (int i = 0; i < 26; i++) {

        if (q->child[i] != NULL) {

            // Print indentation
            for (int j = 0; j < level; j++)
                printf("   ");

            printf("|----%c", i + 'a');

            // Mark end of word
            if (q->child[i]->isEndOfWord == 1)
                printf(" (*)");

            printf("\n");

            // Recursive traversal
            display(q->child[i], level + 1);
        }
    }
}

int main() {

    struct node* root = createNode();

    int n;
    char word[MAX_LENGTH + 1];
    char prefix[MAX_LENGTH + 1];

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter %d lowercase strings:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        insert(root, word);
    }

    printf("\nTrie Structure:\n");
    display(root, 0);

    /* Search operation */
    printf("\nEnter word to search: ");
    scanf("%s", word);

    if (search(root, word))
        printf("Word '%s' found in Trie\n", word);
    else
        printf("Word '%s' NOT found in Trie\n", word);

    /* Prefix search */
    printf("\nEnter prefix to search: ");
    scanf("%s", prefix);

    if (prefixSearch(root, prefix))
        printf("Prefix '%s' exists in Trie\n", prefix);
    else
        printf("Prefix '%s' does NOT exist in Trie\n", prefix);

    return 0;
}



// #include <stdio.h>
// #include <stdlib.h>

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

// void insert(char *word){
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

// void displayyy(struct Node *q, int level){
//     for(int i=0;i<26;i++){
//         if(q->child[i]!=NULL){
//             for(int j=0;j<level;j++){
//                 printf(" ");
//         }
//         printf("|--%c",i+'a');
//         if(q->child[i]->eow==1){
//             printf("*");
//         }
//         printf("\n");
//         displayyy(q->child[i], level+1);
//     }
// }
// }


// int main(){
//     root = createNode();
//     insert("cold");
//     insert("coffee");
//     insert("browine");
//     insert("pizza");
//     insert("fries");
//     displayyy(root, 0);
//     return 0;
// }  
