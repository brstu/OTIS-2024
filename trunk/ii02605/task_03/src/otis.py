from tkinter import messagebox, Canvas, Label, Entry, Button, Tk
from tkinter.colorchooser import askcolor
import numpy as np
from numpy import sqrt
import networkx as nx

window_size = "190x120+1050+260"
font_type = "Arial"

# Eulerian path function
def find_eulerian_path():
    display("Eulerian Path Found", nx.algorithms.eulerian_path(graph))

# Circle creation
def create_circle(a, b, c, **kwargs):
    return canvas.create_oval(a - c, b - c, a + c, b + c, **kwargs)

# Line creation
def create_line(a1, b1, a2, b2):
    con = sqrt((a2 - b1) ** 2 + (b2 - b1) ** 2)
    a = a2 - a1
    b = b2 - b1
    da = (con - 20) * a / con
    db = (con - 20) * b / con
    return a2 - da, b2 - db, a1 + da, b1 + db

# Vertex creation
def add_vertex_to_graph(entname, window):
    names = entname.get()
    nodes.append(Vertex(names))
    window.destroy()

# Vertex class
class Vertex:
    def __init__(self, names):
        self.names = names
        rng = np.random.default_rng(50)
        self.a = rng.integers(0, 700)
        self.b = rng.integers(0, 800)

        self.circle = create_circle(self.a, self.b, 20, fill=color_vertex)
        self.text = canvas.create_text(self.a, self.b, anchor='center', text=names, font="Arial 10", fill="black")
        graph.add_node(names)
    
    def move(self, a, b):
        self.a = a
        self.b = b
        canvas.coords(self.circle, a - 20, b - 20, a + 20, b + 20)
        canvas.coords(self.text, a, b)
        for edge in edges:
            if edge.start == self or edge.end == self:
                edge.move()

    def edit_name(self):
        win = Tk()
        win.title("Edit Name")
        win.geometry(window_size)
        win.wm_attributes('-topmost', 3)
        win.resizable(False, False)
        lab = Label(win, text="Enter new name")
        lab.place(x=10, y=10)
        entry = Entry(win, width=10)
        entry.place(x=10, y=40)
        button = Button(win, text="Change", command=lambda: self.change_name(entry.get()))
        button.place(x=10, y=70)
        win.mainloop()

    def change_name(self, new_name):
        graph._adj[new_name] = graph._adj.pop(self.names)
        self.names = new_name
        canvas.itemconfig(self.text, text=new_name)

    def change_color(self, color):
        canvas.itemconfig(self.circle, fill=color)

    def remove(self):
        canvas.delete(self.circle)
        canvas.delete(self.text)
        for edge in edges:
            if edge.start == self or edge.end == self:
                edge.remove()
                edges.remove(edge)
        graph.remove_node(self.names)

# Edge class
class Edge:
    def __init__(self, start, end, weight):
        self.weight = weight
        self.start = start
        self.end = end
        self.line = canvas.create_line(create_line(self.start.a, self.start.b, self.end.a, self.end.b), width=2, fill="black")
        self.text = canvas.create_text((start.a + end.a) / 2, (start.b + end.b) / 2 - 5, anchor='center', text=self.weight, font="Arial 20", fill="white")
        graph.add_edge(start.names, end.names, weight=weight)

    def edit_weight(self):
        win = Tk()
        win.title("Edit Edge Weight")
        win.geometry(window_size)
        win.wm_attributes('-topmost', 3)
        win.resizable(False, False)
        lab = Label(win, text="Enter new weight")
        lab.place(x=10, y=10)
        entry = Entry(win, width=10)
        entry.place(x=10, y=40)
        button = Button(win, text="Change", command=lambda: self.change_weight(entry.get()))
        button.place(x=10, y=70)
        win.mainloop()

    def change_weight(self, weight):
        self.weight = int(weight)
        canvas.itemconfig(self.text, text=weight)
        graph.remove_edge(self.start.names, self.end.names)
        graph.add_edge(self.start.names, self.end.names, weight=self.weight)

    def change_color(self, color):
        canvas.itemconfig(self.line, fill=color)

    def move(self):
        canvas.coords(self.line, create_line(self.start.a, self.start.b, self.end.a, self.end.b))
        canvas.coords(self.text, (self.start.a + self.end.a) / 2, (self.start.b + self.end.b) / 2 - 5)

    def remove(self):
        canvas.delete(self.line)
        canvas.delete(self.text)
        graph.remove_edge(self.start.names, self.end.names)

