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

    //Left Rotate

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

int main() {
    struct Node* root = NULL;

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

    return 0;
}
