//Binary Search Tree
#include <stdio.h>
#include <stdlib.h>

struct bstnode {
    int data;                //4 bytes
    struct bstnode *left;  //4 bytes
    struct bstnode *right; //4 bytes
};

//Searching in BST - WC Time Complexity is O(n) - in case of Skewed tree
struct bstnode *search_node(struct bstnode *root, int term) {
    if(root == NULL || root->data == term)
        return root;

    if(term < root->data)
        return search_node(root->left, term);
    else
        return search_node(root->right, term);
}

//Creating new node
struct bstnode* create_node(int value) {
    struct bstnode *temp;

    temp = (struct bstnode*)malloc(sizeof(struct bstnode));   // 12 bytes block will be allocated

    temp->data = value;
    temp->left = NULL;
    temp->right= NULL;
    return temp;
}

//Inserting new node iterative approach
// struct bstnode* insert_node(struct bstnode *root, int value) {
//     struct bstnode *newnode, *p, *q;

//     newnode =  create_node(value);
//     if(root == NULL)
//         root = newnode;
//     else { 
//         p = q = root;
//         while(p != NULL) {
//             q = p;
//             if(p->data < value)
//                 p = p->right;
//             else
//                 p = p->left;
//         }
//         if(q->data > value)
//             q->left = newnode;
//         else
//             q->right = newnode;
//     }
//     return root;
// }

// Inserting new node - recursive approach
struct bstnode* insert_node(struct bstnode *root, int value) {
    struct bstnode *newnode = create_node(value);

    if(root == NULL){
        root = newnode;
        return root;
    }
    
    else { 
        if(value < root->data)
            root->left = insert_node(root->left, value);
        else 
            root->right = insert_node(root->right, value);
    }
    return root;
}

// inorder_successor(smallest value in right subtree) - iterative approach
// struct bstnode* inorder_successor(struct bstnode *root) {
//     struct bstnode *cur = NULL;

//     if(root == NULL)
//         return NULL;

//     if(root->right != NULL) {
//         cur = root->right;
//         while(cur->left != NULL) {
//             cur = cur->left;
//         }
//     }
//     return cur;
// }

// inorder_predecessor(largest value in left subtree) - recursive approach
struct bstnode* inorder_predecessor(struct bstnode *root) {
    if (root == NULL || root->right == NULL)
        return root;
    else
        return inorder_predecessor(root->left);
}

//Deletion in BST - Avg TC = O(logn), WC TC = O(n) [Skewed tree]
struct bstnode* delete_node(struct bstnode *root, int value) {
    if(root == NULL)
        printf("Element not found");

    // for checking if value to be deleted in present on left or right
    else if(value < root->data)
        root->left = delete_node(root->left, value);

    else if(value > root->data)
        root->right = delete_node(root->right, value);

    else if(root->left && root->right){
        struct bstnode *temp = inorder_predecessor(root->left);
        root->data = temp->data;
        root->left = delete_node(root->left, temp->data);
    }

    else{
        if(root->left == NULL && root->right == NULL)   // Case 1
            root = NULL;
        
        else if(root->left != NULL)   // Case 2
            root = root->left;
        
        else 
            root = root->right;    // Case 2
    }
    return root;
}

// inorder traversal of bst to print bst
void inorder_bst(struct bstnode *root) {
    if(root != NULL) {
        inorder_bst(root->left);
        printf("%d ", root->data); 
        inorder_bst(root->right);
    }
}

int instruction() {
    int choice;
    printf("\nMain Menu");
    printf("\n1. Inserting node in binary search tree");
    printf("\n2. Search in binary search tree");
    printf("\n3. Deleting node in binary search tree");
    printf("\n4. Display binary search tree (Inorder)");
    printf("\n5. Quit from Menu");
    printf("\nEnter your choice[1-5]:");
    scanf("%d", &choice);
    return choice;
}

void main() {
    struct bstnode *root = NULL;  // otherwise it will be dangling pointer
    struct bstnode *temp;
    int key;
    int choice;
    while (1){
        choice = instruction();
        switch (choice) {
            case 1:
                printf("\nEnter positive integer:");
                scanf("%d", &key);
                if(key < 0)     // can enter only positive values as key
                    break;
                root = insert_node(root, key);
                break;
            case 2:
                fflush(stdin);
                printf("\nEnter the key to search:");
                scanf("%d", &key);
                if(key < 0)
                    break;
                temp = search_node(root, key);
                if(temp == NULL)
                    printf("\nKey does not exist");
                else
                    printf("\nKey exist");
                break;
            case 3:
                fflush(stdin);
                printf("\nEnter the key to delete:");
                scanf("%d", &key);
                root = delete_node(root, key);
                break;
            case 4:
                inorder_bst(root);
                break;
            case 5:
                printf("\nExit from the program menu...Ta Ta...Fir milenge...");
                exit(0);
            default:
                printf("\nEnter correct menu choice[1-6]:");
        }
    }

    // while(1) {
    //     printf("Enter positive integer:");
    //     scanf("%d", &key);
    //     if(key < 0)     // can enter only positive values as key
    //         break;
    //     else {
    //         if(root == NULL)
    //             root = create_bstnode(key);
    //         else
    //             insert_binarytree(root, key);
    //     }
    // }

    // inorder_binarytree(root);

    // while(1) {
    //     printf("\n enter the key to search:");
    //     scanf("%d", &key);
    //     if(key < 0)
    //         break;
    //     temp = search(root,key);
    //     if(temp == NULL)
    //         printf("\n Key does not exist");
    //     else
    //         printf("\n Key exist");
    // }
}






