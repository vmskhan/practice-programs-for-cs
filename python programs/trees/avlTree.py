class treeNode:
    def __init__(self,val):
        self.left=None
        self.right=None
        self.val=val
        self.height=1

def leftRotate(x):
    y=x.right
    x.right=y.left
    y.left=x
    return y

def rightRotate(x):
    y=x.left
    x.left=y.right
    y.right=x
    return y

def getNodeHeight(x):
    return x.height if(x!=None) else 0

def getBalanceFactor(x):
    leftHeight=getNodeHeight(x.left)
    rightHeight=getNodeHeight(x.right)
    return leftHeight-rightHeight


def search(root,ele):
    if(root==None):
        print(f"Key Element {ele} not found. Search Unsuccessful")
    elif(root.val==ele):
        print(f"Key Element {ele} found. Search Successful")
    elif(ele<root.val):
        search(root.left,ele)
    else:             
        search(root.right,ele)

def insert(root,ele):
    if(root==None):
        return treeNode(ele)
    elif(ele<root.val):
        root.left=insert(root.left,ele)
    else:             
        root.right=insert(root.right,ele)
    
    root.height=1+max(getNodeHeight(root.left),getNodeHeight(root.right))
    bf=getBalanceFactor(root)
    if(bf>1): 
        if(ele>root.left.val): #LR
            root.left=leftRotate(root.left)
        root=rightRotate(root)  #LL

    elif(bf<-1):
        if(ele<root.right.val): #RL
            root.right=rightRotate(root.right)
        root=leftRotate(root)  #RR
    return root

def deleteNode(root,ele):
        if(root==None):
            print(f"\nElement {ele} not found. Delete unsuccessful")
            return None
        elif(root.val==ele):
            if(root.right==None or root.left==None):
                temp=root.right if (root.left==None) else root.left
                del root
                print(f"\nKey Element found. Delete successful")
                return temp
            else:
                root.val=minValue(root.right)
                root.right=deleteNode(root.right,root.val) 
        elif(ele<root.val):
            root.left=deleteNode(root.left,ele)
        else:             
            root.right=deleteNode(root.right,ele)

        root.height=1+max(getNodeHeight(root.left),getNodeHeight(root.right))
        bf=getBalanceFactor(root)
        if(bf>1): 
            if(getBalanceFactor(root.left)<0): #LR
                root.left=leftRotate(root.left)
            root=rightRotate(root)  #LL

        elif(bf<-1):
            if(getBalanceFactor(root.right)>=0): #RL
                root.right=rightRotate(root.right)
            root=leftRotate(root)  #RR

        return root

def minValue(root):
    if(root.left==None):
        return root.val
    else:
        minValue(root.left)

def inorder(root):
    if(root!=None):
        inorder(root.left)
        print(root.val,end=" ")
        inorder(root.right)

def levelOrder(root):
    depth=getDepth(root)
    for i in range(0,depth):
        getElementsOfLevel(root,i)
        print()

def getElementsOfLevel(root,level):
    if(root!=None):
        if(level==0):
            print(root.val,end=" ")
        else:
            getElementsOfLevel(root.left,level-1)
            getElementsOfLevel(root.right,level-1)
    elif(level==0):
        print("N",end=" ")

def getDepth(root):
    if(root==None):
        return 0
    else:
        return 1+max(getDepth(root.left),getDepth(root.right))


if __name__=="__main__":
    elements=[2,56,76,12,97,34,4]
    key=56
    root=None
    # elements=[12,7,20,2,9,15,25] #levelorder bst elements 
    for i in elements:
        root=insert(root,i)
    print("\nInorder sequence of elements:",end=" ")
    inorder(root)
    # print("\nAVL tree elements:")
    # levelOrder(root)
    print()
    search(root,key)
    root=deleteNode(root,key)
    # print("\nInorder sequence of elements:",end=" ")
    # inorder(root)
    # print("\nAVL tree elements:")
    # levelOrder(root)