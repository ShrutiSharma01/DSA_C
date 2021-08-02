/********************************************
 
** Assignment Lab Evaluation_1 for section-P1

Q1. Write C code to implement stack data structure (for integers) using linked list.
The program should be menu driven with the following options:

1. To push an element in the stack.
2. To pop an element from the stack and also display the largest element in the stack at
that point in time of pop operation.
3. To display the top element of the stack and also display the largest element in the stack
at that point in time.
4. To display the count of elements in the stack after each push and pop operation.
5. To quit from the program.

Please note: time and memory complexity will be considered for better marks in evaluation.

**********************************************

** Solution by Author: Mukesh K Jadon
*/ 
#include <stdio.h>
#include <stdlib.h>
struct stack
{
  int *arr; //4
  int size; // No of elements in the stack at a point of time
  int maxsize; // maximum limit of stack
  int sp; // top element index 
  int *largest;  //largest element in the stack at sp index
};

// To create and initialize the stack 
void initialize_stack(struct stack *s,int n)
{
    s->arr= (int*)malloc(sizeof(int)*n);
    s->largest= (int*)malloc(sizeof(int)*n);
	s->sp=-1;
    s->maxsize=n;
    s->size=0;
}
void push(struct stack *s, int n)
{
   if(s->sp<s->maxsize-1)
     {  
        
        if(s->sp==-1)
         {
		   printf("%d", s->sp+1);
		   s->largest[s->sp+1] = n;
	     }
		   
        else
         {
		  if(s->largest[s->sp]<n)
                 s->largest[s->sp+1] = n;
          else
               s->largest[s->sp+1] = s->largest[s->sp];
         }
        s->sp++;
        s->arr[s->sp] = n;
        s->size++;
         
     }
   else
     {
       printf("\n Stack Overflow....");
       exit(0);
     }
}

int pop(struct stack *s)
{
   int val;
   if(s->sp<0)
    {
       printf("\n Stack Underflow....");
       exit(0);
     }
    else
     { 
       val = s->arr[s->sp];
       //large = s->largest[s->sp];
       printf("\nLargest in stack is:%d",s->largest[s->sp]);
       s->sp--;
       s->size--;
     }
 return val;
    
}

// Returns the top element of the stack without delete

int top(struct stack *s)
{
   int val;
   if(s->sp<0)
    {
       printf("\n Stack Underflow....");
       exit(0);
     }
    else
     { 
       val = s->arr[s->sp];
       printf("\nLargest in stack is:%d",s->largest[s->sp]);
      }
 return val;
    
}

// Return the number of elements in the stack  

int stacksize(struct stack s)
{
	return s.size;
}

void display_stack(struct stack s)
{
	int i,j;
	i= s.sp;
	//j= s.sp;
	for(j=0;j<=i;j++)
	  printf("%4d",s.arr[j]);
	printf("\n");
	for(j=0;j<=i;j++)
	  printf("%4d",s.largest[j]);
}
// To take the user's choice 

int instruction()
{
	int choice;
	printf("\n\nStack operation Menu");
	printf("\n1. Push in stack");
	printf("\n2. Pop from stack");
	printf("\n3. Top Element in stack");
	printf("\n4. Current size of the stack");
	printf("\n5. Display all in stack");
	printf("\n6. Quit from Program");
	printf("\n Enter your choice[1-6]:");
	scanf("%d",&choice);
	return choice;
}

void main()
{
   struct stack st; // st is a varianble of type stack.
   int val,n;
   int choice;
   printf("\n Enter the maximum size of the stack:");
   scanf("%d", &n); 
   initialize_stack(&st,n);
   while(1)
   {
   	 choice = instruction();
   	 switch(choice)
   	 {
   	 	case 1: printf("\nEnter the element to push:");
   	 	        scanf("%d",&val);
   	 	        push(&st,val);
   	 	        n = stacksize(st);
				printf("\n No of  elements in the stack after push: %d",n);
   	 	        break;
   	 	case 2: val = pop(&st);
			    printf("\nPopped value is: %d",val);
				n = stacksize(st);
				printf("\n No of  elements in the stack after pop: %d",n);
				break;
		case 3: val = top(&st);
			    printf("\nValue at top of the stack is: %d",val);
				break;
		case 4: n = stacksize(st);
				printf("\n No of  elements in the stack: %d",n);
				break;
		case 5: display_stack(st);
				break;
		case 6: printf("\n EXit from the program...");
		        exit(0);
		default: printf("\n Invalid choice try again[1-5]:");
		      
		} // End of switch
		
   }  //End of while  
   
} // End of main()

   
    


   
