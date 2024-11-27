#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node* myNode;
myNode createNode(int data){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

void insert(myNode* root, int data){
    if(*root == NULL){
        *root=createNode(data);
    }
    else if(data < (*root)->data){
        insert(&(*root)->left,data);
    }
    else if(data > (*root)->data){
        insert(&(*root)->right,data);
    }
}

int search(myNode root, int key){
    if(root == NULL){
        return 0;
    }
    if(root->data == key){
        return 1;
    }
    else if(root->data > key){
        return search(root->left,key);
    }
    else if(root->data < key){
        return search(root->right,key);
    }
    return 0;
}

void inorder(myNode root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

myNode insertFromFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file");
        return NULL;
    }
    myNode root = NULL;
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        printf("Scanned number: %d\n", num);
        insert(&root, num);
    }

    fclose(file);
    return root;
}

int getInorderSuccessor(myNode root){
    if(root->left==NULL)
        return root->data;
    else
        return getInorderSuccessor(root->left);
    
}

myNode deleteNode(myNode root,int key){
    if(root==NULL)
    {
        printf("Key Element %d not found\n",key);
        return root;
    }
    else if(root->data==key)
    {
        if(root->left==NULL && root->right==NULL)
        {
            free(root);
            return NULL;
        }
        else if(root->left==NULL){
            myNode temp=root->right;
            free(root);
            return temp;
        }
        else if(root->right==NULL)
        {
            myNode temp=root->left;
            free(root);
            return temp;
        }
        else{
            root->data=getInorderSuccessor(root->right);
            root->right=deleteNode(root->right,root->data);
        }
    }
    else if(key<root->data)
    {
        root->left=deleteNode(root->left,key);
    }
    else{
        root->right=deleteNode(root->right,key);
    }
    return root;
}



void main(){
    const char* filename = "case4.txt";
    myNode root = insertFromFile(filename);
    inorder(root);    
    if(search(root, 3) == 1) {
        printf("\nKey found\n");
    } else {
        printf("\nKey not found\n");
    }
    deleteNode(root,5);
    inorder(root);
}