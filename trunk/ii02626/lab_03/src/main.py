from tkinter import messagebox, Canvas, Label, Entry, Button, Tk, StringVar
from tkinter.colorchooser import askcolor
import numpy as np
from numpy import sqrt
import networkx as nx

MY_CONSTANT = "200x125+1065+260"


def line_intersect_circle(x1, y1, x2, y2):
    main_hypotenuse = sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    main_dx = x2 - x1
    main_dy = y2 - y1
    dx = (main_hypotenuse - 20) * main_dx / main_hypotenuse
    dy = (main_hypotenuse - 20) * main_dy / main_hypotenuse
    return x2 - dx, y2 - dy, x1 + dx, y1 + dy


class Node:
    def __init__(self, name):
        self.name = name
        rng_x = np.random.default_rng(42)
        rng_y = np.random.default_rng(42)
        self.x = rng_x.integers(0, 636)
        self.y = rng_y.integers(0, 636)

        self.krug = create_circle(self.x, self.y, 25, fill=color_vertex)
        self.txt = canv.create_text(self.x, self.y, anchor='center', text=name, font="Arial 10", fill="black")
        graph.add_node(name)

    def move(self, x, y):
        self.x = x
        self.y = y
        canv.coords(self.krug, x-20, y-20, x+20, y+20)
        canv.coords(self.txt, x, y)
        for edge in edges:
            if edge.nodik1 == self or edge.nodik2 == self:
                edge.move()

    def change_color(self, color):
        canv.itemconfig(self.krug, fill=color)

    def delete(self):
        canv.delete(self.krug)
        canv.delete(self.txt)
        for edge in edges:
            if edge.nodik1 == self or edge.nodik2 == self:
                edge.delete()
                edges.remove(edge)
        graph.remove_node(self.name)


def create_circle(x, y, r, **kwargs):
    return canv.create_oval(x-r, y-r, x+r, y+r, **kwargs)


class Edge:
    def __init__(self, node1, node2, weight: int):
        self.weight = weight
        self.nodik1 = node1
        self.nodik2 = node2
        self.line = canv.create_line(line_intersect_circle(self.nodik1.x, self.nodik1.y, self.nodik2.x, self.nodik2.y),
                                       width=2, fill="black")
        self.txt = canv.create_text((node1.x + node2.x) / 2, (node1.y + node2.y) / 2 - 5, anchor='center',
                                       text=self.weight, font="Arial 20", fill="white")
        graph.add_edge(node1.name, node2.name, weight=weight)

    def change(self):
        window = Tk()
        window.title("Change weight")
        window.geometry(MY_CONSTANT)
        window.wm_attributes('-topmost', 3)
        window.resizable(False, False)
        label = Label(window, text="Enter new weight")
        label.place(x=10, y=10)
        entry = Entry(window, width=10)
        entry.place(x=10, y=40)
        print(5)
        button = Button(window, text="Apply changes", command=lambda: self.change_weight(entry.get()))
        button.place(x=10, y=70)
        window.mainloop()

    def change_weight(self, weight):
        self.weight = int(weight)
        canv.itemconfig(self.txt, text=weight)
        graph.remove_edge(self.nodik1.name, self.nodik2.name)
        graph.add_edge(self.nodik1.name, self.nodik2.name, weight=self.weight)

    def change_color(self, color):
        canv.itemconfig(self.line, fill=color)

    def move(self):
        canv.coords(self.line, line_intersect_circle(self.nodik1.x, self.nodik1.y, self.nodik2.x, self.nodik2.y))
        canv.coords(self.txt, (self.nodik1.x + self.nodik2.x) / 2, (self.nodik1.y + self.nodik2.y) / 2 - 5)

    def delete(self):
        canv.delete(self.line)
        canv.delete(self.txt)
        graph.remove_edge(self.nodik1.name, self.nodik2.name)


def create_vertex(entry_of_name, window):
    name = entry_of_name.get()
    nodes.append(Node(name))
    window.destroy()


