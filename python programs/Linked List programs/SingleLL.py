class Node:
	def __init__(self,data):
		self.data=data
		self.next=None
		
class SingleLL:
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
		self.size=self.size+1
		print("Element "+str(ele)+" has been added")

	def remove(self,key):
		if(self.head==None):
			print("List is empty.Cannot perform remove operation")
		else:
		
			if(self.head.data==key):
				temp=self.head
				self.head=self.head.next
				del temp
				self.size=self.size-1					
				print("Element "+str(key)+" has been removed")
			else:	
				prev=self.head
				curr=self.head.next
				while(curr!=None):
					if(curr.data==key):
						prev.next=curr.next
						break						
					prev=curr
					curr=curr.next

				if(curr==None):
					print("Element "+str(key)+" is not present in the list")
				else:
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
				print((str(current.data)+"<-"),end=" ")
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
		myList=SingleLL()
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

