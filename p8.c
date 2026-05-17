#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVEL 3

// Node structure
struct Node {
    int value;
    struct Node* forward[MAX_LEVEL + 1];
};

// Create new node
struct Node* createNode(int value, int level) {
    struct Node* n = (struct Node*)malloc(sizeof(struct Node));
    n->value = value;
    for (int i = 0; i <= MAX_LEVEL; i++) {
        n->forward[i] = NULL;
    }
    return n;
}

// Random level (simple)
int randomLevel() {
    int level = 0;
    while (rand() % 2 && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

// Insert function
void insert(struct Node* header, int* level, int value) {
    struct Node* update[MAX_LEVEL + 1];
    struct Node* current = header;

    // Traverse from top level
    for (int i = *level; i >= 0; i--) {
        while (current->forward[i] != NULL &&
               current->forward[i]->value < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }

    current = current->forward[0];

    // Insert only if not present
    if (current == NULL || current->value != value) {
        int rlevel = randomLevel();

        if (rlevel > *level) {
            for (int i = *level + 1; i <= rlevel; i++) {
                update[i] = header;
            }
            *level = rlevel;
        }

        struct Node* newNode = createNode(value, rlevel);

        for (int i = 0; i <= rlevel; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
    }
}

// Display skip list
void display(struct Node* header, int level) {
    for (int i = 0; i <= level; i++) {
        struct Node* node = header->forward[i];
        printf("Level %d: ", i);
        while (node != NULL) {
            printf("%d ", node->value);
            node = node->forward[i];
        }
        printf("\n");
    }
}

// Main
int main() {
    int level = 0;

    struct Node* header = createNode(-1, MAX_LEVEL);

    insert(header, &level, 3);
    insert(header, &level, 6);
    insert(header, &level, 7);
    insert(header, &level, 9);
    insert(header, &level, 12);

    display(header, level);

    return 0;
}