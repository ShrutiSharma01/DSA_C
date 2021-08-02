#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct node{
    int data;
    int height;
    struct node*left;
    struct node*right;
}node;
int max(int h1,int h2) {
    if (h1 > h2)
        return h1;
    return h2;
}
node* create(int x) {
    node *temp = (node *) malloc(sizeof(node));
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
int height(node*root) {
    if (root == NULL) {
        return 0;
    }
    return (height(root->left) > height(root->right) ? height(root->left) + 1 : height(root->right) + 1);
}
node* root_right(node*root) {
    node *p = root->left;
    node *q = p->right;
    p->right = root;
    root->left = q;
    root->height = height(root);
    p->height = height(p);
    return p;
}
node* root_left(node*root) {
    node *p = root->right;
    node *q = p->left;
    p->left = root;
    root->right = q;
    root->height = height(root);
    p->height = height(p);
    return p;
}
int balancing_factor(node*root) {
    return (height(root->left) - height(root->right));
}
node* AVL(node*root,int x) {
    if (root == NULL) {
        root = create(x);
        root->height = 1;
        return root;
    }
    if (x < root->data) {
        root->left = AVL(root->left, x);
    } else {
        root->right = AVL(root->right, x);
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balancing_factor(root);
    if (bf > 1) {
        if (x < root->left->data) {
            return root_right(root);
        } else {
            root->left = root_left(root->left);
            return root_right(root);
        }
    }
    if (bf < -1) {
        if (x > root->right->data) {
            return root_left(root);
        } else {
            root->right = root_right(root->right);
            return root_left(root);
        }
    }
    return root;
}
node* inorder_pre(node*root) {
    node *p, *q;
    p = q = root;
    while (p != NULL) {
        q = p;
        p = p->right;
    }
    return q;
}
node* Deletion(node*root,int x) {
    if (root == NULL) {
        return root;
    }
    if (root->data == x) {
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        } else if (root->left == NULL && root->right != NULL) {
            node *temp = root->right;
            free(root);
            return root->right;
        } else if (root->left != NULL && root->right == NULL) {
            node *temp = root->left;
            free(root);
            return root->left;
        } else {
            node *temp = inorder_pre(root->left);
            root->data = temp->data;
            root->left = Deletion(root->left, temp->data);
        }

    } else if (x < root->data) {
        root->left = Deletion(root->left, x);
    } else {
        root->right = Deletion(root->right, x);
    }
    if (root == NULL) {
        return root;
    }
    root->height = max(height(root->left), height(root->right)) + 1;
    int bf = balancing_factor(root);
    if (bf > 1) {
        if (balancing_factor(root->left) == 1 || balancing_factor(root->left) == 0) {
            return root_right(root);
        } else if (balancing_factor(root->left) == -1) {
            root->left = root_left(root->left);
            return root_right(root);
        }
    }
    if (bf < -1) {
        if (balancing_factor(root->right) == 1 || balancing_factor(root->right) == 0) {
            return root_left(root);
        } else if (balancing_factor(root->right) == -1) {
            root->right = root_right(root->right);
            return root_left(root);
        }

    }
    return root;
}
void in_order(node*root) {
    if (root == NULL) {
        return;
    }
    in_order(root->left);
    printf("%d  ", root->data);
    in_order(root->right);
    return;
}
int main() {
    node *root = NULL;
    while (1) {
        printf("give the data you want to add and give -1 if you dont't want to add any data\n");
        int x;
        scanf("%d", &x);
        if (x == -1) {
            break;
        }
        root = AVL(root, x);
    }
    in_order(root);
    while (1) {
        printf("\n give 'y' if you want to delete any node , otherwise give 'n' \n");
        char c;
        scanf(" %c", &c);
        if (c == 'n') {
            break;
        } else {
            printf("give the data of the node you want to delete\n");
            int x;
            scanf("%d", &x);
            Deletion(root, x);
        }
    }
    in_order(root);
}
