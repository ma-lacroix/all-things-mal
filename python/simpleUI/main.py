# Trying out tkinter class

import time
import tkinter

class someClass:
    def __init__(self,name):
        self.name = name

    def getName(self):
        return self.name

def main():
    marc = someClass("M-A")
    print(f"Hello world {marc.getName()}")

if __name__=="__main__":
    main()