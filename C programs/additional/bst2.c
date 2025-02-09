// BST implementation using recursion and returning pointer in recursive function
// Only insert function has two versions--- one does not return anything in recursion ---- and the other returns a pointer
//problem-unable to tell if delete was successful
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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

void insertNode(myNode root,int ele){
	if(root->data==ele){
		return;
	}
	else if(ele<root->data)
	{
		if(root->left!=NULL)
			insertNode(root->left,ele);
		else
			root->left=createNode(ele);
	}
	else
	{
		if(root->right!=NULL)
			insertNode(root->right,ele);
		else
			root->right=createNode(ele);	
	}
}

void treeInsertion(myNode* root,int ele)
{
	if((*root)==NULL)
		*root=createNode(ele);
	else
		insertNode(*root,ele);
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
	if(root==NULL){
		printf("Key not found. Delete unsucessful\n");
	}
	else if(root->data==key)
	{
		if(root->left==NULL || root->right==NULL) //no child and single child cases combined
		{
			struct Node* temp=root->left!=NULL?root->left:root->right;
			free(root);
			root=temp;
		}

		// if(root->left==NULL && root->right==NULL)
		// {
		// 	free(root);
		// 	return NULL;
		// }
		// else if(root->left==NULL)
		// {
		// 	struct Node* right=root->right;
		// 	free(root);
		// 	return right;
		// }
		// else if(root->right==NULL)
		// {
		// 	struct Node* left=root->left;
		// 	free(root);
		// 	return left;
		// }
		else
		{	
			root->data=minValue(root->right);
			root->right=deleteNode(root->right,root->data);
		}
		printf("Key %d found. Delete sucessful\n",key);
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
	while(fscanf(fptr,"%d",&num)==1){
			treeInsertion(&root,num);
			// root=insertNode(root,num);
	}
	return root;
}

int main(){
	struct timespec startTime,endTime;
	double timeTaken;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
	myNode root=inputFromFile("case40.txt");
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inserting is %lf microseconds\n",timeTaken);
	
	
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	search(root,5);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for searching is %lf microseconds\n",timeTaken);
	
	printf("Inorder sequence is:\n");
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	inorderTraversal(root);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	printf("\n");
		
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inorder traversal is %lf microseconds\n",timeTaken);

	clock_gettime(CLOCK_MONOTONIC,&startTime);		
	deleteNode(root,5);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for deleting is %lf microseconds\n",timeTaken);
	
	//printf("\nInorder sequence is:\n");
	//inorderTraversal(root);
	printf("\n");
	return 0;
}

// myNode insertNode(myNode root,int ele){
// 	if(root==NULL){
// 		return createNode(ele);
// 	}
// 	else if(root->data==ele){
// 		return root;
// 	}
// 	else if(ele<root->data)
// 	{
// 		root->left=insertNode(root->left,ele);
// 	}
// 	else
// 	{
// 		root->right=insertNode(root->right,ele);
// 	}
// }

/*myNode randomInputCase1(){
	int num=0;
	int N=1000;
	bool firstTime=true;
	myNode root=NULL;

	for(int i=0;i<1000;i++){
		num=rand()%(N-1);
		printf("%d ",num);
		if(firstTime)
			root=createNode(num);
		else
			insertNode(root,num);
		firstTime=false;
	}
	return root;
}*/

