// AVL Tree
#include<stdio.h>
#include<stdlib.h>

struct avlnode {
	int data;
	int height;  
	struct avlnode *left;
    struct avlnode *right;
};
 
// iterative approach to find the height 
int height(struct avlnode *root) {
	int leftHeight, rightHeight;
	if(root == NULL)
		return 0;

	if(root->left == NULL)
		leftHeight = 1;
	else
		leftHeight = 1 + root->left->height;
		
	if(root->right == NULL)
		rightHeight = 1;
	else
		rightHeight = 1 + root->right->height;
	
	if(leftHeight > rightHeight)
		return leftHeight;
	else
	    return rightHeight;
}

// recursive way to find height
// int height(struct avlnode *n) {
// 	if(n == NULL) {      // height = 0 for empty node
// 		return 0;
// 	}
// 	return n->height;
// }

// iterative approach to find balance factor
int balance_factor(struct avlnode *root) {
	int leftHeight, rightHeight;
	if(root == NULL)
		return 0;
 
	if(root->left == NULL)
		leftHeight = 1;
	else
		leftHeight = 1 + root->left->height;
 
	if(root->right == NULL)
		rightHeight = 1;
	else
		rightHeight = 1 + root->right->height;
 
	return leftHeight - rightHeight;
}

// recursive way to find balance factor
// int balance_factor(struct avlnode *n) {
// 	if(n == NULL) {
// 		return 0;
// 	}
// 	return (height(n->left) - height(n->right));
// }

// Recursive searching in AVL - WC Time Complexity is O(logn)
struct avlnode *search_node(struct avlnode *root, int term) {
    if(root == NULL || root->data == term)
        return root;

    if(term < root->data)
        return search_node(root->left, term);
    else
        return search_node(root->right, term);
}   

// single right rotation
struct avlnode *singleRightRotation(struct avlnode *x) {
	struct avlnode *y = x->left;
	x->left = y->right;
	y->right = x;
	x->height = height(x);
	y->height = height(y);
	return y;    // as y becomes the root node now
}

// single left rotation
struct avlnode *singleLeftRotation(struct avlnode *x) {
	struct avlnode *y = x->right;
	x->right = y->left;
	y->left = x;
	x->height = height(x);
	y->height = height(y);
	return y;
}
 
// Single right rotation due to left-to-left case
struct avlnode * LL(struct avlnode *root) {
	root = singleRightRotation(root);
    return root;
}

// Double rotation due to left-to-right case 
struct avlnode * LR(struct avlnode *root) {
	root->left = singleLeftRotation(root->left);
	root = singleRightRotation(root);
	return root;
}

// Single rotation due to right-to-right case
struct avlnode * RR(struct avlnode *root) {
	root = singleLeftRotation(root);
	return root;
} 

// double rotation due to right-to-left case
struct avlnode * RL(struct avlnode *root) {
	root->right = singleRightRotation(root->right);
	root = singleLeftRotation(root);
	return root;
}
 
// Create new avlnode to insert in AVL Tree
struct avlnode *create_avlnode(int key) {
    struct avlnode *temp;
	temp=(struct avlnode*)malloc(sizeof(struct avlnode));
	temp->data  = key;
	temp->left = NULL;
	temp->right= NULL;
	temp->height = 1;
    return temp; 
}    

 // Insertion in an AVL Tree
struct avlnode * insert(struct avlnode *root, int x) {
	if(root == NULL) {
		root = create_avlnode(x);
	}
	else
		if(x < root->data){     // insert in left subtree
			root->left = insert(root->left,x);  //newnode will be inserted in left
			
			// possibility is that tree get heavier in left side
			if(balance_factor(root) == 2){
				if(x < root->left->data) // if case is left to left
					root = LL(root);
				else
					root = LR(root);
			}
		}
        else{        
			if(x > root->data){		// insert in right subtree
				root->right = insert(root->right,x); // newnode will be inserted in right
				
				if(balance_factor(root)== -2){
					if(x  > root->right->data)
						root = RR(root);
					else
						root = RL(root);
				}
			}
		}
	root->height = height(root); // after insertion calculate the height of root
	return root;
}
 