def chose_color(color_label):
    rgb, hx = askcolor()
    print(rgb)
    color_value = hx
    color_label.config(bg=color_value)


def menu_add_vertex():
    add_window = Tk()
    add_window.title("Add vertex")
    add_window.geometry(MY_CONSTANT)
    add_window.wm_attributes('-topmost', 3)
    add_window.resizable(False, False)
    label = Label(add_window, text="Vertex name")
    entry_of_name = Entry(add_window)
    add_button = Button(add_window, text="Chose color", command=lambda: chose_color(color_of_lable))
    color_of_button = Button(add_window, text="Create vertex", command=lambda: create_vertex(entry_of_name, add_window))
    color_of_lable = Label(add_window, width=2, bg="white")
    label.grid(row=0, column=0, sticky="ew")
    entry_of_name.grid(row=1, column=0, sticky="ewns")
    add_button.grid(row=2, column=0, sticky="ewns")
    color_of_button.grid(row=3, column=0, sticky="ewns")
    color_of_lable.grid(row=1, column=1)
    add_window.mainloop()


def create_edge(entry_weight, entry_node1, entry_node2, window):
    try:
        weight = int(entry_weight.get())
    except ValueError:
        messagebox.showerror("Error", "Weight must be number!")
    else:
        node1 = entry_node1.get()
        node2 = entry_node2.get()
        for vertex in nodes:
            if vertex.name == node1:
                node1 = vertex
            if vertex.name == node2:
                node2 = vertex
        edges.append(Edge(node1, node2, weight))
        window.destroy()


def menu_add_edge():
    add_window = Tk()
    add_window.title("Add edge")
    add_window.geometry("210x210+1000+200")
    add_window.wm_attributes('-topmost', 3)
    add_window.resizable(False, False)
    label = Label(add_window, text="Edge weight")
    entry_weight = Entry(add_window)
    label2 = Label(add_window, text="Name of 1st vertex")
    entry_node1_text = StringVar()
    entry_node1 = Entry(add_window, textvariable=entry_node1_text)
    entry_node1_text.set("Enter name of 1st vertex")
    label3 = Label(add_window, text="Name of 2nd vertex")
    entry_node2_text = StringVar()
    entry_node2 = Entry(add_window, textvariable=entry_node2_text)
    entry_node2_text.set("Enter name of 2nd vertex")

    add_button = Button(add_window, text="Choose color", command=lambda: chose_color(color_of_lable))
    color_of_button = Button(add_window, text="Add edge", command=lambda: create_edge(entry_weight, entry_node1,
                                                                                         entry_node2, add_window))
    color_of_lable = Label(add_window, width=2, bg="white")
    label.grid(row=0, column=0, sticky="ew")
    entry_weight.grid(row=1, column=0, sticky="ewns")
    label2.grid(row=2, column=0, sticky="ew")
    entry_node1.grid(row=3, column=0, sticky="ewns")
    label3.grid(row=4, column=0, sticky="ew")
    entry_node2.grid(row=5, column=0, sticky="ewns")
    add_button.grid(row=6, column=0, sticky="ewns")
    color_of_button.grid(row=7, column=0, sticky="ewns")
    color_of_lable.grid(row=1, column=1)
    add_window.mainloop()


def move_node(event):
    for node in nodes:
        if node.x - 25 < event.x < node.x + 25 and node.y - 25 < event.y < node.y + 25:
            node.move(event.x, event.y)
            break


def change_name_or_weight(event):
    x_, y_ = event.x, event.y
    for edge in edges:
        print(2)
        legs_of_sum = sqrt((x_ - edge.node1.x)**2 + (y_ - edge.node1.y)**2) + sqrt((x_ - edge.node2.x)**2 +
                                                                                     (y_ - edge.node2.y)**2)
        gipotenuza = sqrt((edge.node2.x - edge.node1.x)**2 + (edge.node2.y - edge.node1.y)**2)+10
        if legs_of_sum <= gipotenuza:
            edge.change()
            break
    else:
        for node in nodes:
            if node.x - 25 < event.x < node.x + 25 and node.y - 25 < event.y < node.y + 25:
                node.change()
                break


