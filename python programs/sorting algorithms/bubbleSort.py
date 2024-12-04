def bubbleSort(arr):
    for i in range(len(arr)-1):
        for j in range(len(arr)-1):
            if(arr[j]>arr[j+1]):
                arr[j],arr[j+1]=arr[j+1],arr[j]
    return arr

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    nums=bubbleSort(nums)
    print(nums)