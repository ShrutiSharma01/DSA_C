//Name: Shruti Sharma
//Roll Number: 20UCS189
//Section: A2
//Lab Section: Q2 
//Date: June 26, 2021
//Time: 6:15PM (4PM - 6:30PM slot)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Structure of Binary Tree
typedef struct treenode{
    char val;
    struct treenode *left;
    struct treenode *right;
}treenode;

//Stack to store nodes
typedef struct nodeStack{
    treenode *nodesarr[200];
    int top;
}nodeStack;

//Stack to store character 
typedef struct charStack{
    char temp[200];
    int top;
}charStack;

//Function to create New Node
treenode *createNode(char c){
    treenode *temp = (treenode *)malloc(sizeof(treenode));
    temp->val = c;
    temp->right = temp->left = NULL;
    return temp;
}

//Function to push nodes in nodeStack
void pushNode(nodeStack *nst, treenode *t){
    (*nst).top++;
    (*nst).nodesarr[(*nst).top] = t;
}

//Function to push character in charStack
void pushChar(charStack *cst, char c){
    (*cst).top++;
    (*cst).temp[(*cst).top] = c;
}

//Function to create binary tree of given Infix Expression
treenode *createTree(char *s, nodeStack *nst, charStack *cst){
    treenode *a, *t1, *t2;
    // Prioritising the operators
    int priority[123] = {0};
    priority['+'] = priority['-'] = 1, priority['/'] = priority['*'] = 2, priority['^'] = 3, priority[')'] = 0;
    for (int i = 0; i < s[i] != '\0'; i++){
        if (s[i] == '(')
            pushChar(cst, s[i]);
        else if (isalpha(s[i])){
            a = createNode(s[i]);
            pushNode(nst, a);
        }
        else if (priority[s[i]] > 0){
            while (cst->top != -1 && cst->temp[cst->top] != '(' && ((s[i] != '^' && priority[cst->temp[cst->top]] >= priority[s[i]]) || (s[i] == '^' && priority[cst->temp[cst->top]] > priority[s[i]]))){
                a = createNode(cst->temp[cst->top]);
                cst->top--;
                t1 = nst->nodesarr[nst->top];
                nst->top--;
                t2 = nst->nodesarr[nst->top];
                nst->top--;
                a->left = t2;
                a->right = t1;
                pushNode(nst, a);
            }
            // Push s[i] to char stack
            pushChar(cst, s[i]);
        }
        else if (s[i] == ')'){
            while (cst->top != -1 && cst->temp[cst->top] != '('){
                a = createNode(cst->temp[cst->top]);
                cst->top--;
                t1 = nst->nodesarr[nst->top];
                nst->top--;
                t2 = nst->nodesarr[nst->top];
                nst->top--;
                a->left = t2;
                a->right = t1;
                pushNode(nst, a);
            }
            cst->top--;
        }
    }
    a = nst->nodesarr[nst->top];
    return a;
}

//Function to check validity of given Infix Expression
int valid(char input[200]){
    int count = 0;
    int brac = 0;
    for (int i = 0; input[i] != '\0'; i++){
        if (input[i] == '(')
            brac++;
        else if (input[i] == ')'){
            brac--;
            if (brac < 0)
                return 0;
        }
        else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')){
            if (count ==0)
                count = 1;
            else
                return 0;
        }
        else{
            if (count == 1)
                count = 0;
            else
                return 0;
        }
    }
    if (brac == 0 && count == 1)
        return 1;
    else
        return 0;
}

//Function to convert infix to postfix using trees
void postOrder(treenode *root){
    if (root){
        postOrder(root->left);
        postOrder(root->right);
        printf("%c ", root->val);
    }
}

int main(){
    printf("Enter expression: ");
    char temp[200];
    scanf("%s", temp);
    strcat(temp, ")");
    char exp[200] = {"("};
    strcat(exp, temp);
    if (valid(exp)){
        treenode *root = NULL;
        charStack cst;
        cst.top = -1;
        nodeStack nst;
        nst.top = -1;
        root = createTree(exp, &nst, &cst);
        postOrder(root);
    }
    else
        printf("Invalid Expression");
}

//gcc new.c -o new
//./new