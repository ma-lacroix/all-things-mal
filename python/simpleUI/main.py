# Trying out tkinter class

import time
import tkinter as tk

class someWindow:
    
    def __init__(self,name):
        self.name = name
        self.window = tk.Tk()
        self.window.title(self.name)
        self.window.geometry('600x400+50+50')
        self.top = tk.Label(self.window,text="first line")
    
    def getName(self):
        return self.name

    def startLoop(self):
        self.top.pack()
        self.window.mainloop()

def main():
    newWindow = someWindow("First TK project")
    print(f"Starting program {newWindow.getName()}")
    newWindow.startLoop()

if __name__=="__main__":
    main()