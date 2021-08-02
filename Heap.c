#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define size 1000

// Declaration of heap
struct heap{
    int *array;   // array is pointer to integer
    int count;    // number of elements in heap right now
    int capacity;    // size of heap - maximum size of array
    int heap_type;    // min = 0 or max = 1
};

// Creating / Initializing heap
struct heap* createHeap(int capacity){
    struct heap *temp = (struct heap*) malloc(sizeof(struct heap));
    temp->count = -1;
    temp->capacity = capacity;
    temp->array = (int*) malloc(capacity * sizeof(int));
    for(int i = 0; i < capacity; i++){
        temp->array[i] = -1;
    }
    return temp;
}

// Index of leftchild of parentnode
int leftChild(struct heap* h, int i){
    if(i < 0 || i > h->count){
        return -1;
    }
    int left = 2 * i + 1;
    return left;
}

// Index of rightchild of parentnode
int rightChild(struct heap* h, int i){
    if(i < 0 || i > h->count){
        return -1;
    }
    int right = 2 * i + 2;
    return right;
}

// Getting maximum or minimum value of heap
int getMaxMin(struct heap* h){
    if(h->count == -1){
        return -1;
    }
    return h->array[0];    // root contains max value in maxheap and min value in minheap
}

// Swap
void swap(int *arr, int a, int b){
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

// Heapify - top to bottom - TC = O(logn)
void percolateDown(struct heap* h, int i){
    int max, temp;
    int left = leftChild(h, i);
    int right = rightChild(h, i);
    if(left != -1 && h->array[left] > h->array[i])
        max = left;
    else
        max = i;
    if(right != -1 && h->array[right] > h->array[max])
        max = right;
    if(max != i){
        swap(h->array, i, max);
        percolateDown(h, max);
    }
    return;
}

// Index of parent of childnode
int parent(struct heap* h, int i){
    if(i <= 0 || i > h->count){
        return -1;
    }
    int ans;
    if((i - 1) >= 0) return (i - 1) / 2;
    else return -1;
}

// Resize heap
void resizeHeap(struct heap* h){
    h->array = (int*) realloc(h->array, 2 * (h->capacity) * sizeof(int));
}

// Insertion in binary heap
// TC for inserting single element = O(logn), TC for inserting n elements = O(n logn)
void insert(struct heap* h, int data){
    if((h->count) + 1 == h->capacity){
        resizeHeap(h);
    }
    h->count++;
    h->array[h->count] = data;
    
    if(h->count == 0) return;
    int i = parent(h, h->count);
    int temp = h->count;
    while(i >= 0 && h->array[temp] > h->array[i]){
        swap(h->array, i, temp);
        temp = i;
        i = parent(h, i);    // percolate up
    }
}

int search(struct heap* h, int key, int capacity){
    if(h == NULL){
        return -1;
    }
    for(int i = 0; i <= h->count; i++){
        if(h->array[i] == key){
            return i;
        }
    }
    return -1;
}

// Deleting element in heap - always deleted from root
// TC of deleting max element = O(logn)
// TC finding max element = O(1)
int deleteMax(struct heap* h){
    if(h->count == -1){
        return -1;
    }
    int data = h->array[0];
    h->array[0] = h->array[h->count];
    h->count--;
    percolateDown(h, 0);
    return data;
}

void print(struct heap* h){
    for(int i = 0; i <= h->count; i++){
        printf("%d ", h->array[i]);
    }
    printf("\n");
}

int get_choice() {
    int choice;
    printf("\n AVL TREE MENU");
    printf("\n1. Create:");
    printf("\n2. Insert:");
    printf("\n3. Search:");
    printf("\n4. Delete:");
    printf("\n5. Print:");
    printf("\n6. Quit:");
    printf("\n\nEnter Your Choice[1-6]:");
    scanf("%d", &choice);

    return choice;
}

int main(){
    int x, temp;
    int choice;
    struct heap *h = NULL;
    while(1) {
    choice = get_choice();
    switch(choice) {
            case 1:
                h = createHeap(size);
                break;

            case 2:
                printf("\nEnter a key to be inserted:");
                scanf("%d", &x);
                insert(h, x);
                break;

            case 3:
                printf("\nSearch a key:");
                scanf("%d", &x);
                temp = search(h, x, size);
                if(temp == -1)
                    printf("\nKey does not exist");
                else
                    printf("\nKey exists");
                break;

            case 4:
                temp = deleteMax(h);
                if(temp == -1)
                    printf("Heap is empty");
                else
                    printf("Element deleted is %d\n", temp);
                break;

            case 5:
                print(h);
                break;

            case 6:
                printf("\n Exit from Program...ta ta...phir milenge");
                exit(0);

            default:
                printf("\n Invalid Choice TRY AGAIN[1-6]:");
        }
    }
    return 0;
}