// BST implementation using recursion and returning pointer in recursive function
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

struct Node{
	int data;
	struct Node* left;
	struct Node* right;
};

typedef struct Node* myNode;

myNode createNode(int ele){
	myNode newNode=(myNode)malloc(sizeof(struct Node));
	newNode->data=ele;
	newNode->left=newNode->right=NULL;
	return newNode;
}

myNode insertNode(myNode root,int ele){
	if(root==NULL)
		return createNode(ele);
	else if(ele<root->data)
		root->left=insertNode(root->left,ele);
	else if(ele>root->data)
		root->right=insertNode(root->right,ele);
    return root;
}

void inorderTraversal(myNode root){
	if(root==NULL)
		return;
	inorderTraversal(root->left);
	printf("%d ",root->data);
	inorderTraversal(root->right);
}

void search(myNode root,int key){
	if(root==NULL)
		printf("Key %d is not present in tree\n",key);
	else if(root->data==key)
		printf("Key %d has been found\n",key);
	else if(key<root->data)
		search(root->left,key);
	else
		search(root->right,key);
}

int minValue(myNode root){
	if(root->left==NULL)
		return root->data;
	else
		minValue(root->left);
}

myNode deleteNode(myNode root,int key){
	if(root==NULL)
		printf("Key not found. Delete unsucessful\n");
	else if(root->data==key)
	{
		if(root->left==NULL || root->right==NULL) //no child and single child cases combined
		{
			struct Node* temp=root->left!=NULL?root->left:root->right;
			free(root);
			root=temp;
            printf("Key found. Delete sucessful\n");
		}
		else
		{	
			root->data=minValue(root->right);
			root->right=deleteNode(root->right,root->data);
		}
	}
	else if(key<root->data)
		root->left=deleteNode(root->left,key);
	else
		root->right=deleteNode(root->right,key);
	return root;
}

myNode inputFromFile(const char* filename){
	FILE* fptr=fopen(filename,"r");
	int num=0;
	myNode root=NULL;
	if(fptr==NULL){
		printf("Unable to open file");
		exit(0);
		return NULL;
	}
	while(fscanf(fptr,"%d",&num)==1)
			root=insertNode(root,num);
	return root;
}

void printTime(struct timespec startTime, struct timespec endTime,char* operation)
{
    double timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for %s is %lf microseconds\n",operation,timeTaken);
}

int main(){
	struct timespec startTime,endTime;
	int key=5;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
	myNode root=inputFromFile("case40.txt");
	clock_gettime(CLOCK_MONOTONIC,&endTime);	
	printTime(startTime,endTime,"Insertion");
	
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	search(root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	printTime(startTime,endTime,"searching");
	
	printf("Inorder sequence is:\n");
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	inorderTraversal(root);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	printf("\n");	
    printTime(startTime,endTime,"Inorder traversal");

    // levelOrder(root);
	clock_gettime(CLOCK_MONOTONIC,&startTime);		
	root=deleteNode(root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    // levelOrder(root);
    printTime(startTime,endTime,"Deletion");
	
	printf("\n");
	return 0;
}


// int getDepth(myNode root)
// {
//   if(root==NULL)
//     return 0;
//   int left=getDepth(root->left);
//   int right=getDepth(root->right);
//   return 1+(left>right?left:right);
// }

// void currentlevel(myNode root, int level)
// {
//     if (root != NULL) 
//     {
//         if (level == 1)
//             printf("%d ", root->data);
//         else if (level > 1) 
//         { 
//             currentlevel(root->left, level-1); 
//             currentlevel(root->right, level-1);
//         }			
//     }
//     else if(level==1)
//       printf("Nl ");
// }

// void levelOrder(myNode root){
  
//    int depth=getDepth(root);
//     /* Calling current level function, by passing levels one by one. */
//     printf("\n");
//     for(int i = 1; i <= depth; i++)      
//     {
//         currentlevel(root,i);
//         printf("\n");
//     }
// }