// To find the inorder successor of node X
struct avlnode * inorder_successor(struct avlnode * x) {
	struct avlnode *y;
	if(x == NULL)
	   return NULL;
	
	if(x->right==NULL)
	    return x;

	y= x->right;   // inorder successor is leftmost son of right subtree of x
	while(y->left != NULL)
	   y = y->left;
	 
	return y;   
}

// Deletion in AVL Tree
struct avlnode * Delete(struct avlnode *root, int x) {
  	struct avlnode *insucc;
	
	if(root == NULL) {
		return NULL;
	}
	else {
		if(x < root->data) {
			root->left = Delete(root->left,x);  // node to be deleted is in left
				
				if(balance_factor(root) == -2)	//  Need to Rebalance in right side 
					if(balance_factor(root->right) <= 0)
						root = RR(root);
					else
						root = RL(root);
		}
        else {
			if(x > root->data) {		// Node to be deleted is in right 
				root->right = Delete(root->right,x);
				
				if(balance_factor(root) == 2)   // Need to rebalance in left side
					if(balance_factor(root->left) >= 0)
						root = LL(root);
					else
						root = LR(root);
			} 
			else {		//key to be deleted is found
				
				if(root->right != NULL) {      // that means the node to be deleted has two children or has only right child	
					// find its inorder succesor
					insucc = inorder_successor(root);
				
					root->data = insucc->data;     // exchange key of inorder successor
					root->right = Delete(root->right, insucc->data);
					
					if(balance_factor(root) == 2) {     // Need to rebalance in left side
						if(balance_factor(root->left) >= 0)  // to check for left to left case(R0, R1)
							root = LL(root);
						else        // R-1 condition
							root = LR(root);
					}
				}
				else  // when the root has only left child or it is leaf node
					return root->left;   // root->Left  become new root
			}
		}
	}
	root->height = height(root);
	return root;  // return the modified root after deletion
}
 
// Inorder traversal of AVL Tree 
void inorder(struct avlnode *root) {
	if(root != NULL) {
		inorder(root->left);
		printf("%d(BF = %d)", root->data, balance_factor(root));
		inorder(root->right);
	}
}

// Preorder traversal of AVL Tree 
void preorder(struct avlnode *root) {
	if(root != NULL) {
		printf("%d(BF = %d)", root->data, balance_factor(root));
		preorder(root->left);
		preorder(root->right);
	}
}

int get_choice() {
		int choice;
		printf("\n AVL TREE MENU");
        printf("\n1. Create:");
		printf("\n2. Insert:");
		printf("\n3. Search:");
		printf("\n4. Delete:");
		printf("\n5. Print:");
		printf("\n6. Quit:");
		printf("\n\nEnter Your Choice[1-6]:");
		scanf("%d", &choice);
		
		return choice;
 }
	
void main() {
    struct avlnode *root = NULL;
	struct avlnode *temp;
	int x, n, i;
	int choice;
	
	while(1) {  
        choice = get_choice();	
		switch(choice) {
			case 1: 
                printf("\nEnter no. of elements:");
                scanf("%d",&n);
                printf("\nEnter tree key:");
                root = NULL;
                for(i=0;i<n;i++) {
                    scanf("%d",&x);
                    root = insert(root,x);
                }
                break;
				
			case 2: 
                printf("\nEnter a key:");
                scanf("%d",&x);
                root=insert(root,x);
                break;

			case 3: 
                printf("\nSearch a key:");
                scanf("%d",&x);
                temp = search_node(root, x);
				if(temp == NULL)
                    printf("\nKey does not exist");
                else
                    printf("\nKey exist");
                break;
					
			case 4: 
                printf("\nEnter a key:");
                scanf("%d",&x);
                root = Delete(root,x);
                break;
        
			case 5: 
                printf("1. Inorder sequence of keys:\n");
                printf("2. Preorder sequence of keys:\n");
                printf("\n Enter your choice[1-2]");
                scanf("%d", &choice);
                if(choice == 1)
                    inorder(root);
                else {
                    if(choice ==2)
                        preorder(root);
                    else
                        printf("Wrong order...\n");
				}
                break;	

			case 6: 
                printf("\n Exit from Program...");
                exit(0);

            default: 
                printf("\n Invalid Choice TRY AGAIN[1-6]:");
		}
	}
}

