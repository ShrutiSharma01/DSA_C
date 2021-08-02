#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

typedef struct node{
    char *name;
    struct node *next;
}node;

void enqueue(node **front, node **rear, char* name, int *size) {
    node *temp, *ptr;
    temp = (node *) malloc(sizeof(node));
    temp->name = (char *) malloc(sizeof(char *));
    strcpy(temp->name, name);
    if (*front == NULL) {
        *front = temp;
        temp->next = *front;
        *rear = temp;
        *size = *size + 1;
    } else {
        ptr = *rear;
        ptr->next = temp;
        temp->next = *front;
        *rear = temp;
        *size = *size + 1;
    }
    printf("enqueued!\n");
    getch();
}

void dequeue(node **front, node **rear, int *size) {
    if (*front == NULL) {
        printf("empty!");
        getch();
        return;
    }
    *size = *size - 1;
    node *ptr = *front, *temp;
    printf("removed: %s\n", ptr->name);
    getch();
    if (*size == 0) {
        *front = NULL;
        *rear = NULL;
        return;
    }
    temp = ptr;
    ptr = ptr->next;
    *front = ptr;
    free(temp);
    ptr = *rear;
    ptr->next = *front;
}

void display(node **front,int *size) {
    if (*size == 0) {
        printf("queue empty!\n");
        getch();
        return;
    }
    node *ptr = *front;
    do {
        printf("name: %s\n", ptr->name);
        ptr = ptr->next;
    } while (ptr != *front);
    getch();
}

void peek(node **front, char* name){

}

int instructions() {
    printf("1. Insert\n"
           "2. Delete\n"
           "3. Peek\n"
           "4. Display (display the queue)\n"
           "5. Quit\n");
    int ch;
    scanf("%d", &ch);
    return ch;
}

int main() {
    node *front = NULL;
    node *rear = NULL;
    int size = 0;
    char name[100];
    while (1) {
        int ch = instructions();
        switch (ch) {
            case 1:
                printf("enter name:\n");
                scanf("%s", name);
                enqueue(&front, &rear, name, &size);
                break;
            case 2:
                dequeue(&front, &rear, &size);
                break;
            case 3: //peek
                break;
            case 4:
                display(&front, &size);
                break;
            case 5:
                printf("exiting\n");
                getch();
                exit(69);
            default:
                printf("Invalid choice enter again");
                getch();
                break;
        }
    }
}
