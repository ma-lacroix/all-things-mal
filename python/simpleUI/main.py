# Trying out tkinter class

import tkinter as tk
from tkinter import ttk

class createButtons:
    def __init__(self,board,name) -> ttk.Button:
        self.button = ttk.Button(text="\n"+name+"\n",command=self.inputValue)
        self.board = board
        self.name = name
     
    def addToBoard(self,col,row):
        self.button.grid(column=col,row=row,ipadx=1,ipady=1)
    
    def inputValue(self):
        self.board.receiveChar(self.name) 

class mainWindow(tk.Tk):
    
    def __init__(self,name) -> tk.Tk:
        super().__init__()
        self.style = ttk.Style(self)
        self.style.configure('TButton', font=('Helvetica', 10))
        self.name = name
        self.geometry('280x300+50+50')
        self.title(self.name)
        self.button_names= [["1","2","3","+"],
                        ["4","5","6","-"],
                        ["7","8","9","%"],
                        ["0","X","/","="]]
        self.equation = ""
        self.setUpBoard()
    
    def getName(self):
        return self.name
    
    def receiveChar(self,char):
        self.equation = self.equation + char
        # add an evaluator self.evaluator
        print(self.equation)

    def setUpBoard(self):
        i,j = 0,0
        for i in range(0,4):
            for j in range(0,4):
                createButtons(self,self.button_names[i][j]).addToBoard(i,j)

def main():
    newWindow = mainWindow("Calculator")
    print(f"Starting program {newWindow.getName()}")
    newWindow.mainloop()

if __name__=="__main__":
    main()