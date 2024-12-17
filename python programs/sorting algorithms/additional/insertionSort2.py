def insertionSort(arr):
    for i in range(1,len(arr)):
        temp=arr[i]
        j=i-1
        for j in range(i-1,-1,-1):
            if(arr[j]>temp):
                arr[j+1]=arr[j]
            else:
                break
        else:
            j=j-1
        arr[j+1]=temp
    return arr

if __name__=="__main__":
    nums=[6, 25, 3, 12, 15,5,24,4,13]
    nums=insertionSort(nums)
    print(nums)