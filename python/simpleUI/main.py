# Trying out tkinter class

import tkinter as tk
from tkinter import Button, Label, ttk

class calculator:
    
    def __init__(self):
        self.num1 = ""
        self.num2 = ""
        self.operator = ""

    def split(self,aString):
        return [c for c in aString]

    def parseEquation(self,equation):
        for e in equation: # TODO deal with this flow control better
            if e == "=" and (self.num1=="" or self.num2==""):
                print("error")
                self.num1 = ""
                self.num2 = ""
                return ""
            elif e == '=' and self.num1 != "" and self.num2 != "":
                self.getResults()
            elif e in self.split("+-/X%"):
                self.operator = e
                self.num1 = equation.split(e)[0]
                self.num2 = equation.split(e)[1].replace("=","") # TODO deal with the equals symbol better
                return f"{self.num1} {self.operator} {self.num2}"
            else:
                # self.num1 = equation
                # return f"{self.num1}"
                pass
    
    def getResult(self):
        if self.operator == "+":
            return str(self.num1 + self.num2)
        elif self.operator == "-":
            return str(self.num1 - self.num2)
        elif self.operator == "X":
            return str(self.num1 * self.num2)
        elif self.operator == "/":
            return str(self.num1 / self.num2)
        elif self.operator == "%":
            return str(self.num1 % self.num2)
        else:
            return ""

class createButtons:

    def __init__(self,board,name) -> ttk.Button:
        self.button = ttk.Button(text="\n"+name+"\n",command=self.inputValue)
        self.board = board
        self.name = name
     
    def addToBoard(self,col,row):
        self.button.grid(column=col,row=row+10,ipadx=1,ipady=1)
    
    def inputValue(self):
        self.board.receiveChar(self.name) 

class mainWindow(tk.Tk):
    
    def __init__(self,name) -> tk.Tk:
        super().__init__()
        self.calculator = calculator()
        self.style = ttk.Style(self)
        self.style.configure('TButton', font=('Helvetica', 10))
        self.style.configure('TLabel', font=('Courier New', 20))
        self.name = name
        self.geometry('280x300+50+50')
        self.title(self.name)
        self.button_names= [["1","2","3","+"],
                        ["4","5","6","-"],
                        ["7","8","9","%"],
                        ["0","X","/","="]]
        self.equation = ""
        self.answer = ""
        self.setUpBoard()
    
    def getName(self):
        return self.name
    
    def receiveChar(self,char):
        self.equation = self.equation + char
        # TODO add an evaluator
        self.answer = self.calculator.parseEquation(self.equation)
        eq = ttk.Label(text=self.answer)
        eq.grid(column=1,row=0,columnspan=2,rowspan=2)


    def setUpBoard(self):
        self.receiveChar("") # initialize the screen
        for i in range(0,4):
            for j in range(0,4):
                createButtons(self,self.button_names[i][j]).addToBoard(j,i)

def main():
    newWindow = mainWindow("Calculator")
    print(f"Starting program {newWindow.getName()}")
    newWindow.mainloop()

if __name__=="__main__":
    main()