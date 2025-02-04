class treeNode:
    def __init__(self,val):
        self.left=None
        self.right=None
        self.val=val

    
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
    # print("\nBST tree elements:")
    # levelOrder(root)
    print()
    search(root,key)
    deleteNode(root,key)
    # print("\nInorder sequence of elements:",end=" ")
    # inorder(root)
    # print("\nBST tree elements:")
    # levelOrder(root)