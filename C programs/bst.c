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
    if(root == NULL)
        return 0;
    else if(root->data == key)
        return 1;
    else if(key < root->data)
        return search(root->left,key);
    else
        return search(root->right,key);
}

int getInorderSuccessor(myNode root){
    if(root->left==NULL)
        return root->data;
    else
        return getInorderSuccessor(root->left);
}

int deleteNode(myNode* root,int key){
    if(*root==NULL)
        return 0;
    else if((*root)->data==key)
    {
        if((*root)->left==NULL || (*root)->right==NULL) //no child and single child cases combined
        {
            myNode temp=(*root)->left!=NULL?(*root)->left:(*root)->right;
            free(*root);
            *root=temp;
            return 1;
        }
        else{
            (*root)->data=getInorderSuccessor((*root)->right);
            return deleteNode(&(*root)->right,(*root)->data);
        }
    }
    else if(key<(*root)->data)
        return deleteNode(&(*root)->left,key);
    else
        return deleteNode(&(*root)->right,key);
}

int getDepth(myNode root)
{
  if(root==NULL)
    return 0;
  int left=getDepth(root->left);
  int right=getDepth(root->right);
  return 1+(left>right?left:right);
}

void currentlevel(myNode root, int level)
{
    if (root != NULL) 
    {
        if (level == 1)
            printf("%d ", root->data);
        else if (level > 1) 
        { 
            currentlevel(root->left, level-1); 
            currentlevel(root->right, level-1);
        }			
    }
    else if(level==1)
      printf("Nl ");
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


void inorder(myNode root){
    if(root == NULL)
        return;
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
        // printf("Scanned number: %d\n", num);
        insert(&root, num);
    }
    fclose(file);
    return root;
}

void main(){
    const char* filename = "case40.txt";
    int result=0;
    int key=11;  
    struct timespec startTime,endTime;
	double timeTaken;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
	myNode root=insertFromFile(filename);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inserting is %lf microseconds\n",timeTaken);
	
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	result=search(root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
    if(result == 1)
        printf("\nKey %d found. Search successful\n",key);
    else
        printf("\nKey %d not found. Search unsuccessful\n",key);

	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for searching is %lf microseconds\n",timeTaken);
	
	printf("Inorder sequence is:\n");
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	inorder(root);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	printf("\n");
		
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inorder traversal is %lf microseconds\n",timeTaken);
    // levelOrder(root);
	clock_gettime(CLOCK_MONOTONIC,&startTime);		
	deleteNode(&root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
// 	levelOrder(root);
	if(result)
	  printf("\nKey Element %d successfully deleted\n",key);
	else
	  printf("\nKey Element %d not found. Delete unsuccessful\n",key);
	  
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for deleting is %lf microseconds\n",timeTaken);
	printf("\n");
}