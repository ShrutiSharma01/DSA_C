#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

typedef struct node{
    struct node *prev;
    int data;
    struct node *next;
}node;


int instructions() {
    printf("1. Create list\n"
           "2. Display list\n"
           "3. Add at the beginning\n"
           "4. Add at the end\n"
           "5. Add after\n"
           "6. Add before\n"
           "7. Delete\n"
           "8. Reverse\n"
           "9. Quit\n");
    int ch;
    scanf("%d", &ch);
    return ch;
}

void createList(node **head, char *c) {
    if (*c == 'y' || *c == 'Y') {
        *head = NULL;
        printf("list created!");
        getch();
    } else {
        printf("opertaion cancelled!");
        getch();
    }

}

void display(node **head) {
    node *ptr = *head;
    if (ptr == NULL) {
        printf("list empty!");
        getch();
        return;
    }
    do {
        printf("data: %d\n", ptr->data);
        ptr = ptr->next;
    } while (ptr != NULL);
    getch();
}

void addBegin(node **head) {
    node *temp, *ptr;
    temp = (node *) malloc(sizeof(node));
    int data;
    printf("enter data:");
    scanf("%d", &data);
    temp->prev = NULL;
    temp->data = data;
    temp->next = *head;
    if (*head == NULL) {
        *head = temp;
    } else {
        ptr = *head;
        ptr->prev = temp;
        *head = temp;
    }
    printf("node added!");
    getch();
}

void addEnd(node **head) {
    node *temp, *ptr;
    ptr = *head;
    temp = (node *) malloc(sizeof(node));
    printf("enter data:");
    int data;
    scanf("%d", &data);
    temp->data = data;
    temp->next = NULL;
    if (*head == NULL) {
        temp->prev = NULL;
        *head = temp;
        printf("node added!");
        getch();
        return;
    }
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }
    ptr->next = temp;
    temp->prev = ptr;
    printf("node added!");
    getch();
}

void addAfter(node **head) {
    node *temp, *ptr;
    ptr = *head;
    temp = (node *) malloc(sizeof(node));
    printf("enter data:");
    int data;
    scanf("%d", &data);
    temp->data = data;
    printf("enter value to insert after:");
    scanf("%d", &data);
    while (ptr != NULL && ptr->data != data) {
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        printf("doesnt exist!");
        getch();
        return;
    } else if (ptr->next == NULL) {
        ptr->next = temp;
        temp->prev = ptr;
        temp->next = NULL;
    } else {
        temp->next = ptr->next;
        temp->prev = ptr;
        ptr->next->prev = temp;
        ptr->next = temp;
    }
    printf("node added!");
    getch();

}

void addBefore(node **head) {
    node *temp, *ptr;
    ptr = *head;
    temp = (node *) malloc(sizeof(node));
    printf("enter data:");
    int data;
    scanf("%d", &data);
    temp->data = data;
    printf("enter value to insert before:");
    scanf("%d", &data);
    while (ptr != NULL && ptr->data != data) {
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        printf("doesnt exist!");
        getch();
        return;
    } else if (ptr->prev == NULL) {
        temp->prev = NULL;
        temp->next = *head;
        ptr = *head;
        ptr->prev = temp;
        *head = temp;
    } else {
        temp->next = ptr->prev->next;
        temp->prev = ptr->prev;
        ptr->prev->next = temp;
        ptr->prev = temp;
    }
    printf("node added!");
    getch();
}

void deleteNode(node **head) {
    printf("enter value of node to delete:");
    int val;
    scanf("%d", &val);
    node *ptr, *temp;
    ptr = *head;
    while (ptr != NULL && ptr->data != val) {
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        printf("doesnt exist!");
        getch();
        return;
    } else if (ptr->next == NULL && ptr->prev == NULL) {
        *head = NULL;
    } else if (ptr->prev == NULL) {
        temp = ptr;
        ptr = ptr->next;
        ptr->prev = NULL;
        *head = ptr;
        free(temp);
    } else if (ptr->next == NULL) {
        temp = ptr;
        ptr->prev->next = NULL;
        free(temp);
    } else if (ptr->data == val) {
        temp = ptr;
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        free(temp);
    }
    printf("node deleted!");
    getch();
}

int main() {
    node *head = NULL;
    int data;
    char c;
    while (1) {
        int ch = instructions();
        switch (ch) {
            case 1:
                printf("doing this will delete any existing list, continue? (y/n)");
                fflush(stdin);
                scanf("%c", &c);
                createList(&head, &c);
                break;
            case 2:
                display(&head);
                break;
            case 3:
                addBegin(&head);
                break;
            case 4:
                addEnd(&head);
                break;
            case 5:
                addAfter(&head);
                break;
            case 6:
                addBefore(&head);
                break;
            case 7:
                deleteNode(&head);
                break;
            case 8:
                break;
            case 9:
                printf("exiting!");
                getch();
                exit(1);
            default:
                printf("invalid choice!\n");
                getch();
                break;
        }
    }
}
