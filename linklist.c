#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <process.h>
#include<conio.h>
typedef struct Fruit{
    char *name; // Name of the fruit
    char *color; // Color of the fruit
    struct Fruit *nextFruit; // Pointer to next fruit
}fruit;
fruit *head=NULL,*head2=NULL;
void insert_node(){
    fruit *temp=(fruit*)malloc(sizeof(fruit)),*ptr,*prev;
    temp->name=(char *)malloc(sizeof(char*));
    temp->color=(char*)malloc(sizeof(char*));
    printf("enter name and color of fruit:");
    scanf("%s %s",temp->name,temp->color);
    temp->nextFruit=NULL;
    char t[100];
    if(head==NULL)head=temp;
    else{
        if(strcmp(head->name,temp->name)>0)
        {
            temp->nextFruit=head;
            head = temp;
            printf("%s of %s color has been inserted.\n",head->name,head->color);
            return;
        }
        ptr=head;
        prev=ptr;
        while(ptr && (strcmp(ptr->name,temp->name))<=0){
            prev=ptr;
            ptr=ptr->nextFruit;
        }
        temp->nextFruit=prev->nextFruit;
        prev->nextFruit=temp;
    }
    printf("%s of %s color has been inserted.\n",temp->name,temp->color);

}
void print_list(){
    fruit *ptr=head;
    if(head==NULL){
        printf("list empty!\n");

        return;
    }
    while(ptr!=NULL){
        printf("name: %s color: %s\n",ptr->name,ptr->color);
        ptr=ptr->nextFruit;
    }

}
void delete_node(){
    fruit *temp=(fruit*)malloc(sizeof(fruit)),*ptr=head,*prev;
    temp->name=(char*)malloc(sizeof(char*));
    printf("enter name of fruit to delete:");
    scanf("%s",temp->name);
    if(head==NULL){
        printf("No fruits in the list!");
        return;
    }
    else{
        if(strcmp(head->name,temp->name)==0){
            printf("%s of %s color has been removed!\n",head->name,head->color);
            head=head->nextFruit;
            free(ptr);

            return;
        }
        else{
            prev=ptr;
            while(ptr&&strcmp(ptr->name,temp->name)!=0){
                prev=ptr;
                ptr=ptr->nextFruit;
            }
            if(ptr){
                printf("%s of %s color has been removed!\n",ptr->name,ptr->color);
                prev->nextFruit=ptr->nextFruit;
                free(ptr);

                return;
            }
            else{
                printf("does not exist!\n");

                return;
            }
        }
    }

}
void reverse_list(){
    fruit *ptr;
    ptr=head;
    while(ptr!=NULL){
        fruit *temp=(fruit*)malloc(sizeof(fruit));
    }
}
void instructions(){
    while(true) {
        printf("Enter choice:\n1. Insert a new fruit\n2. Delete the fruit\n3. Print the list of fruits\n4. Reverse the list of fruits\n5. Exit menu\n");
        int ch;
        fflush(stdin);
        scanf("%d",&ch);
        switch (ch) {
            case 1:
                insert_node();
                break;
            case 2:
                delete_node();
                break;
            case 3:
                print_list();
                break;
            case 4:
                reverse_list();
                break;
            case 5:
                printf("exiting!");
                exit(0);
            default:printf("invalid input\n");

                break;
        }
    }
}
int main(){
    instructions();
}
