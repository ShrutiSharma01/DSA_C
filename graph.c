//Ayush Dhoot
//20UCS045
//DSA Lab Endterm 31-07-2021

#include<stdio.h>
#include<stdlib.h>

int instructions(){                 //MENU FUNCTION
    int x;
    printf("Enter choice:\n");
    printf("1. Create graph\n");
    printf("2. Display Graph\n");
    printf("3. Find degree of vertex\n");
    printf("4. Find Cycles\n");
    printf("5. Exit\n");
    scanf("%d",&x);
    return x;
}

typedef struct node {                   //STRUCTURE FOR LINK LIST
    int vertex;
    struct node *next;
}node;

int find_degree(node *Adj[],int n,int nodes){           //FUNCTION TO FIND DEGREE OF NODE
    int cnt=0;
    int degree[nodes+1];
    for(int i=1;i<=nodes;i++){
        degree[i]=0;
    }
    for(int i=1;i<=nodes;i++){
        cnt=0;
        node *temp=Adj[i];
        while(temp!=NULL){
            cnt++;
            degree[temp->vertex]++;
            temp=temp->next;
        }
        degree[i]+=cnt;
    }
    return degree[n];
}

void display_graph (node *Adj[], int nodes) {          //FUNCTION TO DISPLAY THE GRAPH
    node *ptr;
    int i;
    for(i = 1; i <= nodes; i++) {
        ptr = Adj[i];
        printf("The neighbours of node %d are: ",i);
        while(ptr != NULL) {
            printf("%d-->", ptr->vertex);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

void create_graph(node *Adj[], int nodes) {            //FUCNTION TO CREATE THE GRAPH
    node *new_node, *tail;
    int i, j, n, val;
    for(i = 1; i <= nodes; i++){
        tail = NULL;
        printf("Enter the number of edges out of vertex %d: ", i);
        scanf("%d", &n);
        for(j = 0; j < n; j++) {
            printf("Enter the edge %d of vertex %d: ", j+1, i);
            scanf("%d", &val);
            new_node = (node *) malloc(sizeof(node));
            new_node->vertex = val;
            new_node->next = NULL;
            if (Adj[i] == NULL)
                Adj[i] = new_node;
            else
                tail->next = new_node;
            tail = new_node;
        }
        printf("\n");
    }
}


int iscyclic(int vertex, node * Adj[], int is_visited[], int dfs_visited[] ){
    is_visited[vertex] = 1;                    //FUCNTION TO CHECK FOR CYCLES
    dfs_visited[vertex] = 1;
    node * curr_node = Adj[vertex];
    while(curr_node != NULL ){
        int x;
        x = curr_node->vertex;
        if( !is_visited[x] ){
            if( iscyclic(x, Adj, is_visited, dfs_visited) ) return 1;
        }
        else if( dfs_visited[x] ) return 1;
        curr_node = curr_node->next;
    }
    dfs_visited[vertex] = 0;
    return 0;
}

void find_cycles(node * Adj[],int nodes){
    int is_visited[nodes + 1], dfs_visited[nodes + 1];          //FUCNTION TO FIND CYCLES
    for(int i=1;i<=nodes;i++){
        is_visited[i]=0;
        dfs_visited[i]=0;
    }
    is_visited[0] = dfs_visited[0] = 1;
    for(int i = 1; i<=nodes; i++){
        if( !is_visited[i] ){
            if(iscyclic(i, Adj, is_visited, dfs_visited)){
                printf("\nThis Graph is Cyclic for: ");
                for(int j = 1; j<=nodes; j++){
                    if(dfs_visited[j] == 1 ) printf("%d ", j);
                }
                printf("\n");
                return;
            }
        }
    }
    printf("No cycles!\n");
}


int main(){                 //MAIN FUNCTION
    int nodes,vertex;
    node *Adj[100];
    while(1){
        int ch=instructions();
        switch (ch){
        case 1:
            printf("\nEnter number of vertices:");
            scanf("%d",&nodes);
            printf("\n");
            for(int i=1;i<=nodes;i++){
                Adj[i]=NULL;
            }
            create_graph(Adj,nodes);
            break;
        case 2:
            display_graph(Adj,nodes);
            break;
        case 3:
            printf("Enter vertex for degree:");
            scanf("%d",&vertex);
            printf("Degree of vertex %d is: %d\n",vertex, find_degree(Adj,vertex,nodes));
            break;
        case 4:
            find_cycles(Adj,nodes);
            break;
        case 5:
            printf("Exiting!");
            exit(0);
        default:
            printf("Invalid choice!");
            break;
        }
    }
}

//gcc 20ucs045.c -o 20ucs045
//./20ucs045
