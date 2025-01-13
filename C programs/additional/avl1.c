// level order insert nodes in input file to check any avl tree
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
    if(root!=NULL)
    {
        int a=getNodeheight(root->left);
        int b=getNodeheight(root->right);
        return a-b;
    }
    return 0;
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
    
    if(balanceFactor>1)
    {
        if((*root)->left->data<ele)   //LR
            leftRotate(&(*root)->left);
        rightRotate(root); //LL
    }
    else if(balanceFactor<-1)
    {
        if((*root)->right->data>ele)  //RL
            rightRotate(&(*root)->right);
        leftRotate(root);  //RR
    }

    // if(balanceFactor>1 && (*root)->left->data>ele) //LL
    // {
    //     rightRotate(root);
    // }
    // else if(balanceFactor<-1 && (*root)->right->data<ele) //RR
    // {
    //     leftRotate(root);
    // }
    // else if(balanceFactor>1 && (*root)->left->data<ele) //LR
    // {
    //     leftRotate(&(*root)->left);
    //     rightRotate(root);
    // }
    // else if(balanceFactor<-1 && (*root)->right->data>ele) //RL
    // {
    //     rightRotate(&(*root)->right);
    //     leftRotate(root);
    // }
}

int search(myNode root, int key){
    if(root == NULL)
        return 0;
    else if(root->data == key)
        return 1;
    else if(root->data > key)
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
    int res=0;
    if(*root==NULL)
      return 0;
    else if((*root)->data==key)
    {
        // printf("%d yes %d",(*root)->data,key);
        if((*root)->left==NULL || (*root)->right==NULL) //no child and single child cases combined
        {
            myNode temp=(*root)->left!=NULL?(*root)->left:(*root)->right;
            free(*root);
            *root=temp;
            return 1;
        }
        else{
            (*root)->data=getInorderSuccessor((*root)->right);
            res=deleteNode(&(*root)->right,(*root)->data);
        }
    }
    else if(key<(*root)->data)
         res=deleteNode(&(*root)->left,key);
    else
        res= deleteNode(&(*root)->right,key);

    (*root)->height=getMaxSubtreeHeight(*root)+1;
    int balanceFactor=getBalanceFactor(*root);
    
    if(balanceFactor>1)
    {
        if(getBalanceFactor((*root)->left)<0)   //LR
            leftRotate(&(*root)->left);
        rightRotate(root); //LL
    }
    else if(balanceFactor<-1)
    {
        if(getBalanceFactor((*root)->right)>=0)  //RL
            rightRotate(&(*root)->right);
        leftRotate(root);  //RR
    }
    return res;    
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
            printf("%d ",root->data);
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
    // char num;
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        // if((int)num==32)
        //  continue;
        // printf("Scanned number: %d\n", num);
        insert(&root, num);
    }
    fclose(file);
    return root;
}

int main(){
  
     const char* filename = "case40.txt";
     int key=65;
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
     
     if (result) 
         printf("\nKey %d found",key);
     else
         printf("\nKey %d not found",key);

     time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
     printf("\nTime taken for searching: %lf microseconds\n", time_taken);

    //  levelOrder(root); 
     clock_gettime(CLOCK_MONOTONIC, &start);
     result=deleteNode(&root,key);
	 clock_gettime(CLOCK_MONOTONIC, &end);
// 	 levelOrder(root);
	 if (result) 
         printf("\nKey %d found. Delete successful",key);
     else
         printf("\nKey %d not found. Delete unsuccessful",key);
	 
     time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
     printf("\nTime taken for deletion: %lf microseconds\n", time_taken);

     return 0;
}