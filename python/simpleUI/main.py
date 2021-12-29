# Trying out tkinter class

import tkinter as tk
from tkinter import ttk

class createButtons:
    def __init__(self,name,col,row) -> ttk.Button:
        self.button = ttk.Button(text=name,command=self.inputValue)
        self.name = name
        self.col = col
        self.row = row
     
    def addToBoard(self):
        self.button.grid(column=self.col,row=self.row,ipadx=1,ipady=1)
    
    def inputValue(self):
        print(self.name) 

class mainWindow(tk.Tk):
    
    def __init__(self,name) -> tk.Tk:
        super().__init__()
        self.style = ttk.Style(self)
        self.style.configure('TButton', font=('Helvetica', 10))
        self.name = name
        self.geometry('280x300+50+50')
        self.title(self.name)
        self.button_names= ["\n1\n","\n2\n","\n3\n","\n+\n",
                        "\n4\n","\n5\n","\n6\n","\n-\n",
                        "\n7\n","\n8\n","\n9\n","\n%\n",
                        "\n0\n","\nX\n","\n/\n","\n=\n"]
        self.equation = ""
        self.setUpBoard()
    
    def getName(self):
        return self.name

    def setUpBoard(self):
        i,j = 0,0
        for button in self.button_names:
            createButtons(button,i,j).addToBoard()
            if i%3==0 and i>0:
                i=0
                j+=1
            else:
                i+=1

def main():
    newWindow = mainWindow("Calculator")
    print(f"Starting program {newWindow.getName()}")
    newWindow.mainloop()

if __name__=="__main__":
    main()