#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
    char *name;
    struct node *next;
};

struct queue{
    struct node *front;
    struct node *rear;
    int size;
};

void initialize(struct queue *q){
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}   

struct node * createnode(char *name){
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    temp->name = (char *)malloc(strlen(name)+1);
    strcpy(temp->name,name);
    temp->next = NULL;
    return temp;
}

void insertqueue(struct queue *q, char *n){
    struct node *temp;
    temp = createnode(n);
    if(q->rear == NULL)
        q->front = q->rear = temp;
    else{
	    q->rear->next =  temp;
	    q->rear = temp;
    }
    temp->next = q->front;// to make circular queue
}
         
char* deletequeue(struct queue *q){
    struct node *temp;
    char *name =NULL;
    if(q->front == NULL) 
        return name;
    else if(q->front == q->rear){
        temp = q->front;  
        name = temp->name;
        q->front = q->rear = NULL;
    }
    else{
        temp = q->front;  
        q->rear->next = q->front->next;
        q->front = q->front->next;
        name = temp->name;
    }
    free(temp); 
    return name;
}

char* peekofqueue(struct queue q){
    char *name =NULL;
    if(q.front == NULL) 
        return name;
    else 
        name = q.front->name;      
    return name;
}

void printqueue(struct queue q){
    if(q.front == NULL)
        printf("\nQueue is empty");
    else{
        while(q.front!=q.rear){
            printf("%s->",q.front->name);
            q.front=q.front->next;
        }
        printf("%s->",q.front->name);   //when q.front = q.rear (last node)
    }
}
               
int instruction(){
    int choice;
    printf("\nMain Menu");
    printf("\n1. Insert in Queue");
    printf("\n2. Delete from Queue");
    printf("\n3. Peek in Queue");
    printf("\n4. Display Queue");
    printf("\n5. Quit from Menu");
    printf("\n Enter your choice[1-5]: ");
    scanf("%d", &choice);
    return choice;
}

void main(){
    struct queue q;
    int choice;
    char name[50];
    char *n;
    initialize(&q);
    while(1){
        choice = instruction();
        switch(choice){
            case 1: 
                printf("\n Enter the name to insert");
                scanf("%s",name);
                insertqueue(&q,name);
                break;
            case 2: 
                n = deletequeue(&q);
                if(n!=NULL)
		            printf("\n the deleted record of %s",n);
		        else
		            printf("\n Queue is empty");
                break;
            case 3: 
                n= peekofqueue(q);
                if(n!=NULL)
                    printf("\n Front element of the queue is:%s", n);
                else
		            printf("\n Queue is empty");
                break;
            case 4: 
                printqueue(q);
                break;
            case 5: 
                printf("\n exit from the program...");
                exit(0);
            default:
                printf("\n Incorrect choice... try again[1-5]:");
        }
    }
}