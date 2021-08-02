/**
Lab Evaluation-2 [Thursday July 22, 2021 Afternoon Batch P2]

Q1.  An App play store is a collection of various purpose mobile Apps. Play store provides a search engine for the mobile users to search an App and can download the App of their choice using a software module which have the following menu options: Every App has the following properties: App_name (Single word), Type of App (such as Game, Financial, medical, social etc.), memory required for installation of an App.

MAIN MENU
       1. Add a Record of new App in the play store.
       2. Search an App on the basis of App_name.
       3. Display Details of that App if found in step 2.
       4. Delete an App from play store on the basis of App_name.
       5. Display list of all Apps available in play store with their type and memory requirements. 
       6. Quit.

Write C code to implement the functionality of above menu options. 

The time complexity of the functions in step-1 to step-5 should be O(1) where N is the number of Apps available in Play store. (Assumption is no two Apps have the same name)

Solution By Mukesh K Jadon
***/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct mobileapp
{
       char name[20];
       char type[20];
       int size;  // memory required to store App in KiloByte
};

struct mobilehashtable
{
  int key;
  struct mobileapp mobapp;
};
struct mobileapp get_app_details()
{
      struct mobileapp mobapp;
      printf("\n Enter Name of App:");
      scanf("%s", mobapp.name);
      printf("\n Enter Type of App:");
      scanf("%s", mobapp.type);
      printf("\n Enter memory required for App in Kilobyte:");
      scanf("%d", &mobapp.size);
      
	  return mobapp;
}

int hash_code(char name[])
{
    int code=0;
    int i=0;
    while(name[i]!= '\0')
    {
        code = code+ name[i]*(i+1);
        i++;
    }
    code = code % MAX_SIZE;
    
	//printf("\n HashCode= %ld", code);
    
	return code;
}
void display_App(struct mobileapp mobapp)
{
     
     printf("\n%s\t%s\t%d KB", mobapp.name, mobapp.type,mobapp.size);
}

void display_list(struct mobilehashtable ht[])
{
     int i;
     printf("\nName\t\tType\t\tSize");
     for(i=0;i<MAX_SIZE;i++)
        if(ht[i].key != -9999)
           display_App(ht[i].mobapp);   
}
int instruction()
{
   int choice;
   
   printf("\nMain Menu");
   printf("\n1. Add a new App in the Play Store");
   printf("\n2. Search an App on the basis of App name");
   printf("\n3. Delete an App on the basis of App name");
   printf("\n4. Display All App Details");
   printf("\n5. Quit from Menu");
   printf("\n Enter your choice[1-5]:");
   scanf("%d", &choice);
   return choice;
}
void initialize_hashtable(struct mobilehashtable ht[])
{
	int i;
	for (i=0;i<MAX_SIZE;i++)
	   ht[i].key= -9999;
	
}
void main()
{
  struct mobileapp mobapp;
  struct mobilehashtable hashtable[MAX_SIZE];
  int choice;
  char name[20];
  int index;
  initialize_hashtable(hashtable);
  while(1)
   {
     choice = instruction();
     switch(choice)
     {
       case 1: mobapp = get_app_details();
               index = hash_code(mobapp.name);
               if(hashtable[index].key!= -9999)
                 printf("\n This App already exist in the App Store...");
               else
                { hashtable[index].key = index;
                  hashtable[index].mobapp = mobapp;
                }
                break;
       case 2: printf("\n Enter the name of the App:");
               scanf("%s",name);
               index = hash_code(name);
               if(hashtable[index].key==index)
                {
                	 printf("\nName\t\tType\t\tSize");
					 display_App(hashtable[index].mobapp);
			    }
               else
                 printf("App is not available in Play Store...");
               break;
       case 3: printf("\n Enter the name of the App to delete:");
               scanf("%s",name);
               index = hash_code(name);
               if(hashtable[index].key==index)
                {
                  printf("\nName\t\tType\t\tSize");
				  display_App(hashtable[index].mobapp);
                  hashtable[index].key = -9999;
                }  
               else
                 printf("App is not available in Play Store...");
               break;
        case 4: display_list(hashtable);
                break; 
       case 5:  printf("\nSaving all databases and shutdown...");
                exit(0);
       default: printf("\n Enter correct menu choice[1-5]:");
     } 
   } // End of while()
} // End of Main()      
