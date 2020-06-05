import tkinter as tk
from tkinter import messagebox



file1=open("Sched1.txt","r")
file1a = open("Sched1a.txt", "r")
file2=open("Sched2.txt","r")
file2a = open("Sched2a.txt", "r")
file3=open("Sched3.txt","r")
file3a = open("Sched3a.txt", "r")
file4=open("Sched3.txt","r")
file4a = open("Sched4a.txt", "r")
file5=open("Sched3.txt","r")
file5a = open("Sched5a.txt", "r")


skies = 10

large_font= ("Verdana", 12)
normal_font = ("Helvetica", 10)
small_font = ("Helvetica", 8)

class Application(tk.Frame):
    def __init__(self, master=None):
        tk.Frame.__init__(self, master)
        self.pack()
        self.create_widgets()
        
        #ybar = Scrollbar1( self, orient='vertical', command=self.yview ) 

    def create_widgets(self):

        for x in range(1):
        	
        	self.Label = tk.Label(self)
        	

        	self.Label["text"] = file1a.read()
        	self.Label.pack(side="top")

        	self.Schedule = tk.Button(self)
        	self.Schedule["text"] = "Schedule " + str(x+1) + "\n(click here to open)"
        	self.Schedule["fg"] = "green"
        	self.Schedule["command"] = self.popup1
        	self.Schedule.pack(side="top")

        for x in range(1):
        	
        	self.Label = tk.Label(self)
        	

        	self.Label["text"] = file2a.read()
        	self.Label.pack(side="top")

        	self.Schedule = tk.Button(self)
        	self.Schedule["text"] = "Schedule " + str(x+2) + "\n(click here to open)"
        	self.Schedule["fg"] = "green"
        	self.Schedule["command"] = self.popup2
        	self.Schedule.pack(side="top")

        for x in range(1):
        	
        	self.Label = tk.Label(self)
        	

        	self.Label["text"] = file3a.read()
        	self.Label.pack(side="top")

        	self.Schedule = tk.Button(self)
        	self.Schedule["text"] = "Schedule " + str(x+3) + "\n(click here to open)"
        	self.Schedule["fg"] = "green"
        	self.Schedule["command"] = self.popup3
        	self.Schedule.pack(side="top")

        for x in range(1):
        	
        	self.Label = tk.Label(self)
        	

        	self.Label["text"] = file4a.read()
        	self.Label.pack(side="top")

        	self.Schedule = tk.Button(self)
        	self.Schedule["text"] = "Schedule " + str(x+4) + "\n(click here to open)"
        	self.Schedule["fg"] = "green"
        	self.Schedule["command"] = self.popup4
        	self.Schedule.pack(side="top")

        for x in range(1):
        	
        	self.Label = tk.Label(self)
        	

        	self.Label["text"] = file5a.read()
        	self.Label.pack(side="top")

        	self.Schedule = tk.Button(self)
        	self.Schedule["text"] = "Schedule " + str(x+5) + "\n(click here to open)"
        	self.Schedule["fg"] = "green"
        	self.Schedule["command"] = self.popup5
        	self.Schedule.pack(side="top")        	        	

        self.quitButton = tk.Button(self, text="QUIT", fg="red", command=self.quit)
        self.quitButton.pack(side="bottom")

    def popup1(msg):
    	messagebox.showinfo("Schedule", file1.read())


    def popup2(msg):
    	messagebox.showinfo("Schedule", file2.read())
    def popup3(msg):
    	messagebox.showinfo("Schedule", file3.read())
    def popup4(msg):
    	messagebox.showinfo("Schedule", file4.read())
    def popup5(msg):
    	messagebox.showinfo("Schedule", file5.read())
    
app = Application()
app.master.title('Sample application')
app.mainloop()

file1.close()
file1a.close()
file2.close()
file2a.close()
file3.close()
file3a.close()
file4.close()
file4a.close()
file5.close()
file5a.close()