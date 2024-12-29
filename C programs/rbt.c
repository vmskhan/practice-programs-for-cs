// BST implementation using recursion and returning pointer in recursive function
// Only insert function has two versions--- one does not return anything in recursion ---- and the other returns a pointer
//Have to work on delete function and then optimize and reduce code
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<math.h>

struct Node{
	int data;
	int colour; //0-black or 1-red
    struct Node* left;
	struct Node* right;
    struct Node* parent;

};

typedef struct Node* myNode;

myNode createNode(int ele){
	myNode newNode=(myNode)malloc(sizeof(struct Node));
	newNode->data=ele;
	newNode->left=NULL;
	newNode->right=NULL;
    newNode->parent=NULL;
    newNode->colour=1; //new red node
	return newNode;
}

void rightRotate(myNode x){
    myNode y=x->left;
    if(x->parent!=NULL){
      if(x->parent->left==x)
          x->parent->left=y;
      else
          x->parent->right=y;
    }
    x->left=y->right;
    y->right=x;
    if(x->left!=NULL) //if right child of y assigned left of x is not null, change its parent
        x->left->parent=x;
    y->parent=x->parent;
    x->parent=y;
}

void leftRotate(myNode x){
    myNode y=x->right;
    if(x->parent!=NULL)
    {
      if(x->parent->left==x)
          x->parent->left=y;
      else
          x->parent->right=y;
    }
    x->right=y->left;
    y->left=x;
    if(x->right!=NULL) //if left child of y assigned right of x is not null, change its parent
        x->right->parent=x;
    y->parent=x->parent;
    x->parent=y;
}



void insertNode(myNode root,int ele){
	if(root->data==ele){
		return;
	}
	
	else if(ele<root->data)
	{
		if(root->left!=NULL)
			insertNode(root->left,ele);
		else{
			root->left=createNode(ele);
            root->left->parent=root;
        }
	}
	
	else
	{
		if(root->right!=NULL)
			insertNode(root->right,ele);
		else{
			root->right=createNode(ele);	
            root->right->parent=root;
        }
	}
     if(root->colour==1 && ((root->right!=NULL && root->right->colour==1) ||(root->left!=NULL && root->left->colour==1))){ // double red problem----here root is parent
        if(root->parent->left==root)// root is left child
        {
            if(root->parent->right!=NULL && root->parent->right->colour==1) //red sibling
            {
                //recolour parent, sibling, and grandparent(if not root)
                root->colour=0;
                root->parent->right->colour=0;
                if(root->parent->parent!=NULL)
                    root->parent->colour=1;
                    // root->parent->colour=(root->parent->colour+1)%2;
            }
            else{ //black sibling or null sibling
                //reorganize using rotation (LL or LR)  and recolour
                if(ele<root->data) //LL
                {
                    rightRotate(root->parent);
                    //recolour parent and grandparent
                    root->colour=0;
                    root->right->colour=1;
                }
                else  //LR
                {
                    leftRotate(root);
                    rightRotate(root->parent->parent);
                    //recolour child and grandparent
                    root->parent->colour=0;
                    root->parent->right->colour=1;
                }
            }
        }
        else{ // root is right child
            if(root->parent->left!=NULL && root->parent->left->colour==1) //red sibling
            {
                //recolour parent, sibling, and grandparent(if not root)
                root->colour=0;
                root->parent->left->colour=0;
                if(root->parent->parent!=NULL)
                {
                    root->parent->colour=1;
                }
            }
            else{ //black sibling or null sibling
                //reorganize using rotation (RR or RL)  and recolour
                if(ele>root->data) //RR
                {
                    leftRotate(root->parent);
                    //recolour parent and grandparent
                    root->colour=0;
                    root->left->colour=1;
                }
                else  //RL
                {
                    rightRotate(root);
                    leftRotate(root->parent->parent);
                    //recolour child and grandparent
                    root->parent->colour=0;
                    root->parent->left->colour=1;

                }
            }
        }
    }


}

int minValue(myNode root){
	if(root->left==NULL)
		return root->data;
	else
		minValue(root->left);
}


int deleteNode(myNode root,int key){
	if(root==NULL){
		return 0;
	}
	else if(root->data==key)
	{
		if(root->left==NULL || root->right==NULL)
		{
		  struct Node* temp=root->left==NULL?root->right:root->left;
		  if(root->parent->left==root)
		    root->parent->left=temp;
		  else
		      root->parent->right=temp;
		  if(temp!=NULL)
		    temp->parent=root->parent;
			free(root);
			return 1;
		}
		else
		{	
			root->data=minValue(root->right);
			return deleteNode(root->right,root->data);
		}
	}
	else if(key<root->data)
		return deleteNode(root->left,key);
	else
		return deleteNode(root->right,key);
		
	
}

void treeInsertion(myNode* root,int ele){
  if(*root==NULL)
  {
    *root=createNode(ele);
    (*root)->colour=0;
    
  }
  else
    insertNode(*root,ele);
  while((*root)->parent!=NULL)
		  *root=(*root)->parent;
}

void treeDeletion(myNode* root,int key)
{
  int result=0;
  if((*root)!=NULL && (*root)->data==key && (*root)->left==NULL && (*root)->right==NULL)
  {
    free(*root);
    *root=NULL;
    printf("Key %d found. Delete sucessful\n",key);
    return;
  }
  else
    result=deleteNode(*root,key);
  
  if(result)
    printf("Key %d found. Delete sucessful\n",key);
  else
    printf("Key not found. Delete unsucessful\n");
    
  while((*root)->parent!=NULL)
		  *root=(*root)->parent;
    
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


void inorderTraversal(myNode root){
	if(root==NULL){
		return;
	}
	inorderTraversal(root->left);
	printf("%d ",root->data);
	inorderTraversal(root->right);
}


int getDepth(myNode root)
{
  if(root==NULL)
    return 0;
  int left=getDepth(root->left);
  int right=getDepth(root->right);
  return 1+(left>right?left:right);
}
// void treePrinter(myNode root){
//   int depth=getDepth(root)-1;
//   int spaces=1;
//   if(depth==1)
//     spaces=3;
//     else if(depth>=2)
//       spaces=pow(2,depth-1)*3;
//     printf("%d %d",depth,spaces);
    
  
// }

void currentlevel(myNode root, int level)
{
    if (root != NULL) 
    {
        if (level == 1)
        {
            printf("%d", root->data);
            if(root->colour)
              printf("R ");
            else
              printf("B ");
        }
        else if (level > 1) 
        { 
            currentlevel(root->left, level-1); 
            currentlevel(root->right, level-1);
        }			
    }
    else{
      printf("Nl ");
    }
}

void levelOrder(myNode root){
  
   int depth=getDepth(root);
    /* Calling current level function, by passing levels one by one. */
    printf("\n");
    for(int i = 1; i <= depth; i++)      
    {
        currentlevel(root,i);
        printf("\n");
    }
}

myNode inputFromFile(const char* filename){
	FILE* fptr=fopen(filename,"r");
	int num=0;
	myNode root=NULL;
	if(fptr==NULL){
		printf("Unable to open file");
		exit(0);
	}
	while(fscanf(fptr,"%d",&num)==1)
			treeInsertion(&root,num);   
			
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

  // treePrinter(root);
  // levelOrder(root);
// 	clock_gettime(CLOCK_MONOTONIC,&startTime);		
// 	deleteNode(root,5);
// 	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
// 	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
// 	printf("\nTime taken for deleting is %lf microseconds\n",timeTaken);
	
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

