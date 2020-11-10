# A parser which can read polish math notations
# Author: Marc-Antoine Lacroix
# WIP

def openBrackets(obj):
# looks for positions of open brackets
    i = 0
    open = []
    for element in obj:
        i+=1
        if(element == '{'):
            open.append(i)
    return open                    

def closedBrackets(obj):
# looks for positions of open brackets
    i = 0
    closed = []
    for element in obj:
        i+=1
        if(element == '}'):
            closed.append(i)
    return closed[::-1]                    

def eval(obj):
# 1.maps the inner and outer positions of brackets in the object
# 2.extracts the math symbol next to the inner object and stores it into a temp object
# 3.performs the operation using the next 2 numbers for first iteration, stores into a temp number
# 4.repeats steps 2 and 3 but using the temp number from step 3
    bracPos = list(zip(openBrackets(obj),closedBrackets(obj)))
    return bracPos

def main():
    obj = list('{"*",{"+",4,5},7}') # polish notation example, the list will allow us to map character positions
    bracPos = eval(obj)
    print(bracPos)

if __name__ == "__main__":
    main()