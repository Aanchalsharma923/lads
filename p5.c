#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int heap[SIZE];
int i = -1;

void heapify(int k) {
    while (k > 0) {
        int parent = (k - 1) / 2;

        if (heap[k] < heap[parent]) {
            int t = heap[k];
            heap[k] = heap[parent];
            heap[parent] = t;
            k = parent;
        } else {
            break;
        }
    }
}

void comparedown(int k) {
    while (1) {
        int left = 2 * k + 1;
        int right = 2 * k + 2;
        int smallest = k;

        if (left <= i && heap[left] < heap[smallest])
            smallest = left;

        if (right <= i && heap[right] < heap[smallest])
            smallest = right;

        if (smallest != k) {
            int t = heap[k];
            heap[k] = heap[smallest];
            heap[smallest] = t;
            k = smallest;
        } else {
            break;
        }
    }
}

void delete() {
    if (i >= 0) {
        printf("Deleted %d\n", heap[0]);
        heap[0] = heap[i];
        i--;
        comparedown(0);
    } else {
        printf("Heap Underflow\n");
    }
}

void insert(int key) {
    if (i == SIZE - 1) {
        printf("Overflow\n");
        return;
    }
    i++;
    heap[i] = key;
    heapify(i);
}

void display() {
    for (int k = 0; k <= i; k++) {
        printf(" %d", heap[k]);
    }
    printf("\n");
}

int main() {
    insert(10);
    insert(20);
    insert(30);
    insert(3);
    insert(4);
    insert(7);

    printf("Heap Data:\n");
    display();

    delete();

    printf("Heap Data After delete:\n");
    display();

    return 0;
}