class Node:
	def __init__(self,data):
		self.data=data
		self.next=None
		self.prev=None
		
class DoubleLL:
	def __init__(self):
		self.head=None
		self.size=0
	
	def add(self,ele):
		myNode=Node(ele)
		if(self.head==None):
			self.head=myNode
		else:
			curr=self.head
			while(curr.next!=None):
				curr=curr.next
			curr.next=myNode
			myNode.prev=curr
		self.size=self.size+1
		print("Element "+str(ele)+" has been added")

	def remove(self,key):
		if(self.head==None):
			print("List is empty.Cannot perform remove operation")
		else:
		
			if(self.head.data==key):
				temp=self.head
				self.head=self.head.next
				self.head.prev=None
				del temp
				self.size=self.size-1					
				print("Element "+str(key)+" has been removed")
			else:	
			
				curr=self.head.next
				while(curr!=None):
					if(curr.data==key):
						break						
					curr=curr.next

				if(curr==None):
					print("Element "+str(key)+" is not present in the list")
				elif(curr.next==None):
					curr.prev.next=None
					del curr
					self.size=self.size-1					
					print("Element "+str(key)+" has been removed")
				else:
					curr.prev.next=curr.next
					curr.next.prev=curr.prev
					del curr
					self.size=self.size-1					
					print("Element "+str(key)+" has been removed")
				
			
	def displayElements(self):
		if(self.head==None):
			print("Linked List is empty")
		else:
			current=self.head
			print("Elements of the Linked List are:")			
			while(current!=None):
				print((str(current.data)+"<->"),end=" ")
				current=current.next
			print()	
					
	def peek(self):
		if(self.head==None):
			print("List is empty")
		else:
			print("Head element of the List is:"+str(self.head.data))

	def getSize(self):
		print("Current size of Linked List is:"+str(self.size))
		
if __name__=="__main__":
		myList=DoubleLL()
		myList.add(1)
		myList.add(2)
		myList.add(3)
		myList.add(5)
		myList.add(4)
		myList.displayElements()
		myList.getSize()
		myList.peek()
		myList.remove(3)
		myList.displayElements()
		myList.remove(1)
		myList.displayElements()
		myList.remove(4)
		myList.displayElements()
		myList.getSize()
		myList.peek()
		myList.remove(1)
		myList.remove(10)

		myList.remove(14)
		myList.displayElements()
		myList.getSize()

