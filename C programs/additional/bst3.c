// BST iterative implementation using prev and curr pointers
//deleteNOde implementation not complete
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Node{
	int data;
	Node* left;
	Node* right;
};

typedef struct Node* myNode;

myNode createNode(int ele){
	myNode newNode=(myNode)malloc(sizeof(struct Node));
	newNode->data=ele;
	newNode->left=NULL;
	newNode->right=NULL;
	return newNode;
}

void insertNode(myNode root,int ele){
    myNode curr=root;
    myNode prev=root;
    bool isLeft=0; //0 is false and 1 is true
    while(curr!=NULL)
    {
        prev=curr;
        if(curr->data==ele)
		    break;
        else if(ele<curr->data)
        {
            curr=curr->left;
            isLeft=1;
        }
        else
        {
            curr=curr->right;
            isLeft=0;
        }
    }
	if(curr==NULL)
    {
        if(isLeft)
            prev->left=createNode(ele);
        else
            prev->right=createNode(ele);
    }	
	
}

void inorderTraversal(myNode root){
	if(root==NULL){
		return;
	}
	inorderTraversal(root->left);
	printf("%d ",root->data);
	inorderTraversal(root->right);
}

void search(myNode root,int key){	
    while(root!=NULL)
    {
        if(root->data==ele)
		    break;
        else if(ele<root->data)
            curr=root->left;
        else
            curr=root->right;
    }
    if(root==NULL)
		printf("Key %d is not present in tree\n",key);
	else if(root->data==key)
		printf("Key %d has been found\n",key);
}

int minValue(myNode root){
	if(root->left==NULL)
		return root->data;
	else
		minValue(root->left);
}

void deleteNode(myNode root,int key){
    myNode curr=root;
    myNode prev=root;
    myNode temp=NULL;
    bool isLeft=0;
    while(curr!==null)
    {
        if(curr->data==ele)
        {
            if(curr->left==NULL || curr->right==NULL)
            {
                temp=curr->left!=NULL?curr->left:curr->right;
                free(curr);
            }
            else
            {	
                curr->data=minValue(curr->right);
                curr->right=deleteNode(curr->right,curr->data);
                temp=curr;
            }
        }
        else if(ele<curr->data){
            prev=curr;
            isLeft=1;
            curr=curr->left;
        }
        else{
            prev=curr;
            isLeft=0;
            curr=curr->right;
        }
    }
	if(curr==NULL)
		printf("Key not found. Delete unsucessful\n");
	else
		printf("Key %d found. Delete sucessful\n",key);
}

myNode inputFromFile(const char* filename){
	FILE* fptr=fopen(filename,"r");
	int num=0;
	bool firstTime=true;
	myNode root=NULL;
	if(fptr==NULL){
		printf("Unable to open file");
		exit(0);
		return NULL;
	}
	while(fscanf(fptr,"%d",&num)==1){
		if(firstTime)
			root=createNode(num);
		else
			insertNode(root,num);
		//root=insertNode(root,num);
		firstTime=false;
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
