
class StackArr:
	def __init__(self,size):
		self.top=-1
		self.dataList=[]
		self.size=size
	
	def push(self,ele):
		
		if(self.top==self.size-1):
			print("Stack Overflow. Cannot push element "+str(ele)+" into stack")
		else:
			self.dataList.append(ele)
			self.top=self.top+1
			print("Element "+str(ele)+" has been pushed")
		

	def pop(self):
		if(self.top==-1):
			print("Stack Underflow. Cannot pop elements")
		else:
			self.top=self.top-1
			data=self.dataList.pop()
			print("Element "+str(data)+" has been popped")
			
	def displayElements(self):
		if(self.top==-1):
			print("Stack is empty")
		else:
			print("Elements of the stack are:")			
			for i in self.dataList:
				print((str(i)+" "),end=" ")
			print()			
			
	def peek(self):
		if(self.top==-1):
			print("stack underflow. Cannot perfrom peek() operation")
		else:
			print("Top of the stack is:"+str(self.dataList[self.top]))

	def getSize(self):
		print("Current size of stack is:"+str(len(self.dataList)))
		
if __name__=="__main__":
		myStack=StackArr(5)
		myStack.push(1)
		myStack.push(2)
		myStack.push(3)
		myStack.push(5)
		myStack.push(4)
		myStack.displayElements()
		myStack.getSize()
		myStack.peek()
		myStack.pop()
		myStack.pop()
		myStack.pop()
		myStack.displayElements()
		myStack.getSize()
		myStack.peek()
		myStack.pop()
		myStack.pop()

		myStack.pop()
		myStack.displayElements()
		myStack.getSize()

