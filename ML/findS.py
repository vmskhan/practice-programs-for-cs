def find_s(trdata):
    #step 1 initialization
    hypothesis=["0"]*len(attributes)
    for example in trdata:
        label=example[-1]
        if(label=="Positive"):
            for i in range(len(attributes)):
                # if(hypothesis[i]=="?"):
                #     continue
                if(hypothesis[i]=="0"):
                    hypothesis[i]=example[i]
                
                elif(hypothesis[i]!=example[i]):
                    hypothesis[i]="?"
                # else:
                #     pass
    return hypothesis
if __name__=="__main__":
    attributes=["colour","shape","size"]
    trdata=[
        ["Red","Large","Round","Positive"],
        ["Red","Small","Round","Negative"],
        ["Red","Large","Square","Positive"],
        ["Blue","Large","Square","Positive"],
    ]
    final_hypothesis=find_s(trdata)
    print("Final_hypothesis",final_hypothesis)