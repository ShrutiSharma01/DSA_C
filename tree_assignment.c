#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int data;
    struct node*left;
    struct node*right;
}node;
node* create() {
    node *p;
    char c;
    printf("if you want to add node type 'y' otherwise 'n' \n ");
    scanf(" %c", &c);
    if (c == 'n')
        return NULL;
    p = (node *) malloc(sizeof(node));
    scanf(" %d", &p->data);
    p->left = create();
    p->right = create();
    return p;
}
int instructions() {
    int n;
    printf("1->pre order traversal\n 2->In order traversal\n 3->post order traversal\n");
    scanf("%d", &n);
    return n;
}
void pre_order(node*root) {
    if (root == NULL) {
        return;
    }
    printf("%c  ", root->data);
    pre_order(root->left);
    pre_order(root->right);
    return;
}
int isFull(node* root) {
    if (root == NULL) return 1;
    if (root->left == NULL && root->right == NULL)return 1;
    if ((root->left) && (root->right))return ((isFull(root->left) && isFull(root->right)));
    return 0;
}
int valCheck(node *root) {
    int ldat = 0, rdat = 0;
    if (root == NULL || (root->left == NULL && root->right == NULL))return 1;
    else {
        if (root->left != NULL) {
            ldat = root->left->data;
        }
        if (root->right != NULL) {
            rdat = root->right->data;
        }
        if (root->data == ldat + rdat && valCheck(root->left) && valCheck(root->right))return 1;
        else return 0;
    }
}
int isSkew(node *root){
    if(root==NULL||(root->left==NULL&&root->right==NULL))return 1;
    if(root->left&&root->right)return 0;
    if(root->left)return isSkew(root->left);
    return isSkew(root->right);
}

typedef struct queue{
    struct node *front;
    struct node *rear;
}queue;


int main() {
    node *root = NULL;
    queue *front=NULL,*rear=NULL;
    root=create();
    if(valCheck(root))printf("true");
    else printf("false");
}
