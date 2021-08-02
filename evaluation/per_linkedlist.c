/***************************************

** Assignment Lab Evaluation_1 for section_Q2

Q1. Use the below given code to input n person records and store these records in a linked
list.
Now split this linked list in four linked list on the basis of age by following the policy
below:
Age 0-18 Linked list-1
Age 19-44 Linked list -2
Age 45-60 Linked list-3
Above age 60 Linked list-4

**************************************

** Solution by Author: Mukesh K Jadon
**/ 



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// we want to store person type records in the linked list

struct person
{
   char name[50];
   int age;
};


struct node
{
   struct person per;   // data part of node contains person record
   struct node *next;  // self referential pointer 
};

// Function to input a person data (name and age)
  
struct person getdata()
{
   struct person p;
   printf("\n Enter name:");
   scanf("%s", p.name);
   printf("\n Enter age:");
   scanf("%d",&p.age);
   return p;
}

// Function  to create a new node and to add name and age to that node.

struct node * create_node(struct person p)
{
   struct node *temp;
   temp = (struct node *) malloc(sizeof(struct node));
   temp->per = p;
   temp->next = NULL;
   return temp;
}

//Function to insert a new node at beginning of the linked list. 

struct node * insert_begin(struct node *head, struct person p)
{
  struct node *temp = create_node(p);
  if( head !=NULL)
       temp->next = head;
    
  return temp;
}

//Function to insert a new node at end of the linked list.

struct node * insert_end(struct node *head, struct person p)
{
  struct node *cur = head;
  struct node *temp = create_node(p);
  if( head ==NULL)
       head  = temp;
  else
    {
      while(cur->next != NULL)
        cur=  cur->next;
      cur->next = temp;
    }
 return head;
}


void split_age(struct node *head,struct node **head1,struct node**head2,struct node **head3,struct node**head4)
{
     struct node *cur = head;
	 while(cur!=NULL)
     {
         //printf("%d->",cur->per.age);
		 if(cur->per.age<=18)
          *head1 = insert_end(*head1,cur->per);
         else
           if(cur->per.age<=44)
             *head2 = insert_end(*head2,cur->per);
           else
            if(cur->per.age<=60)
             *head3  = insert_end(*head3,cur->per);
            else
             *head4 = insert_end(*head4,cur->per);
             
             cur =  cur->next;
     }
} // End of function split       

// Function to display a linked list

void display_list(struct node *head)
{
    printf("head->");
    while(head!= NULL)
     {
       printf("%s|%d ->", head->per.name,head->per.age);
       head =   head->next;
     }
    printf("NULL");
}


// Function to display menu choices

int instruction()
{
   int choice;
   
   printf("\nMain Menu");
   printf("\n1. Insert in beginning of a linked list");
   printf("\n2. Insert at end of  a linked list");
   printf("\n3. Split Linked List on the basis of age");
   printf("\n4. Display Linked list[age group:0-18]");
   printf("\n5. Display Linked list[age group:19-44]");
   printf("\n6. Display Linked list[age group:45-60]");
   printf("\n7. Display Linked list[age group:60 above]");
   printf("\n8. Display Main list:");
   printf("\n9. Quit from Menu");
   printf("\n Enter your choice[1-9]:");
   scanf("%d", &choice);
   return choice;
}

void main()
{
  struct node *head = NULL;
  struct node *head1=NULL,*head2=NULL,*head3=NULL,*head4=NULL;
  struct person p;
  char name[50];
  char *n;
  int choice,age;
  while(1)
   {
     choice = instruction();
     switch(choice)
     {
       case 1: printf("\n Enter person details:");
               p =  getdata(); 
               head = insert_begin(head, p);
               break;
       case 2: printf("\n Enter person details:");
               p =  getdata(); 
               head = insert_end(head, p);
               break;
       case 3: split_age(head, &head1,&head2,&head3,&head4);
               break;

       case 4: printf("\nLinked list of age group [0-18]:");
               display_list(head1);
               break; 
       case 5: printf("\nLinked list of age group [19-44]:");
               display_list(head2);
               break; 
       case 6: printf("\nLinked list of age group [45-60]:");
               display_list(head3);
               break; 
       case 7: printf("\nLinked list of age group [Above 60]:");
               display_list(head4);
               break; 
       case 8: printf("\nMain Linked list");
               display_list(head);
               break;
       case 9: printf("\n exit from the program menu...");
               exit(0);
       default: printf("\n Enter correct menu choice[1-9]:");
     } // End of switch
     
   }// End of while
   
} // End of function main()     
