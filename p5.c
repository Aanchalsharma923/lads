#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int heap[SIZE];
int last = -1;

/* Heapify Up */
void heapifyUp(int index) {

    while (index > 0) {

        int parent = (index - 1) / 2;

        if (heap[index] < heap[parent]) {

            int temp = heap[index];
            heap[index] = heap[parent];
            heap[parent] = temp;

            index = parent;
        }

        else {
            break;
        }
    }
}

/* Heapify Down */
void heapifyDown(int index) {

    while (1) {

        int left = 2 * index + 1;
        int right = 2 * index + 2;

        int smallest = index;

        if (left <= last &&
            heap[left] < heap[smallest])
            smallest = left;

        if (right <= last &&
            heap[right] < heap[smallest])
            smallest = right;

        if (smallest != index) {

            int temp = heap[index];
            heap[index] = heap[smallest];
            heap[smallest] = temp;

            index = smallest;
        }

        else {
            break;
        }
    }
}

/* Insert Element */
void insert(int key) {

    if (last == SIZE - 1) {

        printf("Heap Overflow\n");
        return;
    }

    last++;

    heap[last] = key;

    heapifyUp(last);

    printf("Inserted %d\n", key);
}

/* Delete Minimum Element */
void deleteMin() {

    if (last == -1) {

        printf("Heap Underflow\n");
        return;
    }

    printf("Deleted Element: %d\n", heap[0]);

    heap[0] = heap[last];

    last--;

    heapifyDown(0);
}

/* Peek Minimum Element */
void peek() {

    if (last == -1) {

        printf("Heap is Empty\n");
        return;
    }

    printf("Top Priority Element: %d\n",
            heap[0]);
}

/* Display Heap */
void display() {

    if (last == -1) {

        printf("Heap is Empty\n");
        return;
    }

    printf("Heap Elements:\n");

    for (int i = 0; i <= last; i++)
        printf("%d ", heap[i]);

    printf("\n");
}

/* Main Function */
int main() {

    int choice, value;

    while (1) {

        printf("\n1. Insert");
        printf("\n2. Delete Min");
        printf("\n3. Peek");
        printf("\n4. Display");
        printf("\n5. Exit");

        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                printf("Enter value: ");
                scanf("%d", &value);

                insert(value);

                break;

            case 2:

                deleteMin();

                break;

            case 3:

                peek();

                break;

            case 4:

                display();

                break;

            case 5:

                exit(0);

            default:

                printf("Invalid Choice\n");
        }
    }

    return 0;
}
