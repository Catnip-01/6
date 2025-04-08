import matplotlib.pyplot as plt
import networkx as nx

class Node:
    def __init__(self, v_runtime, pid, color="red"):
        self.v_runtime = v_runtime  # Key for sorting
        self.pid = pid              # Process ID
        self.color = color          # "red" or "black"
        self.left = None            # Left child
        self.right = None           # Right child
        self.parent = None          # Parent node

class RedBlackTree:
    def __init__(self):
        self.root = None

    def insert(self, v_runtime, pid):
        """
        Insert a new process into the RB Tree.
        """
        new_node = Node(v_runtime, pid)
        self._bst_insert(new_node)
        self._fix_violations(new_node)

    def _bst_insert(self, node):
        """
        Perform standard BST insertion.
        """
        parent = None
        current = self.root
        while current is not None:
            parent = current
            if node.v_runtime < current.v_runtime:
                current = current.left
            else:
                current = current.right

        node.parent = parent
        if parent is None:
            self.root = node  # Tree was empty
        elif node.v_runtime < parent.v_runtime:
            parent.left = node
        else:
            parent.right = node

    def _fix_violations(self, node):
        """
        Fix violations of RB Tree properties after insertion.
        """
        while node != self.root and node.parent.color == "red":
            parent = node.parent
            grandparent = parent.parent

            if parent == grandparent.left:  # Parent is the left child
                uncle = grandparent.right
                if uncle and uncle.color == "red":  # Case 1: Uncle is red
                    parent.color = "black"
                    uncle.color = "black"
                    grandparent.color = "red"
                    node = grandparent
                else:
                    if node == parent.right:  # Case 2: Node is a right child
                        node = parent
                        self._left_rotate(node)
                    # Case 3: Node is a left child
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self._right_rotate(node.parent.parent)
            else:  # Parent is the right child (symmetric cases)
                uncle = grandparent.left
                if uncle and uncle.color == "red":  # Case 1: Uncle is red
                    parent.color = "black"
                    uncle.color = "black"
                    grandparent.color = "red"
                    node = grandparent
                else:
                    if node == parent.left:  # Case 2: Node is a left child
                        node = parent
                        self._right_rotate(node)
                    # Case 3: Node is a right child
                    node.parent.color = "black"
                    node.parent.parent.color = "red"
                    self._left_rotate(node.parent.parent)

        self.root.color = "black"

    def _left_rotate(self, x):
        """
        Perform a left rotation at node x.
        """
        y = x.right
        x.right = y.left
        if y.left:
            y.left.parent = x
        y.parent = x.parent
        if x.parent is None:
            self.root = y
        elif x == x.parent.left:
            x.parent.left = y
        else:
            x.parent.right = y
        y.left = x
        x.parent = y

    def _right_rotate(self, y):
        """
        Perform a right rotation at node y.
        """
        x = y.left
        y.left = x.right
        if x.right:
            x.right.parent = y
        x.parent = y.parent
        if y.parent is None:
            self.root = x
        elif y == y.parent.left:
            y.parent.left = x
        else:
            y.parent.right = x
        x.right = y
        y.parent = x

    def find_min(self):
        """
        Find the node with the minimum v-runtime.
        """
        current = self.root
        while current and current.left:
            current = current.left
        return current

    def delete(self, v_runtime):
        """
        Delete a node with the given v-runtime.
        """
        node = self._find_node(v_runtime)
        if not node:
            print(f"No process with v-runtime {v_runtime} exists.")
            return

        self._delete_node(node)

    def _find_node(self, v_runtime):
        """
        Find the node with the given v-runtime.
        """
        current = self.root
        while current:
            if v_runtime == current.v_runtime:
                return current
            elif v_runtime < current.v_runtime:
                current = current.left
            else:
                current = current.right
        return None

    def _delete_node(self, node):
        """
        Delete a node from the RB Tree.
        """
        # TODO: Implement RB Tree deletion logic (complex and omitted for brevity).

    def visualize(self):
        """
        Visualize the RB Tree using NetworkX and Matplotlib.
        """
        G = nx.Graph()
        pos = {}

        def add_edges(node, x=0, y=0, layer=1):
            if not node:
                return
            pos[node] = (x, y)
            if node.left:
                G.add_edge(node, node.left)
                add_edges(node.left, x - 1 / (2 ** layer), y - 1, layer + 1)
            if node.right:
                G.add_edge(node, node.right)
                add_edges(node.right, x + 1 / (2 ** layer), y - 1, layer + 1)

        add_edges(self.root)
        labels = {node: f"{node.v_runtime}\n({node.pid})" for node in G.nodes()}
        colors = ["red" if node.color == "red" else "black" for node in G.nodes()]

        plt.figure(figsize=(8, 6))
        nx.draw(G, pos, labels=labels, node_color=colors, with_labels=True, node_size=2000, font_size=10)
        plt.title("Red-Black Tree Visualization")
        plt.show()


# Example Usage
if __name__ == "__main__":
    rb_tree = RedBlackTree()

    # Step 1: Insert processes with v-runtime
    rb_tree.insert(10, 1)
    rb_tree.insert(5, 2)
    rb_tree.insert(15, 3)
    rb_tree.insert(20, 6)
    rb_tree.insert(14, 8)

    # Step 2: Visualize the RB Tree
    rb_tree.visualize()

    # Step 3: Find the process with the minimum v-runtime
    min_node = rb_tree.find_min()
    if min_node:
        print(f"Process with minimum v-runtime: PID {min_node.pid}, v-runtime {min_node.v_runtime}")

    # Step 4: Delete a process
    rb_tree.delete(5)

    # Step 5: Visualize the RB Tree after deletion
    rb_tree.visualize()