#include <stdio.h>

#define MAX 10

struct node{
    int x1, y1, x2, y2;
    char name[10];
};

struct node tree[MAX];
int count = 0;

int overlap(struct node a, struct node b){
    // left side
    if(a.x2 < b.x1)
        return 0;

    // right side
    if(a.x1 > b.x2)
        return 0;

    // below
    if(a.y2 < b.y1)
        return 0;

    // above
    if(a.y1 > b.y2)
        return 0;

    return 1;
}

void insert(struct node r){
    tree[count] = r;
    count++;
}

void search(struct node q){
    printf("Overlapping rectangles:\n");

    for(int i=0; i<count; i++){
        if(overlap(tree[i], q)){
            printf("%s\n", tree[i].name);
        }
    }
}

int main(){
    struct node r1 = {1,1,3,3,"R1"};
    struct node r2 = {4,4,6,6,"R2"};
    struct node r3 = {2,5,5,8,"R3"};

    insert(r1);
    insert(r2);
    insert(r3);

    struct node query = {2,2,5,5,"Q"};

    search(query);

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>

// #define MAX 10  

// typedef struct {
//     int x1, y1, x2, y2;
//     char name[10];
// } Rectangle;

// Rectangle tree[MAX];
// int count = 0;

// int isOverlap(Rectangle a, Rectangle b) {
//     // If one rectangle is completely to left/right/top/bottom → no overlap
//     if (a.x2 < b.x1 || a.x1 > b.x2 || 
//         a.y2 < b.y1 || a.y1 > b.y2)
//         return 0;

//     return 1; // Overlap exists
// }

// void insert(Rectangle r) {
//     if (count < MAX) {
//         tree[count++] = r;
//     } else {
//         printf("Tree is full!\n");
//     }
// }

// void search(Rectangle query) {
//     printf("Rectangles overlapping with query:\n");

//     for (int i = 0; i < count; i++) {
//         if (isOverlap(tree[i], query)) {
//             printf("%s ", tree[i].name);
//         }
//     }
//     printf("\n");
// }

// int main() {

//     Rectangle r1 = {1, 1, 3, 3, "R1"};
//     Rectangle r2 = {4, 4, 6, 6, "R2"};
//     Rectangle r3 = {2, 5, 5, 8, "R3"};
//     Rectangle r4 = {7, 2, 9, 4, "R4"};

//     insert(r1);
//     insert(r2);
//     insert(r3);
//     insert(r4);

//     Rectangle query = {2, 2, 5, 5, "Q"};

//     search(query);

//     return 0;
// }