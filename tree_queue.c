#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct treenode {
    int val;
    struct treenode* left;
    struct treenode* right;
    struct treenode* next;
}treenode;

typedef struct queue{
    struct treenode *front;
    struct treenode *rear;
}queue;

void initialize(struct queue *q){
    q->front = NULL;
    q->rear = NULL;
}

struct treenode* createnode(int val){
    struct treenode *temp;
    temp = (struct treenode *)malloc(sizeof(struct treenode));
    temp->val = val;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

struct treenode* create_binarytree() {
    struct treenode* p;
    int val;
    printf("Enter val(-1 for terminate): ");
    scanf("%d", &val);
    if(val == -1)
        return NULL;
    p = (struct treenode *) malloc(sizeof(struct treenode));
    p->val = val;
    printf("Enter left child of %d:\n", val);
    p->left = create_binarytree();
    printf("Enter right child of %d:\n", val);
    p->right = create_binarytree();
    return p;
}

bool check_skewed_tree(struct treenode* root){
    if (root == NULL || (root->left == NULL && root->right == NULL))     // check if node is NULL or is a leaf node
        return true;

    if (root->left && root->right)     // check if node has two children if yes, return false
        return false;

    if (root->left)
        return check_skewed_tree(root->left);

    return check_skewed_tree(root->right);
}

bool check_sum(struct treenode* root) {
    int left_data = 0, right_data = 0;   // If left child or right child is not present then 0 is used as data of that child
    if(root == NULL || (root->left == NULL && root->right == NULL))
        return true;

    if(root->left != NULL)
        left_data = root->left->val;

    if(root->right != NULL)
        right_data = root->right->val;

    if((root->val == left_data + right_data) && check_sum(root->left) && check_sum(root->right))
        return true;
    return false;
}

bool check_full_binarytree(struct treenode* root){
    if (root == NULL)     //empty tree
        return true;

    if (root->left == NULL && root->right == NULL)     //leaf node
        return true;

    if ((root->left) && (root->right))    // If both left and right are not NULL, and left & right subtrees are full
        return (check_full_binarytree(root->left) && check_full_binarytree(root->right));

    return false;       //return this if none of the above conditions work
}

void enqueue(treenode* root,queue *q){
    if(q->front==NULL){
        q->front=q->rear=root;
    }
    else{
        q->rear->next=root;
        q->rear=root;
    }
}

void dequeue(queue *q){
    if(q->front==q->rear){
        q->front=q->rear=NULL;
    }
    else{
        q->front=q->front->next;
    }
}

void levelorder_traversal(struct treenode* root, struct queue* q) {
    if(root == NULL)
        return;
    enqueue(root, q);
    while(((q->front) != NULL) && ((q->rear) != NULL)){
        struct treenode* current = q->front;
        printf("%d ", current->val);
        if(current->left != NULL)
            enqueue(current->left, q);
        if(current->right != NULL)
            enqueue(current->right, q);
        dequeue(q);
    }
    return;
}

int instruction() {
    int choice;
    printf("\nMain Menu");
    printf("\n1. Create Binary tree");
    printf("\n2. Check the biary tree is skewed or not:");
    printf("\n3. Check the sum of parent node is equal to its chiled or not:");
    printf("\n4. Check the binarytree is full binary tree or not");
    printf("\n5. Level order traversal");
    printf("\n6. Exit from the program");
    printf("\n Enter your choice[1-6]:");
    scanf("%d", &choice);
    return choice;
}

int main() {
    struct treenode *root = NULL;    //to avoid dangling pointer
    struct queue q;
    initialize(&q);
    int choice;
    int flag;
    while(1) {
        choice = instruction();
        switch(choice) {
            case 1:
                root = create_binarytree();
                break;

            case 2:
                flag = check_skewed_tree(root);
                if(flag)
                    printf("\n The given Binary tree is skewed.");
                else
                    printf("\n The given Binary tree is not skewed.");
                break;

            case 3:
                flag = check_sum(root);
                if(flag)
                    printf("\n The given Binary tree satisfy the property of sum.");
                else
                    printf("\n The given Binary tree does not satisfy the property of sum.");
                break;

            case 4:
                flag = check_full_binarytree(root);
                if(flag)
                    printf("\n The given Binary tree is a full binary tree.");
                else
                    printf("\n The given Binary tree is not a full binary tree.");
                break;

            case 5:
                levelorder_traversal(root, &q);
                break;

            case 6:
                printf("\n Exiting from program....");
                exit(0);

            default:
                printf("\nInvalid Choice try again[1-6]:");
        }
    }
}
