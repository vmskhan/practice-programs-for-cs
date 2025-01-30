#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct SplayTreeNode {
    int key;
    struct SplayTreeNode *left, *right;
} SplayTreeNode;

typedef struct SplayTree {
    SplayTreeNode *root;
} SplayTree;

// Helper function to create a new node
SplayTreeNode* newNode(int key) {
    SplayTreeNode* node = (SplayTreeNode*) malloc(sizeof(SplayTreeNode));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Right rotation
SplayTreeNode* rightRotate(SplayTreeNode* x) {
    SplayTreeNode* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

// Left rotation
SplayTreeNode* leftRotate(SplayTreeNode* x) {
    SplayTreeNode* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

// Splay operation (bottom-up)
SplayTreeNode* splay(SplayTreeNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    // If the key is in the left subtree
    if (key < root->key) {
        // Key is not in the tree
        if (root->left == NULL)
            return root;

        // Zig-Zig (Left-Left)
        if (key < root->left->key) {
            root->left->left = splay(root->left->left, key);
            root = rightRotate(root);
        }
        // Zig-Zag (Left-Right)
        else if (key > root->left->key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = leftRotate(root->left);
        }

        // Perform final rotation
        return (root->left == NULL) ? root : rightRotate(root);
    } else { // If the key is in the right subtree
        // Key is not in the tree
        if (root->right == NULL)
            return root;

        // Zag-Zig (Right-Left)
        if (key < root->right->key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = rightRotate(root->right);
        }
        // Zag-Zag (Right-Right)
        else if (key > root->right->key) {
            root->right->right = splay(root->right->right, key);
            root = leftRotate(root);
        }

        // Perform final rotation
        return (root->right == NULL) ? root : leftRotate(root);
    }
}

// Insert operation
SplayTreeNode* insert(SplayTreeNode* root, int key) {
    if (root == NULL) 
        return newNode(key);

    root = splay(root, key);

    // If the key is already in the tree, do nothing
    if (root->key == key)
        return root;

    // Otherwise, create a new node
    SplayTreeNode* new_node = newNode(key);

    // If the key is smaller than root's key, make the new node as root's left child
    if (key < root->key) {
        new_node->right = root;
        new_node->left = root->left;
        root->left = NULL;
    } 
    // If the key is greater, make the new node as root's right child
    else {
        new_node->left = root;
        new_node->right = root->right;
        root->right = NULL;
    }
    
    return new_node;
}

// Delete operation
SplayTreeNode* delete(SplayTreeNode* root, int key) {
    if (root == NULL) 
        return root;

    root = splay(root, key);

    // If key is not found, return the root as it is
    if (root->key != key)
        return root;

    // Key found, now delete it
    SplayTreeNode *temp;
    if (root->left == NULL) {
        temp = root;
        root = root->right;
    } else {
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right;
    }
    
    free(temp);
    return root;
}

// Search operation
SplayTreeNode* search(SplayTreeNode* root, int key) {
    return splay(root, key);
}

// In-order traversal to print the tree
void inorder(SplayTreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}


int getDepth(SplayTreeNode* root)
{
  if(root==NULL)
    return 0;
  int left=getDepth(root->left);
  int right=getDepth(root->right);
  return 1+(left>right?left:right);
}

void currentlevel(SplayTreeNode* root, int level)
{
    if (root != NULL) 
    {
        if (level == 1)
            printf("%d ", root->key);
        else if (level > 1) 
        { 
            currentlevel(root->left, level-1); 
            currentlevel(root->right, level-1);
        }			
    }
    else if(level==1){
      printf("Nl ");
    }
}

void levelOrder(SplayTreeNode* root){
  
   int depth=getDepth(root);
    /* Calling current level function, by passing levels one by one. */
    printf("\n");
    for(int i = 1; i <= depth; i++)      
    {
        currentlevel(root,i);
        printf("\n");
    }
}

SplayTreeNode* inputFromFile(const char* filename){
	FILE* fptr=fopen(filename,"r");
	int num=0;
	SplayTreeNode* root=NULL;
	if(fptr==NULL){
		printf("Unable to open file");
		exit(0);
	}
	while(fscanf(fptr,"%d",&num)==1)
			root=insert(root,num);   
			
	return root;
}

void printTime(struct timespec startTime, struct timespec endTime,char* operation)
{
    double timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for %s is %lf microseconds\n",operation,timeTaken);
}


int main() {
    SplayTree tree;
    tree.root = NULL;
    struct timespec startTime,endTime;
    
    clock_gettime(CLOCK_MONOTONIC,&startTime);
	tree.root=inputFromFile("case10.txt");
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    printTime(startTime,endTime,"Insertion");

    
    clock_gettime(CLOCK_MONOTONIC,&startTime);
	tree.root = search(tree.root, 5);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    printTime(startTime,endTime,"searching");
    
    levelOrder(tree.root);
    clock_gettime(CLOCK_MONOTONIC,&startTime);
    tree.root = delete(tree.root, 20);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    printTime(startTime,endTime,"Deletion");
levelOrder(tree.root);
    clock_gettime(CLOCK_MONOTONIC,&startTime);
    inorder(tree.root);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    printTime(startTime,endTime,"Inorder Traversal");
    
    printf("\n");

    return 0;
}
