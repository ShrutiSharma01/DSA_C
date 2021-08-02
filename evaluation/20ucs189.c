/* Name - Shruti Sharma
Section - Q2
Roll Number - 20UCS189
Time - 2-4 pm */

#include <stdio.h>
#include <stdlib.h>

struct node {
    int vertex;
    struct node *next;
};

// created graph using adjacency list
void createGraph(struct node *Adj[], int no_of_nodes) {
    struct node *new_node, *last;
    int n, val;
    
    for(int i = 1; i <= no_of_nodes; i++){
        last = NULL;
        printf("\n Enter the number of neighbours of %d: ", i);
        scanf("%d", &n);
        
        for(int j = 0; j < n; j++) {
            printf("\n Enter the neighbour %d of %d: ", j + 1, i);
            scanf("%d", &val);
            new_node = (struct node *) malloc(sizeof(struct node));
            new_node->vertex = val;
            new_node->next = NULL;
            
            if (Adj[i] == NULL){
                Adj[i] = new_node;
            }
            
            else{
                last->next = new_node;
            }
            last = new_node;
        }
    }
}

// function to display graph made using adjacency list
void displayGraph (struct node *Adj[], int no_of_nodes) {
    struct node *ptr;
    int i;
    
    for(i = 1; i <= no_of_nodes; i++) {
        ptr = Adj[i];
        printf("\n The adjacency list of node %d are:", i);
        
        while(ptr != NULL) {
            printf("\t%d->", ptr->vertex);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

// find degree of asked vertex
int find_degree(struct node *Adj[], int n, int nodes) {
    int cnt = 0;
    int degree[nodes + 1];
    
    for(int i = 1; i <= nodes; i++){
        degree[i] = 0;
    }
    
    for(int i = 1; i <= nodes; i++){
        cnt = 0;
        struct node *temp = Adj[i];
        
        while(temp != NULL){
            cnt++;
            degree[temp->vertex]++;
            temp = temp->next;
        }
        
        degree[i] += cnt;
    }
    return degree[n];
}

// check if reach to same node or not
int checkIfCyclic(int vertex, struct node * Adj[], int visited[], int dfsVisited[]) {
    visited[vertex] = 1;
    dfsVisited[vertex] = 1;
    struct node * current = Adj[vertex];
    
    while(current != NULL) {
        int x;
        x = current->vertex;
        
        if(!visited[x]) {
            if(checkIfCyclic(x, Adj, visited, dfsVisited)){
                return 1;
            } 
        }
        
        else if(dfsVisited[x]){
            return 1;
        } 
        current = current->next;
    }
    
    dfsVisited[vertex] = 0;
    return 0;
}

// function to find graph cyclic or not
void isItCyclic(struct node * Adj[],int nodes){
    int visited[nodes + 1], dfsVisited[nodes + 1];
    
    for(int i = 1; i <= nodes; i++){
        visited[i] = 0;
        dfsVisited[i] = 0;
    }
    
    visited[0] = dfsVisited[0] = 1;
    
    for(int i = 1; i <= nodes; i++){
        if(!visited[i]){
            if(checkIfCyclic(i,Adj, visited, dfsVisited)){
                printf("\nThis Graph is Cyclic for: ");
                for(int j = 1; j <= nodes; j++){
                    if(dfsVisited[j] == 1) printf("%d ", j);
                }
                return;
            }
        }
    }
    printf("\nThis Graph is not cyclic. ");
}

// Menu driven program
int get_choice() {
    int choice;
    
    printf("\nMENU");
    printf("\n1. Create Graph using Adjacency list:");
    printf("\n2. Display graph:");
    printf("\n3. Find Degree of Vertex");
    printf("\n4. Find Cycles");
    printf("\n5. Quit:");
    printf("\n\nEnter Your Choice[1-5]:");
    scanf("%d", &choice);
    
    return choice;
}

// Main function
int main() {
    struct node *Adj[100];
    int no_of_nodes;
    int choice,vertex;
    
    while(1) {
        choice = get_choice();
        switch(choice) {
            case 1:
                printf("\n Enter the number of nodes in G: ");
                scanf("%d", &no_of_nodes);
                for(int i = 1; i <= no_of_nodes; i++)
                Adj[i] = NULL;
                createGraph(Adj, no_of_nodes);
                break;
                
            case 2:
                printf("\n The graph is: ");
                displayGraph(Adj, no_of_nodes);
                break;
                
            case 3:
                printf("Enter vertex of which degree is to be found:");
                scanf("%d", &vertex);
                printf("Degree of vertex %d is %d", vertex, find_degree(Adj, vertex, no_of_nodes));
                break;
                
            case 4:
                isItCyclic(Adj, no_of_nodes);
                break;
                
            case 5:
                exit(0);
                
            default:
                break;
        }
    }
    return 0;
} // end of main

// gcc 20ucs189.c -o 20ucs189
// ./20ucs189
