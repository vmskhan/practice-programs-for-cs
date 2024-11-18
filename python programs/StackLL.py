class Node:
	def __init__(self,data):
		self.data=data
		self.next=None
		

class StackLL:
	def __init__(self):
		self.top=None
		self.size=0
	
	def push(self,ele):
		myNode=Node(ele)
		if(self.top==None):
			self.top=myNode
		else:
			myNode.next=self.top
			self.top=myNode
		self.size=self.size+1
		print("Element "+str(ele)+" has been pushed")
	def pop(self):
		if(self.top==None):
			print("Stack Underflow")
		else:
			data=self.top.data
			myNode=self.top
			self.top=self.top.next
			self.size=self.size-1
			del myNode
			print("Element "+str(data)+" has been popped")
			
	def displayElements(self):
		if(self.top==None):
			print("Stack is empty")
		else:
			current=self.top
			print("Elements of the stack are:")			
			while(current!=None):
				print((str(current.data)+"<-"),end=" ")
				current=current.next
			print()			
	def peek(self):
		if(self.top==None):
			print("stack underflow")
		else:
			print("Top of the stack is:"+str(self.top.data))

	def getSize(self):
		print("Current size of stack is:"+str(self.size))
		
if __name__=="__main__":
		myStack=StackLL()
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

