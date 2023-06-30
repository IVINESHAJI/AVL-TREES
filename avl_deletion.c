#include <stdio.h>
#include <stdlib.h>

struct Node {

    int height;
    struct Node *lchild;
    struct Node *rchild;
    int data;
};

int max(int a,int b) {

    return (a > b) ? a : b;

}

int height(struct Node *node) {

    if (node == NULL) {
        return 0;
    }

    else {

        int left = height(node -> lchild);
        int right = height(node -> rchild);

        return 1 + max(left,right);
    }
}

struct Node *rightRotate (struct Node* y) {

    struct Node *x = y -> lchild;
    struct Node *x_right = x -> rchild;

    //Right Rotate

    x -> rchild = y;
    y -> lchild = x_right;

    //Update Height
    x -> height = 1 + max(height(x -> lchild),height(x -> rchild));
    y -> height = 1 + max(height(y -> lchild),height(y -> rchild));

    return x;
}

struct Node *leftRotate (struct Node* y) {

    struct Node *x = y -> rchild;
    struct Node *x_left = x -> lchild;

    //Right Rotate

    x -> lchild = y;
    y -> rchild = x_left;

    //Update Height
    x -> height = 1 + max(height(x -> lchild),height(x -> rchild));
    y -> height = 1 + max(height(y -> lchild),height(y -> rchild));

    return x;
}

struct Node *insert(struct Node* node,int data) {

    if (node == NULL) {

        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode -> lchild = newNode -> rchild = NULL;
        newNode -> height = 1;
        newNode -> data = data;

        printf("%d Added Successfully\n",newNode -> data);
        return newNode;
    }

    if (node -> data > data) {

        node -> lchild = insert(node -> lchild,data) ;

    }

    else if (node -> data < data) {

        node -> rchild = insert(node -> rchild,data);

    }

    else {

        printf("%d Already Exists\n",data);

        return node;

    }

    //Update height

    node -> height = 1 + max(height(node -> lchild),height(node ->rchild));

    int balance = height(node -> lchild) - height(node ->rchild);

    if (balance > 1) {

        if (node -> lchild -> data > data) {

            return rightRotate(node);

        }

        else {

            node -> lchild = leftRotate(node -> lchild);
            return rightRotate(node);

        }
    }

    if (balance < -1) {

        if (node -> rchild -> data < data) {

            return leftRotate(node);

        }

        else {

            node -> rchild = rightRotate(node -> rchild);
            return leftRotate(node);

        }
    }

    return node;
}

void inorderTraversal(struct Node* node) {
    if (node != NULL) {
        inorderTraversal(node->lchild);
        printf("%d ", node->data);
        inorderTraversal(node->rchild);
    }
}

struct Node *findMin(struct Node *node) {

    if (node == NULL) {

        return NULL;

    }

    else if (node -> lchild == NULL) {

        return node;

    }

    else {

        return findMin(node -> lchild);

    }
}


struct Node* deletion(struct Node* node, int data) {

    if (node == NULL) {
    
        printf("%d Not in AVL Tree\n", data);
        return node;
    
    }

    if (data < node -> data) {
    
        node -> lchild = deletion(node -> lchild, data);
    } 
    
    else if (data > node->data) {

        node -> rchild = deletion(node -> rchild, data);
    } 
    
    else {

        printf("%d Deleted Successfully\n",data);
        // Node found, perform deletion

        //Node has just 1 child or no child
        if (node -> lchild == NULL ){

            struct Node *temp = node -> rchild;
            free(node);
            return temp;

        } 

        if (node -> rchild == NULL ){

            struct Node *temp = node -> lchild;
            free(node);
            return temp;
            
        } 
        
        else {

            // Node has two children
            struct Node* temp = findMin(node->rchild);
            node->data = temp->data;
            node->rchild = deletion(node->rchild, temp->data);
        }
    }


    // Update the height of the current node
    node->height = 1 + max(height(node->lchild), height(node->rchild));

    // Check the balance factor and perform rotations if necessary
    int balance = height(node->lchild) - height(node->rchild);

    if (balance > 1) {

        if (height(node->lchild->lchild) >= height(node->lchild->rchild)) {

            // Left Left Case
            return rightRotate(node);
        
        } 
        
        else {
        
            // Left Right Case
            node->lchild = leftRotate(node->lchild);
            return rightRotate(node);
        
        }
    } 
    
    else if (balance < -1) {
    
        if (height(node->rchild->rchild) >= height(node->rchild->lchild)) {
    
            // Right Right Case
            return leftRotate(node);
    
        } 
        
        else {
        
            // Right Left Case
            node->rchild = rightRotate(node->rchild);
            return leftRotate(node);
        
        }
    }

    return node;
}


int main() {
    struct Node* root = NULL;

    //Insertion
    root = insert(root, 25);
    root = insert(root, 50);
    root = insert(root, 27);
    root = insert(root, 28);
    root = insert(root, 30);
    root = insert(root, 30);
    root = insert(root, 45);

    printf("In-order traversal of AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    //Deletion
    root = deletion(root,25);
    root = deletion(root,25);

    printf("In-order traversal of AVL tree: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
