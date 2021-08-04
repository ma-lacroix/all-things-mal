import ctypes
import os

def compile(libName,sourceFile):
    os.system("g++ --std=c++17 -shared -Wl,-install_name,{n}.so -o {n}.so -fPIC {s}.cpp".format(n=libName,s=sourceFile))

def main():
    
    # create c++ shared library
    libName = 'demo'
    sourceFile = 'main'
    compile(libName,sourceFile)
    
    # run both c++ functions
    cpp_lib = ctypes.CDLL('{n}.so'.format(n=libName))
    cpp_lib.printMsg()
    cpp_lib.printSum(30,20)


if __name__ == "__main__":
    main()

