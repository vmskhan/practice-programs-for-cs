class HashTable:
    def __init__(self,size):
        self.size=size
        self.hashTable=[-1]*size
        self.collisionCount=0
        self.constant=getPrime(size)
    
    def getHash(self,key):
        return key%self.size
    
    def getStepSize(self,key):
        return self.constant-(key%self.constant)


    def insertKeyIntoTable(self,key):
        hashedVal=self.getHash(key)
        stepSize=self.getStepSize(key)
        count=0
        while(count!=self.size):
            count+=1
            if(self.hashTable[hashedVal]==-1):
                self.hashTable[hashedVal]=key
                break
            else:
                print(f"collision occurred for {key} at {hashedVal}")
                self.collisionCount+=1
            hashedVal=self.getHash(hashedVal+stepSize)
        if(count==self.size):
            print("Hash table is full")
    
    def insertKeys(self,keys):
        for key in keys:
            self.insertKeyIntoTable(key)
        print(f"\nCollsions-{self.collisionCount}")

    def displaytable(self):
        for i,x in enumerate(self.hashTable):
            print(str(i)+" - "+str(x))

def getPrime(size):
        for i in range(size-1,2,-1):
            if(isPrime(i)):
                return i
        return 2
    
def isPrime(i):
    for k in range(2,(i/2)+2):
        if(i%k==0):
            return False
    return True

if __name__=="__main__":
    size=11
    hashTable=HashTable(size)
    keys=[2,4,26,76,534,32,86,21]
    hashTable.insertKeys(keys)
    hashTable.displaytable()

    
        

