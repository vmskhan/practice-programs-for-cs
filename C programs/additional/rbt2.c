//nmc code
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct node {
    int d; 
    int c; // 1-red, 0-black
    struct node* p; 
    struct node* r; 
    struct node* l; 
};

struct node* root = NULL;
 
struct node* createNode(int ele){
    struct node* temp
            = (struct node*)malloc(sizeof(struct node));
        temp->r = NULL;
        temp->l = NULL;
        temp->p = NULL;
        temp->d = ele;
        temp->c = 1;
    return temp;
}
// function to perform BST insertion of a node
struct node* bst(struct node* trav, 
                      struct node* temp)
{
    // If the tree is empty, 
    // return a new node
    if (trav == NULL)
        return temp;
 
  
    if (temp->d < trav->d) 
    {
        trav->l = bst(trav->l, temp);
        trav->l->p = trav;
    }
    else if (temp->d > trav->d) 
    {
        trav->r = bst(trav->r, temp);
        trav->r->p = trav;
    }
 
    
    return trav;
}
 

void rightrotate(struct node* temp)
{
    struct node* left = temp->l;
    temp->l = left->r;
    if (temp->l)
        temp->l->p = temp;
    left->p = temp->p;
    if (!temp->p)
        root = left;
    else if (temp == temp->p->l)
        temp->p->l = left;
    else
        temp->p->r = left;
    left->r = temp;
    temp->p = left;
}
 

void leftrotate(struct node* temp)
{
    struct node* right = temp->r;
    temp->r = right->l;
    if (temp->r)
        temp->r->p = temp;
    right->p = temp->p;
    if (!temp->p)
        root = right;
    else if (temp == temp->p->l)
        temp->p->l = right;
    else
        temp->p->r = right;
    right->l = temp;
    temp->p = right;
}
 

void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;
 
    while ((pt != root) && (pt->c != 0)
           && (pt->p->c == 1)) 
    {
        parent_pt = pt->p;
        grand_parent_pt = pt->p->p;
 
        /*  Case : A
             Parent of pt is left child 
             of Grand-parent of
           pt */
        if (parent_pt == grand_parent_pt->l) 
        {
 
            struct node* uncle_pt = grand_parent_pt->r;
 
            /* Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if (uncle_pt != NULL && uncle_pt->c == 1) 
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
 
            else {
 
                /* Case : 2
                     pt is right child of its parent
                     Left-rotation required */
                if (pt == parent_pt->r) {
                    leftrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                     pt is left child of its parent
                     Right-rotation required */
                rightrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
 
        /* Case : B
             Parent of pt is right 
             child of Grand-parent of
           pt */
        else {
            struct node* uncle_pt = grand_parent_pt->l;
 
            /*  Case : 1
                The uncle of pt is also red
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->c == 1)) 
            {
                grand_parent_pt->c = 1;
                parent_pt->c = 0;
                uncle_pt->c = 0;
                pt = grand_parent_pt;
            }
            else {
                /* Case : 2
                   pt is left child of its parent
                   Right-rotation required */
                if (pt == parent_pt->l) {
                    rightrotate(parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->p;
                }
 
                /* Case : 3
                     pt is right child of its parent
                     Left-rotation required */
                leftrotate(grand_parent_pt);
                int t = parent_pt->c;
                parent_pt->c = grand_parent_pt->c;
                grand_parent_pt->c = t;
                pt = parent_pt;
            }
        }
    }
}
 
void search(struct node* rootNode,int key){
	if(root==NULL)
		printf("Key %d is not present in tree\n",key);
	else if(rootNode->d==key)
		printf("Key %d has been found\n",key);
	else if(key<rootNode->d)
		search(rootNode->l,key);
	else
		search(rootNode->r,key);
}

void inorder(struct node* trav)
{
    if (trav == NULL)
        return;
    inorder(trav->l);
    printf("%d ", trav->d);
    inorder(trav->r);
}
 
void inputFromFile(const char* filename){
	FILE* fptr=fopen(filename,"r");
	int num=0;
	if(fptr==NULL){
		printf("Unable to open file");
		exit(0);
	}
	while(fscanf(fptr,"%d",&num)==1){
		struct node* temp=createNode(num);
        root = bst(root, temp);
        fixup(root, temp);
        root->c = 0;
	}
}



int getDepth(struct node* root)
{
  if(root==NULL)
    return 0;
  int left=getDepth(root->l);
  int right=getDepth(root->r);
  return 1+(left>right?left:right);
}

void currentlevel(struct node* root, int level)
{
    if (root != NULL) 
    {
        if (level == 1)
        {
            printf("%d", root->d);
            if(root->c)
              printf("R ");
            else
              printf("B ");
        }
        else if (level > 1) 
        { 
            currentlevel(root->l, level-1); 
            currentlevel(root->r, level-1);
        }			
    }
    else{
      printf("Nl ");
    }
}

void levelOrder(struct node* root){
  
   int depth=getDepth(root);
    /* Calling current level function, by passing levels one by one. */
    printf("\n");
    for(int i = 1; i <= depth; i++)      
    {
        currentlevel(root,i);
        printf("\n");
    }
}

// driver code
int main()
{
    struct timespec startTime,endTime;
	double timeTaken;

	clock_gettime(CLOCK_MONOTONIC,&startTime);
    inputFromFile("case40.txt");
    clock_gettime(CLOCK_MONOTONIC,&endTime);
    
    timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inserting is %lf microseconds\n",timeTaken);
 
 
    printf("Inorder sequence of the tree\n");

    clock_gettime(CLOCK_MONOTONIC,&startTime);
    inorder(root);
    clock_gettime(CLOCK_MONOTONIC,&endTime);

    timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for inorder traversal is %lf microseconds\n",timeTaken);
    levelOrder(root);
    clock_gettime(CLOCK_MONOTONIC,&startTime);
	search(root,60);
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	
	timeTaken=(endTime.tv_sec-startTime.tv_sec)*1e6+(endTime.tv_nsec-startTime.tv_nsec)/1e3;
	printf("\nTime taken for searching is %lf microseconds\n",timeTaken);
 
    return 0;
}