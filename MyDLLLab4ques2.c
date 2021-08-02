#include<stdio.h>
#include<process.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct node{      //node of a doubly linked list contains 3 elements
    int data;
    struct node *next;
    struct node *prev;
}Node;

int instructions(){
    printf("1. Create list\n"
           "2. Display list\n"
           "3. Add at the beginning\n"
           "4. Add at the end\n"
           "5. Add after\n"
           "6. Add before\n"
           "7. Delete\n"
           "8. Reverse\n"
           "9. Reverse Print\n"
           "10. Quit\n");
    int option;
    scanf("%d", &option);
    return option;
}

Node* createList(Node* head, char c){
    if(c == 'y' || c == 'Y'){
        head = NULL;
        printf("New List is created!\n");
    }
    else{
        printf("Opertaion is cancelled!\n");
    }
    return head;
}

void display(Node* head){    //printing node in forward direction
    if(head == NULL){
        printf("List is empty!\n");
        return;
    }
    while(head != NULL){
        printf("%d ", head -> data);
        head = head -> next;
    }
    printf ("\nThis is the doubly linked linked in the forward direction.\n");
    return;
}

Node* GetNewNode(int num){     //creating a node
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> data = num;
    newNode -> prev = NULL;
    newNode -> next = NULL;
    return newNode;
}

Node* addBegin(Node* head){
    int num;
    printf("Enter value to be inserted at the beginning: ");
    scanf("%d", &num);
    Node* newNode = GetNewNode(num);
    if (head == NULL){
        head = newNode;
        printf("The list was empty but now a new value is added to the list.\n");
        return head;
    }
    head -> prev = newNode;
    newNode -> next = head;
    head = newNode;
    printf("A new value is added to the list at the beginning.\n");
    return head;
}

Node* addEnd(Node* head){
    int num;
    printf("Enter value to be inserted at the end: ");
    scanf("%d", &num);
	Node* temp = head;
	Node* newNode = GetNewNode(num);
	if(head == NULL) {
		head = newNode;
        printf("The list was empty but now a new value is added to the list.\n");
		return head;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp -> next = newNode;
	newNode -> prev = temp;
    printf("A new value is added to the list at the end.\n");
    return head;
}

Node* addAfter(Node* head){
    int num1, num;
    printf("Enter value after which a node has to be inserted: ");
    scanf("%d", &num1);
    printf("Enter value to be inserted after given node: ");
    scanf("%d", &num);
    if(head == NULL){
        printf("The list is empty!\n");
        return head;
    }
    Node* ptr = head;
    Node* temp = GetNewNode(num);
    while ((ptr != NULL) && (ptr -> data != num1)) ptr = ptr -> next;
    if(ptr == NULL){
        printf("The entered value after which a node has to be inserted does not exist.\n");
        return head;
    }
    else if(ptr -> next == NULL){
        temp -> prev = ptr;
        ptr -> next = temp;
        printf("A new value is added to the list after the given value.\n");
        return head;
    }
    temp -> next = ptr -> next;
    temp -> prev = ptr;
    ptr -> next -> prev = temp;
    ptr -> next = temp;
    printf("A new value is added to the list after the given value.\n");
    return head;
}

Node* addBefore(Node* head){
    int num1, num;
    printf("Enter value before which a node has to be inserted: ");
    scanf("%d", &num1);
    printf("Enter value to be inserted before given node: ");
    scanf("%d", &num);
    if(head == NULL){
        printf("The list is empty!\n");
        return head;
    }
    Node* ptr = head;
    Node* temp = GetNewNode(num);
    while ((ptr != NULL) && (ptr -> data != num1)) ptr = ptr -> next;
    if(ptr == NULL){
        printf("The entered value before which a node has to be inserted does not exist.\n");
        return head;
    }
    else if(ptr -> prev == NULL){
        temp -> next = ptr;
        ptr -> prev = temp;
        head = temp;
        printf("A new value is added to the list before the given value.\n");
        return head;
    }
    Node* ptr_prev = ptr -> prev;
    temp -> next = ptr;
    temp -> prev = ptr_prev;
    ptr_prev -> next = temp;
    ptr -> prev = temp;
    printf("A new value is added to the list before the given value.\n");
    return head;
}

Node* deleteNode(Node* head){
    int num;
    printf("Enter value for which the node has to deleted: ");
    scanf("%d", &num);
    if(head == NULL){
        printf("The list is empty!\n");
        return head;
    }
    Node* ptr = head;
    while ((ptr != NULL) && (ptr -> data != num)) ptr = ptr -> next;
    if(ptr == NULL){    //value not found
        printf("The entered value which has to be deleted does not exist.\n");
        return head;
    }
    else if((ptr == head) && (ptr -> next == NULL)){   //deleting head node when only 1 node present
        free(ptr);
        head = NULL;
        printf("The value was present at head node (only one node was present in the list) and that node is deleted successfully.\n");
        return head;
    }
    else if(ptr == head){   //deleting head node when there are multiple nodes present
        head = head -> next;
        head -> prev = NULL;
        free(ptr);
        printf("The value was present at head node (with multiple nodes present) and that node is deleted successfully.\n");
        return head;
    }
    else if(ptr -> next == NULL){   //deleting last node
        ptr -> prev -> next = NULL;
        free(ptr);
        printf("The value was present at last node and that node is deleted successfully.\n");
        return head;
    }
    else{   //node to be deleted in present between 2 nodes
        Node* ptr_prev = ptr -> prev;
        Node* ptr_next = ptr -> next;
        ptr_prev -> next = ptr_next;
        ptr_next -> prev = ptr_prev;
        free(ptr);
        printf("The node containing the given value (present between two nodes) is deleted successfully.\n");
        return head;
    }
}

Node* reverse(Node* head){
    Node *temp = NULL;
    Node *current = head;
    if(current == NULL){
        printf("The list is empty.\n");
        return head;
    }
    while(current != NULL){
        temp = current -> prev;
        current -> prev = current -> next;
        current -> next = temp;
        current = current -> prev;
    }
    if(temp != NULL ) head = temp -> prev;
    printf("The doubly linked list is successfully reversed.\n");
    return head;
}

void reverseDisplay(Node* head){
    if(head == NULL){
        printf("List is empty!\n");
        return;
    }
    while(head -> next != NULL) head = head -> next;   //going to the last node
    while(head != NULL){   //traverse backward using prev pointer
        printf("%d ", head -> data);
        head = head -> prev;
    }
    printf ("\nThis is the doubly linked linked in the reverse direction.\n");
    return;
}

int main(){
    Node *head = NULL;  //empty list
    char c;
    int option, num, num1;
    while(1){
        option = instructions();
        switch(option){
            case 1:
                printf("Selecting this option will create an entirely new list. Do you wish to continue? (y/n)");
                fflush(stdin);
                scanf("%c", &c);
                head = createList(head, c);
                getch();
                break;
            case 2:
                display(head);
                getch();
                break;
            case 3:
                head = addBegin(head);
                getch();
                break;
            case 4:
                head = addEnd(head);
                getch();
                break;
            case 5:
                head = addAfter(head);
                getch();
                break;
            case 6:
                head = addBefore(head);
                getch();
                break;
            case 7:
                head = deleteNode(head);
                getch();
                break;
            case 8:
                head = reverse(head);
                getch();
                break;
            case 9:
                reverseDisplay(head);
                getch();
                break;
            case 10:
                printf("BBye! Have a nice day!");
                return 0;
            default:
                printf("Invalid Choice!\n");
                getch();
                break;
        }
    }
    return 0;
}
