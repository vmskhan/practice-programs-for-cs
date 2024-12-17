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
   

    (*x)->height = getMaxSubtreeHeight(*x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
     *x=y;
}

void leftRotate(myNode* x){
    myNode y = (*x)->right;

    (*x)->right = y->left;
    y->left = *x;
    

    (*x)->height = getMaxSubtreeHeight(*x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
    *x=y;
}


void insert(myNode* root, int ele){

    if(*root == NULL){
        *root=createNode(ele);
        return;
    }
    else if(ele < (*root)->data){
        insert(&(*root)->left,ele);
    }
    else if(ele > (*root)->data){
        insert(&(*root)->right,ele);
    }
    
    (*root)->height=getMaxSubtreeHeight(*root)+1;
    int balanceFactor=getBalanceFactor(*root);
    
    if(balanceFactor>1 && (*root)->left->data>ele) //LL
    {
        rightRotate(root);
    }
    else if(balanceFactor<-1 && (*root)->right->data<ele) //RR
    {
        leftRotate(root);
    }
    else if(balanceFactor>1 && (*root)->left->data<ele) //LR
    {
        leftRotate(&(*root)->left);
        rightRotate(root);
    }
    else if(balanceFactor<-1 && (*root)->right->data>ele) //RL
    {
        rightRotate(&(*root)->right);
        leftRotate(root);
    }
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
        //printf("Scanned number: %d\n", num);
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
  
     const char* filename = "case40.txt";
     int key=40;
     int result=0;
     struct timespec start, end;
     double time_taken;
     
     clock_gettime(CLOCK_MONOTONIC, &start);
     myNode root = insertFromFile(filename);
	 clock_gettime(CLOCK_MONOTONIC, &end);
	 time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
	 printf("\nTime taken for insertion: %lf microseconds\n", time_taken);
	 
	 
     printf("Inorder Traversal: ");
     clock_gettime(CLOCK_MONOTONIC, &start);
     inorder(root);
   	 clock_gettime(CLOCK_MONOTONIC, &end);
     printf("\n");
     
   	 time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
	 printf("\nTime taken for inoder traversal: %lf microseconds\n", time_taken);

	
	 clock_gettime(CLOCK_MONOTONIC, &start);
     result=search(root, key);
     clock_gettime(CLOCK_MONOTONIC, &end);
     
     if (result) {
         printf("\nKey %d found",key);
     } else {
         printf("\nKey %d not found",key);
     }

     time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
     printf("\nTime taken for searching: %lf microseconds\n", time_taken);

     
     clock_gettime(CLOCK_MONOTONIC, &start);
     deleteNode(&root,key);
	 clock_gettime(CLOCK_MONOTONIC, &end);
	 
     time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
     printf("\nTime taken for deletion: %lf microseconds\n", time_taken);
     
     return 0;
}