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
        printf("\nentered");
        myNode parent=root->parent;
        bool isRootLeft=false;
        myNode sibling=NULL;
        int curNodeColour=root->colour;

     
      if(parent!=NULL)
      {
        isRootLeft=parent->left==root?true:false;
        sibling=isRootLeft?parent->right:parent->left;
        
         //case 1, root->colour=1 , red node, only delete node, skip if condition
        //case 2, if node is root node and is double black then make it single black, so here keep it unchanged, nothing to do just skip if condition
        //case3-6, also case-2 got covered with outer if condition for parent
        if(curNodeColour==0)
        {
          //case 4, red sibling (red sibling will only have black children ,even if its null children)
          if(sibling->colour==1)
          {
              printf("\ncase4");
            //make sibling black
            // make parent red
              sibling->colour=0;
              parent->colour=1;
              //rotate parent in the direction of db
              if(isRootLeft) //RR case
                leftRotate(parent);
              else
                rightRotate(parent); //LL case
               printf("\ncase4 complete");
              //after rotation check db case on root
            //   fixBlackHeightViolation(root);
               printf("\ncase4 fully complete");
          }
          //case-3,5,6
          else
          {
            //case3, black sibling with black children
          //there will always be a black/red sibling for a black node, no need to check for null
            myNode nearChild=isRootLeft?sibling->left:sibling->right;
            myNode farChild=isRootLeft?sibling->right:sibling->left;
            int ncColour=nearChild==NULL?0:nearChild->colour;
            int fcColour=farChild==NULL?0:farChild->colour;
            //case-3 black sibling with both children black/NULL
            if(ncColour==0 && fcColour==0)
            {
                printf("\ncase3");
              //make sibling red
              sibling->colour=1;
              // add black to parent, if db exists fix again, or else exit
              if(parent->colour=0) //db
                fixBlackHeightViolation(parent);
              else //red parent, make it black
                parent->colour=0;
            }
            
            else{ 
              //case-5 black sibling with near child red and far child black
              if(ncColour==1 && fcColour==0)
              {
                  printf("\ncase5");
                //make sibling red
                // make near child black
                  sibling->colour=1;
                  if(nearChild!=NULL)
                    nearChild->colour=0;
                  //rotate sibling in the opposite direction of db
                  if(isRootLeft) //LL case
                    rightRotate(sibling);
                  else
                    leftRotate(sibling); //RR case
                  
                 //apply case -6
              }
              //case-6 black sibling with far child red and near child black
              sibling=isRootLeft?parent->right:parent->left;
              myNode nearChild=isRootLeft?sibling->left:sibling->right;
              myNode farChild=isRootLeft?sibling->right:sibling->left;
              if(fcColour==1) //covers two red child to black sibling also
              {
                  printf("\ncase6");
                //swap colour of parent and sibling
                //make farchild black
                  sibling->colour=parent->colour;
                  parent->colour=0; // since it is black sibling
                  if(farChild!=NULL)
                    farChild->colour=0;

                //rotate parent in db direction
                  if(isRootLeft) 
                    leftRotate(parent);
                  else
                    rightRotate(parent); 
                  
                  // fixBlackHeightViolation(root);
              }
            }

          }

        }
        else
            printf("\ncase1 or case 2");
      }
      
}

int deleteNode(myNode root,int key){
	if(root==NULL)
		return 0;
	else if(root->data==key)
	{
		if(root->left==NULL && root->right==NULL)
		{
		    printf("\nenter checking");
      fixBlackHeightViolation(root);
      printf("\nexit checking");
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
    int key=15;
    
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	myNode root=inputFromFile("case40.txt");
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inserting is %lf microseconds\n",timeTaken);
	
	
	clock_gettime(CLOCK_MONOTONIC,&startTime);
	search(root,key);
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
   levelOrder(root);
	clock_gettime(CLOCK_MONOTONIC,&startTime);		
	treeDeletion(&root,key);
// 	treeDeletion(&root,44);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	levelOrder(root);
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

////////////////////////
//In insertion function logic to solve double red problem
////////////////////////

// if(root->colour==1 && ((root->right!=NULL && root->right->colour==1) ||(root->left!=NULL && root->left->colour==1))){ // double red problem----here root is parent
        // if(root->parent->left==root)// root is left child
        // {
        //     if(root->parent->right!=NULL && root->parent->right->colour==1) //red sibling
        //     {
        //         //recolour parent, sibling, and grandparent(if not root)
        //         root->colour=0;
        //         root->parent->right->colour=0;
        //         if(root->parent->parent!=NULL)
        //             root->parent->colour=1;
        //             // root->parent->colour=(root->parent->colour+1)%2;
        //     }
        //     else{ //black sibling or null sibling
        //         //reorganize using rotation (LL or LR)  and recolour
        //         if(ele<root->data) //LL
        //         {
        //             rightRotate(root->parent);
        //             //recolour parent and grandparent
        //             root->colour=0;
        //             root->right->colour=1;
        //         }
        //         else  //LR
        //         {
        //             leftRotate(root);
        //             rightRotate(root->parent->parent);
        //             //recolour child and grandparent
        //             root->parent->colour=0;
        //             root->parent->right->colour=1;
        //         }
        //     }
        // }
        // else{ // root is right child
        //     if(root->parent->left!=NULL && root->parent->left->colour==1) //red sibling
        //     {
        //         //recolour parent, sibling, and grandparent(if not root)
        //         root->colour=0;
        //         root->parent->left->colour=0;
        //         if(root->parent->parent!=NULL)
        //         {
        //             root->parent->colour=1;
        //         }
        //     }
        //     else{ //black sibling or null sibling
        //         //reorganize using rotation (RR or RL)  and recolour
        //         if(ele>root->data) //RR
        //         {
        //             leftRotate(root->parent);
        //             //recolour parent and grandparent
        //             root->colour=0;
        //             root->left->colour=1;
        //         }
        //         else  //RL
        //         {
        //             rightRotate(root);
        //             leftRotate(root->parent->parent);
        //             //recolour child and grandparent
        //             root->parent->colour=0;
        //             root->parent->left->colour=1;

        //         }
        //     }
        // }
    // }
