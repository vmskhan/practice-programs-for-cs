def selectionSort(arr):
    for i in range(len(arr)-1):
        index=i
        for j in range(i+1,len(arr)):
            if(arr[j]<arr[index]):
                index=j
        arr[i],arr[index]=arr[index],arr[i]
    return arr

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    nums=selectionSort(nums)
    print(nums)