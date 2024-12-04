def insertionSort(arr):
    for i in range(1,len(arr)):
        for j in range(i,0,-1):
            if(arr[j-1]>arr[j]):
                arr[j-1],arr[j]=arr[j],arr[j-1]
    return arr

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    nums=insertionSort(nums)
    print(nums)