# Function for color change
def change_color(color_label):
    global color_vertex
    rgb, hx = askcolor()
    color_vertex = hx
    color_label.config(bg=color_vertex)

# Vertex addition function
def add_new_vertex():
    add_win = Tk()
    add_win.title("Add Vertex")
    add_win.geometry(window_size)
    add_win.wm_attributes('-topmost', 3)
    add_win.resizable(False, False)
    lab = Label(add_win, text="Enter vertex name")
    entnames = Entry(add_win)
    add_button = Button(add_win, text="Pick Color", command=lambda: change_color(color_label))
    color_button = Button(add_win, text="Add Vertex", command=lambda: add_vertex_to_graph(entnames, add_win))
    color_label = Label(add_win, width=2, bg="white")
    lab.grid(row=0, column=0, sticky="ew")
    entnames.grid(row=1, column=0, sticky="ewns")
    add_button.grid(row=2, column=0, sticky="ewns")
    color_button.grid(row=3, column=0, sticky="ewns")
    color_label.grid(row=1, column=1)
    add_win.mainloop()

# Edge creation function
def create_edge(entweight, entn1, entn2, window):
    try:
        weight = int(entweight.get())
    except ValueError:
        messagebox.showerror("Error", "Edge weight must be a number")
    else:
        n1 = entn1.get()
        n2 = entn2.get()
        for vertex in nodes:
            if vertex.names == n1:
                n1 = vertex
            if vertex.names == n2:
                n2 = vertex
        edges.append(Edge(n1, n2, weight))
        window.destroy()

# Edge addition menu
def add_new_edge():
    add_win = Tk()
    add_win.title("Add Edge")
    add_win.geometry("220x220+1050+260")
    add_win.wm_attributes('-topmost', 3)
    add_win.resizable(False, False)
    lab = Label(add_win, text="Start Vertex")
    entn1 = Entry(add_win, text="Start Vertex")
    lab2 = Label(add_win, text="End Vertex")
    entn2 = Entry(add_win, text="End Vertex")
    lab3 = Label(add_win, text="Edge Weight")
    entry_weight = Entry(add_win)
    add_button = Button(add_win, text="Pick Color", command=lambda: change_color(color_label))
    color_button = Button(add_win, text="Add Edge", command=lambda: create_edge(entry_weight, entn1, entn2, add_win))
    color_label = Label(add_win, width=2, bg="white")
    lab.grid(row=0, column=0, sticky="ew")
    entry_weight.grid(row=1, column=0, sticky="n")
    lab2.grid(row=2, column=0, sticky="ew")
    entn1.grid(row=3, column=0, sticky="n")
    lab3.grid(row=4, column=0, sticky="ew")
    entn2.grid(row=5, column=0, sticky="n")
    add_button.grid(row=6, column=0, sticky="n")
    color_button.grid(row=7, column=0, sticky="n")
    color_label.grid(row=1, column=1)
    add_win.mainloop()

# Canvas mouse events
def move_vertex(event):
    for n in nodes:
        if n.a - 25 < event.x < n.a + 25 and n.b - 25 < event.y < n.b + 25:
            n.move(event.x, event.y)
            break

def edit_name_or_weight(event):
    a, b = event.x, event.y
    for edge in edges:
        distance = sqrt((a - edge.start.a) ** 2 + (b - edge.start.b) ** 2) + sqrt((a - edge.end.a) ** 2 + (b - edge.end.b) ** 2)
        hypotenuse = sqrt((edge.end.a - edge.start.a) ** 2 + (edge.end.b - edge.start.b) ** 2)
        if abs(distance - hypotenuse) < 20:
            edge.edit_weight()
            break
    for n in nodes:
        if n.a - 25 < event.x < n.a + 25 and n.b - 25 < event.y < n.b + 25:
            n.edit_name()
            break

# Setup
root = Tk()
root.title("Graph Editor")
root.geometry("900x900")
root.resizable(False, False)

canvas = Canvas(root, width=900, height=900, bg="white")
canvas.pack()

graph = nx.Graph()
nodes = []
edges = []

root.bind("<Button-1>", move_vertex)
root.bind("<Button-3>", edit_name_or_weight)

add_vertex_button = Button(root, text="Add Vertex", command=add_new_vertex)
add_edge_button = Button(root, text="Add Edge", command=add_new_edge)
eulerian_path_button = Button(root, text="Find Eulerian Path", command=find_eulerian_path)

add_vertex_button.pack()
add_edge_button.pack()
eulerian_path_button.pack()

root.mainloop()
