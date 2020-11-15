# A parser which can read polish math notations
# Author: Marc-Antoine Lacroix
# WIP

def eval(obj,alist):
    x=0
    for element in obj:
        if(type(element) is list):
            eval(element,alist)
        else:
            x=element
            alist.append(x)
            print(x)
    return sum(alist)            

def main():
    # obj = ['+',['-',4,3],1]
    obj = [[1,2,3],[4,5,[6,7,8]]]
    l = []
    x = eval(obj,l)
    print(x)
    
if __name__ == "__main__":
    main()