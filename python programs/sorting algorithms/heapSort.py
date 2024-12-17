#try heapsort on a tree and heapsort using min-heap
def heapSort(arr):
    n=len(arr)
    start=n//2-1
    for i in range(start,-1,-1):
        heapify(arr,n,i)

    for i in range(n-1,0,-1):
        arr[0],arr[i]=arr[i],arr[0]
        heapify(arr,i,0)

def heapify(arr,n,i):
    largest=i
    leftChild=2*i+1
    rightChild=2*i+2
    if(leftChild<n and arr[leftChild]>arr[largest]):
        largest=leftChild
    if(rightChild<n and arr[rightChild]>arr[largest]):
        largest=rightChild

    if(largest!=i):   
        arr[largest],arr[i]=arr[i],arr[largest]
        heapify(arr,n,largest)

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    heapSort(nums)
    print(nums)