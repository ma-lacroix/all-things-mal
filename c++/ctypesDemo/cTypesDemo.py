import ctypes
import os
import datetime

def compile(libName,sourceFile):
    os.system("g++ --std=c++17 -shared -Wl,-install_name,{n}.so -o {n}.so -fPIC {s}.cpp".format(n=libName,s=sourceFile))

def printSum(loops,numA,numB):
    i = 0
    result = 0
    while(i < loops):
        result += numA+numB
        i+=1
    print("     The result is: {}".format(result))

def main():
    
    # create c++ shared library
    libName = 'demo'
    sourceFile = 'main'
    compile(libName,sourceFile)
    
    # list of experiments
    nums = [1,10,100,1000,10000,1000000,10000000,100000000,1000000000,10000000000]
    cpp_lib = ctypes.CDLL('{n}.so'.format(n=libName))
    cpp_lib.printMsg()

    for num in nums:
        print("Running for {}:\n".format(num))
        # run both c++ functions
        start = datetime.datetime.now()    
        cpp_lib.printSum(num,30,20)
        check1 = datetime.datetime.now()
        datetime.timedelta()
        cppRun = abs(check1-start).total_seconds()
        print("     c++ run time (sec): {}\n".format(cppRun))

        # run Python code
        printSum(num,30,20)
        check2 = datetime.datetime.now()
        pythonRun = abs(check2-check1).total_seconds()
        print("     Python run time (sec): {}\n".format(pythonRun))

if __name__ == "__main__":
    main()