#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node* left;
    struct Node* right;
    int height;
};

typedef struct Node* myNode;

myNode createNode(int data){
    myNode node = (myNode)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    node->height=1;
    return node;
}

int getNodeheight(myNode root){
    return root != NULL ? root->height : 0;
}

int getMaxSubtreeHeight(myNode root) {
    int a=getNodeheight(root->left);
    int b=getNodeheight(root->right);
    return a > b ? a : b;
}

int getBalanceFactor(myNode root){
    int a=getNodeheight(root->left);
    int b=getNodeheight(root->right);
    return root != NULL ? a-b : 0 ;
}

void rightRotate(myNode* x){
    myNode y = (*x)->left;

    (*x)->left = y->right;
    y->right = *x;
    *x=y;

    (*x)->height = getMaxSubtreeHeight(*x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
}

void leftRotate(myNode* x){
    myNode y = (*x)->right;

    (*x)->right = y->left;
    y->left = *x;
    *x=y;

    (*x)->height = getMaxSubtreeHeight(*x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
}


void insert(myNode* root, int ele){
    printf("a");
    if(*root == NULL){
        printf("b");
        *root=createNode(ele);
        return;
    }
    else if(ele < (*root)->data){
        printf("b");
        insert(&(*root)->left,ele);
    }
    else if(ele > (*root)->data){
        printf("c");
        insert(&(*root)->right,ele);
    }
    printf("d");
    (*root)->height=getMaxSubtreeHeight(*root)+1;
    int balanceFactor=getBalanceFactor(*root);
    printf("e");
    if(balanceFactor>1 && (*root)->left->data>ele) //LL
    {
        printf("f");
        rightRotate(root);
        printf("g");
    }
    else if(balanceFactor<-1 && (*root)->right->data<ele) //RR
    {
        printf("h");
        leftRotate(root);
        printf("i");
    }
    else if(balanceFactor>1 && (*root)->left->data<ele) //LR
    {
        printf("j");
        leftRotate(&(*root)->left);
        printf("k");
        rightRotate(root);
        printf("l");
    }
    else if(balanceFactor<-1 && (*root)->right->data>ele) //RL
    {
        printf("m");
        rightRotate(&(*root)->right);
        printf("n");
        leftRotate(root);
        printf("o");
    }
    printf("p");
}

int search(myNode root, int key){
    if(root == NULL){
        return 0;
    }
    else if(root->data == key){
        return 1;
    }
    else if(root->data > key){
        return search(root->left,key);
    }
    else 
    //if(root->data < key)
    {
        return search(root->right,key);
    }
    //return 0;
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
        printf("hai");
        insert(&root, num);
        inorder(root);
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

void deleteNode(myNode* root,int key){
    if(*root==NULL)
    {
        printf("Key Element %d not found\n",key);
        // return root;
    }
    else if((*root)->data==key)
    {
        if((*root)->left==NULL && (*root)->right==NULL)
        {
            free(*root);
            *root=NULL;
            return;
        }
        else if((*root)->left==NULL){
            myNode temp=(*root)->right;
            free(*root);
            *root=temp;
        }
        else if((*root)->right==NULL)
        {
            myNode temp=(*root)->left;
            free(*root);
            *root=temp;
        }
        else{
            (*root)->data=getInorderSuccessor((*root)->right);
            deleteNode(&(*root)->right,(*root)->data);
        }
    }
    else if(key<(*root)->data)
    {
        deleteNode(&(*root)->left,key);
    }
    else{
        deleteNode(&(*root)->right,key);
    }
    
    (*root)->height=getMaxSubtreeHeight(*root)+1;
    int balanceFactor=getBalanceFactor(*root);
    if(balanceFactor>1 && (*root)->left->data>key) //LL
    {
        rightRotate(root);
    }
    else if(balanceFactor<-1 && (*root)->right->data<key) //RR
    {
        leftRotate(root);
    }
    else if(balanceFactor>1 && (*root)->left->data<key) //LR
    {
        leftRotate(&(*root)->left);
        rightRotate(root);
    }
    else if(balanceFactor<-1 && (*root)->right->data>key) //RL
    {
        rightRotate(&(*root)->right);
        leftRotate(root);
    }
    
}


void main(){
    const char* filename = "case3a.txt";
    myNode root = insertFromFile(filename);
    inorder(root);    
    if(search(root, 3) == 1) {
        printf("\nKey found\n");
    } else {
        printf("\nKey not found\n");
    }
    deleteNode(&root,5);
    inorder(root);
}