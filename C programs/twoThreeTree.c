#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node* node;

typedef struct Node {
    int keys[3];
    node children[4];
    int numKeys;
} Node;

node createNode() {
    node newNode = (node)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->numKeys = 0;
    for (int i = 0; i < 4; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void freeTree(node root) {
    if (root == NULL) {
        return;
    }
    
    for (int i = 0; i <= root->numKeys; i++) {
        freeTree(root->children[i]);
    }
    
    free(root);
}

bool search(node root, int key) {
    if (root == NULL) {
        return false;
    }

    int i;
    for (i = 0; i < root->numKeys; i++) {
        if (key == root->keys[i]) {
            return true;
        }
        if (key < root->keys[i]) {
            return search(root->children[i], key);
        }
    }
    return search(root->children[i], key);
}

node findParent(node root, node child) {
    if (root == NULL || root->children[0] == NULL) {
        return NULL;
    }

    for (int i = 0; i <= root->numKeys; i++) {
        if (root->children[i] == child) {
            return root;
        }
        node result = findParent(root->children[i], child);
        if (result != NULL) {
            return result;
        }
    }
    return NULL;
}

node split(node root, node nodeToSplit) {
    node newNode = createNode();
    int midKey = nodeToSplit->keys[1];

    newNode->keys[0] = nodeToSplit->keys[2];
    newNode->numKeys = 1;

    if (nodeToSplit->children[0] != NULL) {
        newNode->children[0] = nodeToSplit->children[2];
        newNode->children[1] = nodeToSplit->children[3];
        nodeToSplit->children[2] = nodeToSplit->children[3] = NULL;
    }

    nodeToSplit->numKeys = 1;

    if (root == nodeToSplit) {
        node newRoot = createNode();
        newRoot->keys[0] = midKey;
        newRoot->children[0] = nodeToSplit;
        newRoot->children[1] = newNode;
        newRoot->numKeys = 1;
        return newRoot;
    } 
    else {
        node parent = findParent(root, nodeToSplit);
        int i = parent->numKeys - 1;
        
        while (i >= 0 && parent->keys[i] > midKey) {
            parent->keys[i + 1] = parent->keys[i];
            parent->children[i + 2] = parent->children[i + 1];
            i--;
        }
        
        parent->keys[i + 1] = midKey;
        parent->children[i + 2] = newNode;
        parent->numKeys++;

        if (parent->numKeys == 3) {
            root = split(root, parent);
        }
    }

    return root;
}

node insert(node root, int key) {
    if (root == NULL) {
        root = createNode();
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    }

    node current = root;
    while (current->children[0] != NULL) {
        int i = 0;
        while (i < current->numKeys && key > current->keys[i]) {
            i++;
        }
        current = current->children[i];
    }

    int i = current->numKeys - 1;
    while (i >= 0 && current->keys[i] > key) {
        current->keys[i + 1] = current->keys[i];
        i--;
    }
    current->keys[i + 1] = key;
    current->numKeys++;

    if (current->numKeys == 3) {
        root = split(root, current);
    }

    return root;
}

node deleteNode(node root, int key) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return NULL;
    }

    node current = root;
    node parent = NULL;
    int i;
    
    while (current != NULL) {
        for (i = 0; i < current->numKeys && key > current->keys[i]; i++);
        if (i < current->numKeys && key == current->keys[i]) {
            break;
        }
        parent = current;
        current = current->children[i];
    }

    if (current == NULL) {
        printf("Key %d not found.\n", key);
        return root;
    }

    if (current->children[0] == NULL) {
        for (int j = i; j < current->numKeys - 1; j++) {
            current->keys[j] = current->keys[j + 1];
        }
        current->numKeys--;

        if (root == current && current->numKeys == 0) {
            free(current);
            return NULL;
        }
        
        if (current->numKeys == 0 && parent != NULL) {
            for (i = 0; i <= parent->numKeys; i++) {
                if (parent->children[i] == current) {
                    break;
                }
            }
            
            for (int j = i; j < parent->numKeys; j++) {
                parent->children[j] = parent->children[j + 1];
            }
            parent->children[parent->numKeys] = NULL;
            
            free(current);
        }
        
        return root;
    } 
    else {
        node successor = current->children[i + 1];
        node prev = current;
        
        while (successor->children[0] != NULL) {
            prev = successor;
            successor = successor->children[0];
        }
        
        current->keys[i] = successor->keys[0];
        
        if (successor->numKeys == 1 && successor->children[0] == NULL) {
            for (i = 0; i <= prev->numKeys; i++) {
                if (prev->children[i] == successor) {
                    break;
                }
            }
            
            for (int j = i; j < prev->numKeys; j++) {
                prev->children[j] = prev->children[j + 1];
            }
            prev->children[prev->numKeys] = NULL;
            
            free(successor);
            return root;
        }
        
        for (i = 0; i < successor->numKeys - 1; i++) {
            successor->keys[i] = successor->keys[i + 1];
        }
        successor->numKeys--;
    }
    
    return root;
}

void inorderTraversal(node root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->numKeys; i++) {
        inorderTraversal(root->children[i]);
        printf("%d ", root->keys[i]);
    }
    inorderTraversal(root->children[root->numKeys]);
}

void insertFromFile(const char* filename, node* root) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    int num;
    while (fscanf(file, "%d", &num) == 1) {
        *root = insert(*root, num);
    }
    fclose(file);
}

int main() {
    node root = NULL;
    const char* filename = "case40.txt";
    struct timespec start, end;
    double time_taken;

    clock_gettime(CLOCK_MONOTONIC, &start);
    insertFromFile(filename, &root);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;

    printf("\nIn-order Traversal: ");
    inorderTraversal(root);
    printf("\nTime taken for insertion: %lf microseconds", time_taken);

    clock_gettime(CLOCK_MONOTONIC, &start);
    if (search(root, 25)) {
        printf("\nKey found");
    } else {
        printf("\nKey not found");
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("\nTime taken for searching: %lf microseconds", time_taken);

    clock_gettime(CLOCK_MONOTONIC, &start);
    root = deleteNode(root, 80);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_taken = (end.tv_sec - start.tv_sec) * 1e6 + (end.tv_nsec - start.tv_nsec) / 1e3;
    printf("\nTime taken for deletion: %lf microseconds\n", time_taken);

    freeTree(root);

    return 0;
}