//Ayush Dhoot
//20UCS045
//Section A1
//Date: June 1 , 2021
//Time: 5:05PM (4PM-6PM slot)

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int val;
    int greatest;
    struct node *next;
}node;

int instructions() {                                        //function for menu instructions
    printf("1. Push element\n"
           "2. Pop element\n"
           "3. Display top and largest element\n"
           "4. Display count of elements\n"
           "5. Quit\n");
    int ch;
    scanf("%d", &ch);
    return ch;
}

void push(node **top,int val,int *size) {               //function to push element to the top position
    node *temp = (node *) malloc(sizeof(node));
    if (!temp) {                                         //if temp fails to create
        printf("insufficient memory in heap!\n");
        return;
    }
    if (*top == NULL) {                                 //store the greatest element upto the current node
        temp->greatest = val;                          //to find the max element in O(1)
    } else {
        if (val > (*top)->greatest) {
            temp->greatest = val;
        } else {
            temp->greatest = (*top)->greatest;
        }
    }
    temp->val = val;
    temp->next = *top;                           //next of new node becomes the previous top
    *top = temp;                                //new node becomes the top element in the stack
    *size = *size + 1;
    printf("pushed %d\n", val);
}

void pop(node **top,int *size) {                //function to pop from the stack
    if (*top == NULL) {                         //if top is null then underflow
        printf("Underflow error!\n");
        return;
    }
    node *temp = *top;
    printf("greatest value in stack before pop: %d\n",
           temp->greatest); //finding the greatest element in the stack in O(1)
    printf("popped: %d\n", (*top)->val);
    *top = (*top)->next;                    //top moves to the next of the popped element
    *size = *size - 1;
    free(temp);                            //free memory
}

void peek(node **top) {                     //function to print the top element
    if (*top == NULL) {                     //if top is null then stack does not exist
        printf("stack is empty!\n");
        return;
    }
    printf("top: %d\n", (*top)->val);
    node *temp = *top;
    printf("greatest value in stack: %d\n", temp->greatest);
}

int main() {
    int size = 0;                                       //variable to store size of the stack
    node *top = NULL;
    int val;
    while (1) {                                         //loop to print menu until user exits
        int ch = instructions();
        switch (ch) {
            case 1:
                printf("enter value to push:");
                scanf("%d", &val);
                push(&top, val, &size);
                break;
            case 2:
                pop(&top, &size);
                break;
            case 3:
                peek(&top);
                break;
            case 4:
                printf("size of stack = %d\n", size);
                break;
            case 5:
                exit(1);
            default:
                printf("invalid input!\n");
                break;

        }
    }
}

//gcc 20UCS045.c -o 20UCS045
//./20UCS045
