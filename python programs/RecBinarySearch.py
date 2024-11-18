def binarySearch(arr,key,left,right):
	if(left>right):
		print('Element '+str(key)+' is not present in the list')
		return
	mid=(left+right)//2
	if(arr[mid]==key):
		print('Element '+str(key)+' found at position '+str(mid+1))
		return
	elif key<arr[mid]:
	    binarySearch(arr,key,left,mid-1)
	else:
	    binarySearch(arr,key,mid+1,right)
		
if __name__=="__main__":
    numList=[0,1,5,6,8,10,23,34,54,86,87,123]
    print('Elements of the list are:')
    for i in numList:
        print(str(i)+" ",end=" ")
    print()
    binarySearch(numList,1,0,len(numList))
    binarySearch(numList,10,0,len(numList))
    binarySearch(numList,60,0,len(numList))
    binarySearch(numList,123,0,len(numList))
    binarySearch(numList,8,0,len(numList))
    binarySearch(numList,34,0,len(numList))
