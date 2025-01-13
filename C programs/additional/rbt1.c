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

void fixDoubleRed(myNode root,int ele){
    if(root==NULL)
        return;
    else if(root->data==ele)
        return;
    else if(ele<root->data)
        fixDoubleRed(root->left,ele);
    else
        fixDoubleRed(root->right,ele);

   if(root->colour==1 && ((root->right!=NULL && root->right->colour==1) ||(root->left!=NULL && root->left->colour==1))){ // double red problem----here root is parent
        
        bool isRootLeft=root->parent->left==root?true:false;
        bool performedDoubleRotation=false;
        myNode sibling=isRootLeft?root->parent->right:root->parent->left;
        
        if(sibling!=NULL && sibling->colour==1)//red sibling - recolour parent, sibling, and grandparent(if not root)
        {
          root->colour=0;
          sibling->colour=0;
          if(root->parent->parent!=NULL)
              root->parent->colour=1;
        }
        else{//black sibling or null sibling -reorganize using rotation and recolour
          myNode grandParent=root->parent;
          myNode parent=root;
          myNode child=ele<root->data?root->left:root->right;

          //////////////////////** Rotations **//////////////////////////
          
          if(isRootLeft){ 
              if(ele>root->data){//LR- recolour child and gp
                leftRotate(parent);
                 performedDoubleRotation=true;
                }
              rightRotate(grandParent);//LL - recolour parent and gp
            }
          else
          {
            if(ele<root->data){//RL - recolour child and gp
              rightRotate(parent);
              performedDoubleRotation=true;
            }
            leftRotate(grandParent); //RR - recolour parent and gp
          }
          
          ////////////////**  Recolouring **/////////////////////////////////
          
          if(performedDoubleRotation) //only for double rotation child node is at the top, or else parent node is at the top
              child->colour=0;
          else
              parent->colour=0;
          grandParent->colour=1; //irrespective of any case gp is recoloured
        }
    }
}

myNode insertNode(myNode root,int ele){
    if(root==NULL)
        return createNode(ele);
    else if(ele<root->data)
    {
        root->left=insertNode(root->left,ele);
        root->left->parent=root;
    }
    else
    {
        root->right=insertNode(root->right,ele);
        root->right->parent=root;
    }
    return root;
}

int inorderSuccessor(myNode root){
	if(root->left==NULL)
		return root->data;
	else
		inorderSuccessor(root->left);
}

int inorderPredecessor(myNode root){
	if(root->right==NULL)
		return root->data;
	else
		inorderPredecessor(root->right);
}

void fixBlackHeightViolation(myNode root){
        myNode parent=root->parent;
      if(parent!=NULL)//case 2, if node is root node and is double black just skip if condition
      {
        int curNodeColour=root->colour;
        bool isRootLeft=parent->left==root?true:false;
        myNode sibling=isRootLeft?parent->right:parent->left;

        if(curNodeColour==0)//case 1, red leaf node, skip if condition 
        { //case3-6
          myNode nearChild=isRootLeft?sibling->left:sibling->right;
          myNode farChild=isRootLeft?sibling->right:sibling->left;
          int ncColour=nearChild==NULL?0:nearChild->colour;
          int fcColour=farChild==NULL?0:farChild->colour;
          if(sibling->colour==1) //case 4, red sibling - make sibling black & make parent red
          {
              sibling->colour=0;
              parent->colour=1;
              //rotate parent in the direction of db
              if(isRootLeft) //RR case
                leftRotate(parent);
              else
                rightRotate(parent); //LL case
              fixBlackHeightViolation(root); //after rotation check db case on root
          }
         
          else if(ncColour==0 && fcColour==0) //case-3 black sibling with both children black/NULL
          {                             // make sibling red & add black to parent, if db exists fix again, or else exit
            sibling->colour=1;
            if(parent->colour==0) //db
              fixBlackHeightViolation(parent);
            else //red parent, make it black
              parent->colour=0;
          }
          else if(ncColour==1 && fcColour==0)//case-5 black sibling with near child red and far child black
          {                              //make sibling red & make near child black and then apply case -6
              // case 5+6
              sibling->colour=0; //make sibling black as, for case 5 it becomes red and then it case-6 as far child it becomes black
              nearChild->colour=parent->colour;// near child becomes black and then in case 6 as sibling it exchanges colour with parent
              parent->colour=0;//parent becomes black as it exchanges colour with nearchild in case-6
              //rotate sibling in the opposite direction of db
              //rotate parent in direction of db
              if(isRootLeft){ //LL case
                rightRotate(sibling);
                leftRotate(parent);
              }
              else
              {
                leftRotate(sibling); //RR case
                rightRotate(parent); 
              }
          
          }
    
          else if(fcColour==1)    //case-6 black sibling with far child red and near child black
          {                 //covers two red child to black sibling also
            //swap colour of parent and sibling & make farchild black
              sibling->colour=parent->colour;
              parent->colour=0; // since it is black sibling
              farChild->colour=0;
              //rotate parent in db direction
              if(isRootLeft) 
                leftRotate(parent);
              else
                rightRotate(parent); 
          }
        }
      }
}

int deleteNode(myNode root,int key){
	if(root==NULL)
		return 0;
	else if(root->data==key)
	{
		if(root->left==NULL && root->right==NULL)
		{
      fixBlackHeightViolation(root);
      if(root->parent->left==root)
          root->parent->left=NULL;
        else
          root->parent->right=NULL;
			free(root);
			return 1;
		}
		else
		{	if(root->right!=NULL)
			{ 
			    root->data=inorderSuccessor(root->right);
			    return deleteNode(root->right,root->data);
			}
			else
			{
			    root->data=inorderPredecessor(root->left);
			    return deleteNode(root->left,root->data);
			}
		}
	}
	else if(key<root->data)
		return deleteNode(root->left,key);
	else
		return deleteNode(root->right,key);
}

myNode treeInsertion(myNode root,int ele){
  if(root==NULL)
  {
    root=createNode(ele);
    root->colour=0;
  }
  else{
    root=insertNode(root,ele);
    fixDoubleRed(root,ele);
  }
  while(root->parent!=NULL)
		  root=root->parent;
    return root;
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
    printf("\nKey %d found. Delete sucessful\n",key);
  else
    printf("\nKey not found. Delete unsucessful\n");
    
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
	if(root==NULL)
		return;

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
	{
	    levelOrder(root);
			root=treeInsertion(root,num);   
// 			levelOrder(root);
	}
	return root;
}

void printTime(struct timespec startTime, struct timespec endTime,char* operation)
{
    double timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for %s is %lf microseconds\n",operation,timeTaken);
}


int main(){
	struct timespec startTime,endTime;
    int key=30;
    
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
	treeDeletion(&root,key);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    // levelOrder(root);
    printTime(startTime,endTime,"Deletion");

	printf("\n");
	return 0;
}
