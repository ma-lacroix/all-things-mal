# Trying out tkinter class

import time
import tkinter as tk
from tkinter import Button, ttk
from typing import Sized

class mainWindow(tk.Tk):
    
    def __init__(self,name):
        super().__init__()
        self.name = name
        self.geometry('300x300+50+50')
        self.title(self.name)
        self.columnconfigure(0,weight=1)
        self.columnconfigure(1,weight=1)
        self.columnconfigure(2,weight=1)
        self.columnconfigure(3,weight=1)
        self.rowconfigure(0,weight=1)
        self.rowconfigure(1,weight=1)
        self.rowconfigure(2,weight=1)
        self.rowconfigure(3,weight=1)
        self.setUpBoard()
        
        # self.line1 = tk.Label(self.window,text="first line")
        # self.line2 = tk.Label(self.window,text="second line")
    
    def getName(self):
        return self.name

    def setUpBoard(self):
        b_one = Button(self, text="1",width=5,height=5,highlightbackground='blue',highlightcolor='red')
        b_one.grid(column=0, row=0)
        b_two = Button(self, text="2",width=5,height=5)
        b_two.grid(column=1, row=0)
        b_three = Button(self, text="3",width=5,height=5)
        b_three.grid(column=2, row=0)
        b_four = Button(self, text="4",width=5,height=5)
        b_four.grid(column=0, row=1)
        b_five = Button(self, text="5",width=5,height=5)
        b_five.grid(column=1, row=1)
        b_six = Button(self, text="6",width=5,height=5)
        b_six.grid(column=2, row=1)
        b_seven = Button(self, text="7",width=5,height=5)
        b_seven.grid(column=0, row=2)
        b_eight = Button(self, text="8",width=5,height=5)
        b_eight.grid(column=1, row=2)
        b_nine = Button(self, text="9",width=5,height=5)
        b_nine.grid(column=2, row=2)
        b_plus = Button(self,text="+",width=5,height=5)
        b_plus.grid(column=3,row=0)
        b_minus = Button(self,text="-",width=5,height=5)
        b_minus.grid(column=3,row=1)
        b_divide = Button(self,text="/",width=5,height=5)
        b_divide.grid(column=3,row=2)
        b_multiply = Button(self,text="*",width=5,height=5)
        b_multiply.grid(column=3,row=3)

        # button
        button = Button(self, text="Run!",width=10,height=5)
        button.grid(column=1, row=3)

def main():
    newWindow = mainWindow("Calculator")
    print(f"Starting program {newWindow.getName()}")
    newWindow.mainloop()

if __name__=="__main__":
    main()
