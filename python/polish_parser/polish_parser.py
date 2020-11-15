# A parser which can read polish math notations
# Author: Marc-Antoine Lacroix
# WIP

def getSymbol(list1,list2):
    if(list1[0]=='-'):
        res = list2[0]-list2[1]
    elif(list1[0]=='+'):
        res = list2[0]+list2[1]
    elif(list1[0]=='/'):
        res = list2[0]/list2[1]
    elif(list1[0]=='*'):
        res = list2[0]*list2[1]
    return res

def eval(obj):
    alist = []
    if(type(obj[1]) is list):
        alist.append(eval(obj[1]))
    else:
        alist.append(obj[1])
    if(type(obj[2]) is list):
        alist.append(eval(obj[2]))
    else:
        alist.append(obj[2])
    return getSymbol(obj,alist)
    
def main():
    obj = ['-',['+',['-',['/',8,2],3],7],['+',2,['-',['*',2,2],1]]]
    res = eval(obj)
    print("Final result: {}".format(res))
    
if __name__ == "__main__":
    main()