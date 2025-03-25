class HashTable:
    def __init__(self,size):
        self.size=size
        self.hashTable=[-1]*size
        self.collisionCount=0


    def getHash(self,key):
        return key%self.size

    def insertKeyIntoTable(self,key):
        hashedVal=self.getHash(key)
        count=0
        while(count!=self.size):
            newVal=self.getHash(hashedVal+count**2)
            count+=1
            if(self.hashTable[newVal]==-1):
                self.hashTable[newVal]=key
                break
            else:
                print(f"collision occurred for {key} at {newVal}")
                self.collisionCount+=1
        if(count==self.size):
            print("Hash table is full")
    
    def insertKeys(self,keys):
        for key in keys:
            self.insertKeyIntoTable(key)
        print(f"\nCollsions-{self.collisionCount}")

    def displaytable(self):
        for i,x in enumerate(self.hashTable):
            print(str(i)+" - "+str(x))

if __name__=="__main__":
    size=11
    hashTable=HashTable(size)
    keys=[2,4,26,76,534,32,86,21]
    hashTable.insertKeys(keys)
    hashTable.displaytable()

    
        

