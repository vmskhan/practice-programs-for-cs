def quickSort(arr,left,right):
    if(left<right):
        partitionIndex=partition(arr,left,right)
        quickSort(arr,left,partitionIndex-1)
        quickSort(arr,partitionIndex+1,right)    

def partition(arr,left,right):
    pivot=arr[left]
    i=left
    for j in range(left+1,right+1):
        if(arr[j]<pivot):
            i=i+1
            arr[i],arr[j]=arr[j],arr[i]
            
    arr[left]=arr[i]
    arr[i]=pivot
    return i

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    quickSort(nums,0,len(nums)-1)
    print(nums)