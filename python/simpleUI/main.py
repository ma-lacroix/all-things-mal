# Trying out tkinter class

import tkinter as tk
from tkinter import Button, Label, ttk

class calculator:

    """Just the math logic post-button click"""

    def __init__(self):
        self.num1 = ""
        self.num2 = ""
        self.operator = ""

    def split(self,aString):
        return [c for c in aString]

    def parseEquation(self,newChar):
        if newChar in self.split("X/%-+"):
            self.operator = newChar
            return f"{self.num1} {self.operator}"
        elif newChar == "=":
            return self.getResult()
        elif self.operator == "":
            self.num1+=newChar
            return f"{self.num1}"
        elif self.operator != "":
            self.num2+=newChar
            return f"{self.num1} {self.operator} {self.num2}"

    def getResult(self):
        n1 = int(self.num1)
        n2 = int(self.num2)
        if self.operator == "+":
            r = n1 + n2
        elif self.operator == "-":
            r = n1 - n2
        elif self.operator == "X":
            r = n1 * n2
        elif self.operator == "/":
            r = n1 / n2
        elif self.operator == "%":
            r = n1 % n2
        return f"{r}"  

    def resetCalc(self):
        self.num1 = ""
        self.num2 = ""
        self.operator = ""
        return f""

class createButtons:
    
    """Used to handle the calculator buttons & functions"""

    def __init__(self,board,name) -> ttk.Button:
        self.button = ttk.Button(text="\n"+name+"\n",command=self.inputValue)
        self.board = board
        self.name = name
     
    def addToBoard(self,col,row):
        self.button.grid(column=col,row=row+10,ipadx=1,ipady=1)
    
    def inputValue(self):
        self.board.receiveChar(self.name) 

class mainWindow(tk.Tk):

    """Main window container"""
    
    def __init__(self,name) -> tk.Tk:
        super().__init__()
        self.calculator = calculator()
        self.style = ttk.Style(self)
        self.style.configure('TButton', font=('Helvetica', 10))
        self.style.configure('TLabel', font=('Courier New', 20))
        self.name = name
        self.geometry('280x230+50+50')
        self.title(self.name)
        self.button_names= [["1","2","3","+"],
                        ["4","5","6","-"],
                        ["7","8","9","%"],
                        ["0","X","/","="]]
        self.equation = ""
        self.topBar = ttk.Label(text=self.equation)
        self.setUpBoard()
    
    def getName(self):
        return self.name

    def resetCalc(self):
        self.equation = self.calculator.resetCalc()
        self.topBar.destroy()
        self.topBar = ttk.Label(text=self.equation)
        self.topBar.grid(column=1,row=0,columnspan=2,rowspan=2)

    def receiveChar(self,newChar):
        self.equation = self.calculator.parseEquation(newChar)
        self.topBar.destroy()
        self.topBar = ttk.Label(text=self.equation)
        self.topBar.grid(column=1,row=0,columnspan=2,rowspan=2)


    def setUpBoard(self):
        self.receiveChar("") # initialize the screen
        for i in range(0,4):
            for j in range(0,4):
                createButtons(self,self.button_names[i][j]).addToBoard(j,i)
        ceButton = ttk.Button(text="\nRESET\n",command=self.resetCalc)
        ceButton.grid(column=0,row=20)

def main():
    newWindow = mainWindow("Calculator")
    print(f"Starting program {newWindow.getName()}")
    newWindow.mainloop()

if __name__=="__main__":
    main()