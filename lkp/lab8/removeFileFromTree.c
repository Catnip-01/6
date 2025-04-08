#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct Process {
    char pid[10];
    int runtime;
    int weight;
    double vruntime;
} Process;

typedef struct Node {
    Process process;
    struct Node *left;
    struct Node *right;
    int color; // 0: black, 1: red
} Node;

Node *root = NULL;

// Function to find the minimum vruntime process in the RB tree
Process findMinVruntime() {
    Node *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current->process;
}

// Function to create a new node
Node *createNode(Process process) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->process = process;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // Red by default
    return newNode;
}

// Function to perform left rotation
Node *leftRotate(Node *node) {
    Node *rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    return rightChild;
}

// Function to perform right rotation
Node *rightRotate(Node *node) {
    Node *leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    return leftChild;
}

// Function to fix the RB tree after insertion
Node *fixRBTree(Node *root, Node *node) {
    Node *parent = NULL;
    Node *grandparent = NULL;

    while (node != root && node->color == 1 && node->parent->color == 1) {
        parent = node->parent;
        grandparent = parent->parent;

        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;

            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }

                rightRotate(grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        } else {
            Node *uncle = grandparent->left;

            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }

                leftRotate(grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                node = parent;
            }
        }
    }

    root->color = 0; // Root must be black
    return root;
}

// Function to insert a process into the RB tree
Node *insertProcess(Node *root, Process process) {
    Node *newNode = createNode(process);
    Node *current = root;
    Node *parent = NULL;

    while (current != NULL) {
        parent = current;
        if (process.vruntime < current->process.vruntime) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (parent == NULL) {
        root = newNode;
    } else if (process.vruntime < parent->process.vruntime) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    root = fixRBTree(root, newNode);
    return root;
}

// Function to delete a process (Simplified for demonstration)
Node *deleteProcess(Node *root, Process process) {
    // Basic deletion (does not handle all RB tree cases)
    // In a real implementation, you'd need to handle all cases
    // including rebalancing.
    Node *current = root;
    Node *parent = NULL;

    while (current != NULL) {
        if (current->process.vruntime == process.vruntime) {
            if (parent == NULL) {
                root = NULL;
            } else if (parent->left == current) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
            free(current);
            return root;
        }
        parent = current;
        if (process.vruntime < current->process.vruntime) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return root;
}

int main() {
    Process p1 = {"P1", 20, 10, 0};
    Process p2 = {"P2", 30, 5, 0};
    Process p3 = {"P3", 15, 15, 0};

    root = insertProcess(root, p1);
    root = insertProcess(root, p2);
    root = insertProcess(root, p3);

    int time = 0;
    int total_weight = p1.weight+p2.weight+p3.weight;

    while (root != NULL) {
        Process currentProcess = findMinVruntime();
        printf("Time %d: Running %s\n", time, currentProcess.pid);

        double slice_time = (double)currentProcess.weight / total_weight * 10.0;
        if (currentProcess.runtime <= slice_time) {
            time += currentProcess.runtime;
            currentProcess.vruntime += currentProcess.runtime * (1024.0 / currentProcess.weight);
            currentProcess.runtime = 0;
        } else {
            time += (int)slice_time;
            currentProcess.runtime -= (int)slice_time;
            currentProcess.vruntime += slice_time * (1024.0 / currentProcess.weight);
        }

        if (currentProcess.runtime <= 0) {
            printf("Time %d: %s finished.\n", time, currentProcess.pid);
            root = deleteProcess(root, currentProcess);
        } else {
            root = deleteProcess(root, currentProcess);
            root = insertProcess(root, currentProcess);
        }
        total_weight = 0;
        Node *temp = root;
        while(temp != NULL){
            total_weight+=temp->process.weight;
            if(temp->left != NULL) {temp = temp->left;}
            else if(temp->right != NULL){temp = temp->right;}
            else{break;}
        }

    }

    return 0;
}