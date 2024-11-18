class Node:
	def __init__(self,data):
		self.data=data
		self.next=None
		
class QueueLL:
	def __init__(self):
		self.front=None
		self.rear=None
		self.size=0
	
	def enqueue(self,ele):
		myNode=Node(ele)
		if(self.rear==None):
			self.rear=myNode
		else:
			self.rear.next=myNode
			self.rear=myNode
			
		if(self.front==None):
			self.front=self.rear
		self.size=self.size+1
		print("Element "+str(ele)+" has been added")

	def dequeue(self):
		if(self.front==None):
			print("Queue Underflow")
		else:
			myNode=self.front
			data=self.front.data
			self.front=self.front.next
			self.size=self.size-1
			if(self.front==None):
				self.rear=None
			del myNode
			print("Element "+str(data)+" has been removed")
			
	def displayElements(self):
		if(self.front==None):
			print("Queue is empty")
		else:
			current=self.front
			print("Elements of the queue are:")			
			while(current!=None):
				print((str(current.data)+"<-"),end=" ")
				current=current.next
			print()	
					
	def peek(self):
		if(self.front==None):
			print("Queue underflow")
		else:
			print("Front element of the Queue is:"+str(self.front.data))

	def getSize(self):
		print("Current size of Queue is:"+str(self.size))
		
if __name__=="__main__":
		myQueue=QueueLL()
		myQueue.enqueue(1)
		myQueue.enqueue(2)
		myQueue.enqueue(3)
		myQueue.enqueue(5)
		myQueue.enqueue(4)
		myQueue.displayElements()
		myQueue.getSize()
		myQueue.peek()
		myQueue.dequeue()
		myQueue.dequeue()
		myQueue.dequeue()
		myQueue.displayElements()
		myQueue.getSize()
		myQueue.peek()
		myQueue.dequeue()
		myQueue.dequeue()

		myQueue.dequeue()
		myQueue.displayElements()
		myQueue.getSize()

