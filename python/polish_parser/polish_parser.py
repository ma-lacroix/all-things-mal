# A parser which can read polish math notations
# Author: Marc-Antoine Lacroix
# WIP

def eval(obj,i):
    olen = len(obj)
    if(i>olen):
        return
    eval(obj,i+1)
    print(obj)

def main():
    # obj = ['+',['-',4,3],1]
    obj = [[1,2,3],[4,5,6],[7,8,[9,10,11]]]
    i = 0
    eval(obj,i)
    
if __name__ == "__main__":
    main()