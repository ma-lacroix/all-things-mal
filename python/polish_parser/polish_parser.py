# A parser which can read polish math notations
# Author: Marc-Antoine Lacroix
# WIP

def useSymbol(symbol,alist):
    if(symbol=='-'):
        res = alist[0]-alist[1]
    elif(symbol=='+'):
        res = alist[0]+alist[1]
    elif(symbol=='/'):
        res = alist[0]/alist[1]
    elif(symbol=='*'):
        res = alist[0]*alist[1]
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
    return useSymbol(obj[0],alist)
    
def main():
    obj = ['-',['+',['-',['/',8,2],3],7],['+',2,['-',['*',2,2],1]]]
    res = eval(obj)
    print("Final result: {}".format(res))
    
if __name__ == "__main__":
    main()