def change_color(event):
    x_, y_ = event.x, event.y
    for node in nodes:
        if node.x - 25 < event.x < node.x + 25 and node.y - 25 < event.y < node.y + 25:
            node.change_color(askcolor()[1])
            break
    else:
        for edge in edges:
            legs_of_sum = sqrt((x_ - edge.node1.x)**2 + (y_ - edge.node1.y)**2) +\
                       sqrt((x_ - edge.node2.x)**2 + (y_ - edge.node2.y)**2)
            hypotenuse = sqrt((edge.node2.x - edge.node1.x)**2 + (edge.node2.y - edge.node1.y)**2)+10
            if legs_of_sum <= hypotenuse:
                edge.change_color(askcolor()[1])
                break


def delete(event):
    x, y = event.x, event.y
    for node in nodes:
        if node.x - 25 < x < node.x + 25 and node.y - 25 < y < node.y + 25:
            node.delete()
            nodes.remove(node)
            print(1)
            break
    else:
        for edge in edges:
            print(2)
            legs_of_sum = sqrt((x - edge.node1.x)**2 + (y - edge.node1.y)**2) + sqrt((x - edge.node2.x)**2 +
                                                                                  (y - edge.node2.y)**2)
            hypotenuse = sqrt((edge.node2.x - edge.node1.x)**2 + (edge.node2.y - edge.node1.y)**2)+10
            if legs_of_sum <= hypotenuse:
                edge.delete()
                edges.remove(edge)
                break


def shortest_path():
    enter = []
    window = Tk()
    window.title("Vertex choice")
    window.geometry("210x130+1000+260")
    window.resizable(False, False)
    label = Label(window, text="Choose 1st vertex")
    label.grid(row=0, column=0, sticky="ew")
    entry1 = Entry(window)
    entry1.grid(row=1, column=0, sticky="ewns")
    label2 = Label(window, text="Choose 2nd vertex")
    label2.grid(row=2, column=0, sticky="ew")
    entry2 = Entry(window)
    entry2.grid(row=3, column=0, sticky="ewns")
    button = Button(window, text="Done", command=lambda: func(enter, window))
    button.grid(row=4, column=0, sticky="ewns")

    def func(arr, func_win):
        arr += [entry1.get(), entry2.get()]
        func_win.destroy()

        if len(arr) >= 2:
            display_props("Shortest path", nx.algorithms.shortest_path(graph, arr[0], arr[1]))
        else:
            return 0, 0
        func_win.mainloop()
        return arr[0], arr[1]


def display_props(title, props):
    string = ''
    for prop in props:
        string += str(prop) + ' '
    window = Tk()
    window.title(title)
    window.geometry("500x500")
    label = Label(window, text=string)
    label.pack()
    window.mainloop()


def eulerian_cycle():
    display_props("Eulerian cycle", nx.algorithms.eulerian_path(graph))


nodes = []
edges = []
color_vertex = "#fff"
graph = nx.Graph()
root = Tk()
root.title("GraphAPP")
root.geometry("800x600+500+150")
canv = Canvas(root, width=636, height=596, bg="grey")
canv.place(x=160, y=0)

button1 = Button(root, text="Add vertex", anchor="w", command=menu_add_vertex)
button2 = Button(root, text="Add edge", anchor="w", command=menu_add_edge)
button3 = Button(root, text="Eulerian cycle", anchor="w", command=eulerian_cycle)
button4 = Button(root, text="Shortest path", anchor="w", command=shortest_path)
button1.grid(row=0, column=0, stick="ew")
button2.grid(row=1, column=0, stick="ew")
button3.grid(row=2, column=0, stick="ew")
button4.grid(row=3, column=0, stick="ew")
canv.bind('<B1-Motion>', move_node)
canv.bind('<Button-2>', change_name_or_weight)
canv.bind('<Button-3>', change_color)
root.bind('<B3-Motion>', delete)
root.mainloop()