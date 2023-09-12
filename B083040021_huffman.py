import tkinter as tk
from tkinter import Tk
import os


def run():
        command = "hw8-b083040021 -c -i "+ entry.get() + " -o "+ entry1.get()
        os.system(command)


def run1():
        command = "hw8-b083040021 -u -i "+ entry.get() + " -o "+ entry1.get()
        os.system(command)


win=tk.Tk()

win.title("B083040021 huffman")

win.geometry("600x230+250+150")

label = tk.Label(win, text = 'input file')
label.place(x = 275,y = 30)


entry = tk.Entry(win)
entry.place(x = 200,y = 50,width =200,
        height = 20)


label1 = tk.Label(win, text = 'output file')
label1.place(x = 270,y = 100)

entry1= tk.Entry(win)
entry1.place(x = 200,y = 120,width =200,
        height = 20)


button = tk.Button(win,          # 按鈕所在視窗
                   text = 'press',  # 顯示文字
                   command = run)
button.place(x = 315,y = 160,width =50,
        height = 30)

button1 = tk.Button(win,          # 按鈕所在視窗
                   text = 'unpress',  # 顯示文字
                   command = run1)
button1.place(x = 230,y = 160,width =50,
        height = 30)

win.mainloop()