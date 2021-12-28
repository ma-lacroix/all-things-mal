# Trying out tkinter class

import tkinter as tk
from tkinter import ttk

class createButtons:
    def __init__(self,name,col,row) -> None:
        self.button = ttk.Button(text=name)
        self.col = col
        self.row = row
    
    def addToBoard(self):
        self.button.grid(column=self.col,row=self.row)

class mainWindow(tk.Tk):
    
    def __init__(self,name):
        super().__init__()
        self.style = ttk.Style(self)
        self.style.configure('TButton', font=('Helvetica', 10))
        self.name = name
        self.geometry('300x300+50+50')
        self.title(self.name)
        self.setUpBoard()
    
    def getName(self):
        return self.name

    def setUpBoard(self):
        button_names= ["\n1\n","\n2\n","\n3\n",
                        "\n4\n","\n5\n","\n6\n",
                        "\n7\n","\n8\n","\n9\n",
                        "\n0\n"]
        i,j = 0,0
        for button in button_names:
            createButtons(button,i,j).addToBoard()
            if i%2==0 and i>0:
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