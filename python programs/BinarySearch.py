def binarySearch(arr,key):
	left=0
	right=len(arr)-1
	while left<=right:
		mid=(left+right)//2
		if(arr[mid]==key):
			print('Element '+str(key)+' found at position '+str(mid+1))
			return
		elif key<arr[mid]:
			right=mid-1
		else:
			left=mid+1
	print('Element '+str(key)+' is not present in the list')
	
if __name__=="__main__":
    numList=[0,1,5,6,8,10,23,34,54,86,87,123]
    print('Elements of the list are:')
    for i in numList:
        print(str(i)+" ",end=" ")
    print()
    binarySearch(numList,1)
    binarySearch(numList,10)
    binarySearch(numList,60)
    binarySearch(numList,123)
    binarySearch(numList,8)
    binarySearch(numList,34)
