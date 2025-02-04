class treeNode:
    def __init__(self):
        self.left=None
        self.right=None
        self.val=-1

def insertNode(root,ele,size):
    if(size==1):
        root.val=ele
    else:
        temp=treeNode()
        temp.val=ele
        path=[]
        prev=root
        while(size!=1):
            div=size%2
            path.append(div)
            size=size//2
        
        while(len(path)!=0):
            num=path.pop()
            prev=root
            if(num==1):
                root=root.right
            else:
                root=root.left
        if(num==1):
            prev.right=temp
        else:
            prev.left=temp



def createBinaryTree(elements):
    root=treeNode()
    size=1
    for ele in elements:
        insertNode(root,ele,size)
        size+=1
    return root


def preorder(root):
    if(root!=None):
        print(root.val,end=" ")
        preorder(root.left)
        preorder(root.right)

def inorder(root):
    if(root!=None):
        inorder(root.left)
        print(root.val,end=" ")
        inorder(root.right)

def postorder(root):
    if(root!=None):
        postorder(root.left)
        postorder(root.right)
        print(root.val,end=" ")

if __name__=="__main__":
    #elements=[2,56,76,12,97,34,4]
    # elements=[12,7,20,2,9,15,25] #levelorder bst elements 
    root=createBinaryTree(elements)
    print("\nPreorder Sequence of elements:",end=" ")
    preorder(root)
    print("\nInorder sequence of elements:",end=" ")
    inorder(root)
    print("\nPostorder sequence of elements:",end=" ")
    postorder(root)

#can insert elemetns in levelorder sequence of BST to check correctness