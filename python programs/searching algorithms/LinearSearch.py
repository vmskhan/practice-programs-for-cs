def linearSearch(arr,key):
	for i in range(len(arr)):
		if(arr[i]==key):
			print('Element '+str(key)+' found at position '+str(i+1))
			return
	print('Element '+str(key)+' is not present in the list')
	
if __name__=="__main__":
    numList=[1,6,34,87,54,123,86,23,8,0,10,5]
    print('Elements of the list are:')
    for i in numList:
        print(str(i)+" ",end=" ")
    print()
    linearSearch(numList,1)
    linearSearch(numList,10)
    linearSearch(numList,60)
    linearSearch(numList,123)
    linearSearch(numList,8)
    linearSearch(numList,34)
