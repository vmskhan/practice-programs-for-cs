// level order insert nodes in input file to check any avl tree
//avl implementation using only recursion and returning pointer in recursion
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
    int a=getNodeheight(root->left);
    int b=getNodeheight(root->right);
    return a-b;
}

myNode rightRotate(myNode x){
    myNode y = x->left;

    x->left = y->right;
    y->right = x;
   

    x->height = getMaxSubtreeHeight(x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
    return y;
}

myNode leftRotate(myNode x){
    myNode y = x->right;

    x->right = y->left;
    y->left = x;
    

    x->height = getMaxSubtreeHeight(x) + 1;
    y->height = getMaxSubtreeHeight(y) + 1;
    return y;
}


myNode insert(myNode root, int ele){

    if(root == NULL)
        return createNode(ele);
    else if(ele < root->data)
        root->left=insert(root->left,ele);
    else if(ele > root->data){
        root->right=insert(root->right,ele);
    }
    
    root->height=getMaxSubtreeHeight(root)+1;
    int balanceFactor=getBalanceFactor(root);
    
    if(balanceFactor>1)
    {
        if(root->left->data<ele)   //LR
            root->left=leftRotate(root->left);
        root=rightRotate(root); //LL
    }
    else if(balanceFactor<-1)
    {
        if(root->right->data>ele)  //RL
            root->right=rightRotate(root->right);
        root=leftRotate(root);  //RR
    }
    return root;
}

void search(myNode root, int key){
    if(root == NULL)
        printf("\nKey %d not found",key);
    else if(root->data == key)
        printf("\nKey %d found",key);
    else if(root->data > key)
        search(root->left,key);
    else 
        search(root->right,key);
}



int getInorderSuccessor(myNode root){
    if(root->left==NULL)
        return root->data;
    else
        return getInorderSuccessor(root->left);
}

myNode deleteNode(myNode root,int key){
    if(root==NULL){
      printf("\nKey %d not found. Delete unsuccessful",key);
        return root;
    }
    else if(root->data==key)
    {
        if(root->left==NULL || root->right==NULL) //no child and single child cases combined
        {
            myNode temp=root->left!=NULL?root->left:root->right;
            free(root);
            root=temp;
            printf("\nKey found. Delete successful");
            return root;
        }
        else{
            root->data=getInorderSuccessor(root->right);
            root->right=deleteNode(root->right,root->data);
        }
    }
    else if(key<root->data)
         root->left=deleteNode(root->left,key);
    else
        root->right=deleteNode(root->right,key);

    root->height=getMaxSubtreeHeight(root)+1;
    int balanceFactor=getBalanceFactor(root);
    
    if(balanceFactor>1)
    {
        if(getBalanceFactor(root->left)<0)   //LR
            root->left=leftRotate(root->left);
        root=rightRotate(root); //LL
    }
    else if(balanceFactor<-1)
    {
        if(getBalanceFactor(root->right)>=0)  //RL
            root->right=rightRotate(root->right);
        root=leftRotate(root);  //RR
    }
    return root;    
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
        root=insert(root, num);
    }
    fclose(file);
    return root;
}

void printTime(struct timespec startTime, struct timespec endTime,char* operation)
{
    double timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for %s is %lf microseconds\n",operation,timeTaken);
}


int main(){
  
     const char* filename = "case40.txt";
     int key=15;
     struct timespec startTime, endTime;
     
     clock_gettime(CLOCK_MONOTONIC, &startTime);
     myNode root = insertFromFile(filename);
	 clock_gettime(CLOCK_MONOTONIC, &endTime);
     printTime(startTime,endTime,"Insertion");
	 
	 
     printf("Inorder Traversal: ");
     clock_gettime(CLOCK_MONOTONIC, &startTime);
     inorder(root);
   	 clock_gettime(CLOCK_MONOTONIC, &endTime);
     printf("\n");
     
   	 printTime(startTime,endTime,"Inorder travesal");

	
	 clock_gettime(CLOCK_MONOTONIC, &startTime);
     search(root, key);
     clock_gettime(CLOCK_MONOTONIC, &endTime);

     printTime(startTime,endTime,"searching");

    //  levelOrder(root); 
     clock_gettime(CLOCK_MONOTONIC, &startTime);
     root=deleteNode(root,key);
	 clock_gettime(CLOCK_MONOTONIC, &endTime);
	//  levelOrder(root);
    printTime(startTime,endTime,"Deletion");

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
//             printf("%d ",root->data);
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