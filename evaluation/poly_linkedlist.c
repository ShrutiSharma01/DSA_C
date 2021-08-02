/****************************
** Assignment Lab Evaluation_1 for Section- P2

Q1. Write C code to add two algebraic expressions of the form:
a[n]*x^n + ... a[0]*x^0+ ... a[-m]*x^-m using linked list data structures (Symbol ^ denotes
power of or exponent operator).
Expression_1 = +100*X^2000 +10*X^1000 -10*X^500 -10*X^-1000
Expression_2 = +200*X^3000 +10*X^1000 +110*X^500 +1000*X^0 +10*X^-1000
Expression_1 + Expression_2 = +200*X^3000 +100*X^2000 +20*X^1000 +100*X^500
+1000*X^0
*****************************

** Solution by Author: Mukesh K Jadon
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// we want to store Polynomial equation in a linkedlist

struct polynode
{
   int coeff;   // data part of node contains person record
   int pow;
   struct polynode *next;  // self referential pointer 
};


// Function  to create a new polynode and to add Coeff and power to that polynode.

struct polynode * create_polynode(int coeff, int pow)
{
   struct polynode *temp;
   temp = (struct polynode *) malloc(sizeof(struct polynode));
   temp->coeff = coeff;
   temp->pow = pow;
   temp->next = NULL;
   return temp;
}

//Function to insert a new polynode at end of the linked list.

struct polynode * insert_sorted(struct polynode *head, int coeff, int pow)
{
  
   struct polynode *temp, *prev, *cur;
    temp = create_polynode(coeff,pow);
     if(head ==NULL)
          head = temp;
     else
       if(head->pow<pow)
        {
             temp->next = head;
             head =temp;
        }
       else
         {
              prev= cur = head;
             
              while(cur!=NULL && cur->pow>pow)
               {
                   prev = cur;
                   cur = cur->next;       
                }
                    prev->next  = temp;
                    temp->next  = cur;
                    
            }
            
	 return head;
}
/*The create polynomial function
 * Will Create a linked list of Polynomial equation
*/
struct polynode * create_polynomial(struct polynode  * head)
 {
    char choice; 
    int coeff, pow;
   do
	{
        //Get the polynomial term data
        printf("\nEnter Coeff:");
        scanf("%d", &coeff);
        printf("\nEnter Pow:");
        scanf("%d", &pow);
        head = insert_sorted(head,coeff,pow);
        printf("\nDo you want to add more terms to the polynomial list[Y/N]: ");
        scanf("%c",&choice);
		scanf("%c", &choice);
    }while(choice=='Y'||choice=='y');
    
  return head;  
}


// Function to add two polynomials 

struct polynode * add_polynomial(struct polynode* poly1, struct polynode* poly2) 
{
    struct polynode *result= NULL;
    //Loop while both of the linked lists have value
    while(poly1!=NULL && poly2!=NULL)
	{
        if (poly1->pow > poly2->pow) 
		{
            result = insert_sorted(result,poly1->coeff,poly1->pow);
            poly1= poly1->next;
        }
        else 
		  if (poly1->pow < poly2->pow) 
		   {
            result = insert_sorted(result,poly2->coeff,poly2->pow);
            poly2 = poly2->next;
           }
        else 
		  {
            result = insert_sorted(result,poly1->coeff+poly2->coeff,poly1->pow);
            poly1= poly1->next;
            poly2 = poly2->next;
          }
 
      }
    //Loops while either of the polynomial has some term left to process
    while(poly1!=NULL)
     {
        result = insert_sorted(result,poly1->coeff,poly1->pow);
        poly1= poly1->next;
     }
    while(poly2!=NULL)
     {
         result = insert_sorted(result,poly2->coeff,poly2->pow);
         poly2 = poly2->next;
     }
   printf("\nAddition Complete");
   
return result;   
} // End of add_polynomial()

// Function to display polynomial 
void display_list(struct polynode *head)
{
    printf("head->");
    while(head!= NULL)
     {
       printf("%d^%d ->", head->coeff,head->pow);
       head =   head->next;
     }
    printf("NULL");
}

// Function to display menu choices
int instruction()
{
   int choice;
   
   printf("\n\nMain Menu");
   printf("\n1. Create polynomial_1:");
   printf("\n2. Create polynomial_2:");
   printf("\n3. Add the polynomial_1 and polynomial_2");
   printf("\n4. Display Polynomial_1");
   printf("\n5. Display Plolynomial_2");
   printf("\n6. Display Resultant Polynomial");
   printf("\n7. Quit from Menu");
   printf("\n Enter your choice[1-7]:");
   scanf("%d", &choice);
   return choice;
}

void main()
{
  struct polynode *head1=NULL,*head2=NULL,*head3=NULL;
  int choice,coeff,pow;
  while(1)
   {
     choice = instruction();
     switch(choice)
     {
       case 1: printf("\n Enter Polynomial equation_1:\n");
	           head1 = create_polynomial(head1);
               break;
       case 2: printf("\n Enter Polynomial equation_2:\n");
	           head2 = create_polynomial(head2);
               break;
       case 3: head3 = add_polynomial(head1,head2);
               break;

       case 4: printf("\nPolynomial_1:");
               display_list(head1);
               break; 
       case 5: printf("\nPolynomial_2:");
               display_list(head2);
               break; 
       case 6: printf("\nResultant Polynomial:");
               display_list(head3);
               break; 
       case 7: printf("\n exit from the program menu...");
               exit(0);
       default: printf("\n Enter correct menu choice[1-7]:");
     } // End of switch
     
   }// End of while
   
}  // End of function main()     
