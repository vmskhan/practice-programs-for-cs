// BST implementation using double pointers and recursion without returning anything in recursive function
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
    else if(root->data == key){
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
    
}


void main(){
    const char* filename = "case10.txt";
    int result=0;
    int key=40;  
    struct timespec startTime,endTime;
	double timeTaken;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
	myNode root=inputFromFile(filename);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inserting is %lf microseconds\n",timeTaken);
	
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	result=search(root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
    if(result == 1) {
        printf("\nKey found\n");
    } else {
        printf("\nKey not found\n");
    }

	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for searching is %lf microseconds\n",timeTaken);
	
	printf("Inorder sequence is:\n");
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	inorder(root);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	printf("\n");
		
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inorder traversal is %lf microseconds\n",timeTaken);

	clock_gettime(CLOCK_MONOTONIC,&startTime);		
	deleteNode(&root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for deleting is %lf microseconds\n",timeTaken);
	printf("\n");
}