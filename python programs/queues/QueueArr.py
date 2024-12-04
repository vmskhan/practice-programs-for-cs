class QueueArr:
	def __init__(self,size):
		self.front=0
		self.rear=0
		self.size=size
		self.dataList=[]
	
	def enqueue(self,ele):
		if(self.rear==self.size):
			print("Queue Overflow. Cannot add "+str(ele)+" to the queue")
		else:
			self.dataList.append(ele)
			self.rear=self.rear+1
			print("Element "+str(ele)+" has been added")
		

	def dequeue(self):
		if(self.front==self.rear):
			print("Queue Underflow. Cannot remove a element from empty stack")
		else:
			data=self.dataList.pop(0)
			self.rear=self.rear-1
			print("Element "+str(data)+" has been removed")
			
	def displayElements(self):
		if(self.front==self.rear):
			print("Queue is empty")
		else:
			print("Elements of the queue are:")			
			for i in self.dataList:
				print((str(i)+"<-"),end=" ")
			print()	
					
	def peek(self):
		if(self.front==self.rear):
			print("Queue underflow")
		else:
			print("Front element of the Queue is:"+str(self.dataList[self.front]))

	def getSize(self):
		print("Current size of Queue is:"+str(len(self.dataList)))
		
if __name__=="__main__":
		myQueue=QueueArr(5)
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

