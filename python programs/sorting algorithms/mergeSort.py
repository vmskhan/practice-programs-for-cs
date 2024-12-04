# have to work on it
def mergeSort(arr):
    temp=[]
    mid=(left+right)//2
    


def mergeElements(arr,left,mid,right):
    temp=[]
    i=left
    j=mid+1
    while(i<=mid and j<=right):
        if(arr[i]<=arr[j]):
            temp.append(arr[i])
            i=i+1
        else:
            temp.append(arr[j])
            j=j+1
    while(i<=mid):
        temp.append(arr[i])
        i=i+1
    while(j<=right):
        temp.append(arr[j])
        j=j+1
    
    arr[:]=arr[0:left]+temp+arr[right+1:]
    return arr

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    nums=mergeSort(nums,0,len(nums)-1)
    print(nums)