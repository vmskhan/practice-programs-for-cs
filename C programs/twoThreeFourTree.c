#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct Node* node;

typedef struct Node {
    int keys[4];          
    node children[5];     
    int numKeys;         
} Node;


node createNode() {
    node newNode = (node)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->numKeys = 0;
    for (int i = 0; i < 5; i++) {
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
    int midKey = nodeToSplit->keys[2];

    newNode->keys[0] = nodeToSplit->keys[3];
    newNode->numKeys = 1;

    if (nodeToSplit->children[0] != NULL) {
        newNode->children[0] = nodeToSplit->children[3];
        newNode->children[1] = nodeToSplit->children[4];
        nodeToSplit->children[3] = nodeToSplit->children[4] = NULL;
    }

    nodeToSplit->numKeys = 2;

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

        if (parent->numKeys == 4) {
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

    if (current->numKeys == 4) {
        root = split(root, current);
    }

    return root;
}

node mergeNodes(node root, node node1, node node2, int parentKey) {
    node1->keys[node1->numKeys] = parentKey;
    for (int i = 0; i < node2->numKeys; i++) {
        node1->keys[node1->numKeys + 1 + i] = node2->keys[i];
    }
    
    if (node2->children[0] != NULL) {
        for (int i = 0; i <= node2->numKeys; i++) {
            node1->children[node1->numKeys + 1 + i] = node2->children[i];
        }
    }
    
    node1->numKeys = node1->numKeys + 1 + node2->numKeys;
    free(node2);
    return root;
}

node redistributeKeys(node root, node left, node right, node parent, int index) {
    if (left->numKeys > right->numKeys) {
        right->keys[right->numKeys] = parent->keys[index];
        parent->keys[index] = left->keys[left->numKeys - 1];
        if (left->children[0] != NULL) {
            right->children[right->numKeys + 1] = right->children[right->numKeys];
            right->children[right->numKeys] = left->children[left->numKeys];
        }
        right->numKeys++;
        left->numKeys--;
    } else {
        for (int i = left->numKeys; i > 0; i--) {
            left->keys[i] = left->keys[i - 1];
        }
        left->keys[0] = parent->keys[index];
        parent->keys[index] = right->keys[0];
        if (right->children[0] != NULL) {
            left->children[left->numKeys + 1] = right->children[0];
            for (int i = 0; i < right->numKeys; i++) {
                right->children[i] = right->children[i + 1];
            }
        }
        for (int i = 0; i < right->numKeys - 1; i++) {
            right->keys[i] = right->keys[i + 1];
        }
        left->numKeys++;
        right->numKeys--;
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
    int keyIndex = -1;
    
    while (current != NULL) {
        keyIndex = -1;
        for (int i = 0; i < current->numKeys; i++) {
            if (key == current->keys[i]) {
                keyIndex = i;
                break;
            }
        }
        
        if (keyIndex != -1) break;
        
        parent = current;
        int i;
        for (i = 0; i < current->numKeys && key > current->keys[i]; i++);
        current = current->children[i];
    }

    if (current == NULL) {
        printf("Key %d not found.\n", key);
        return root;
    }

    if (current->children[0] == NULL) {
        for (int i = keyIndex; i < current->numKeys - 1; i++) {
            current->keys[i] = current->keys[i + 1];
        }
        current->numKeys--;

        if (current == root && current->numKeys == 0) {
            free(current);
            return NULL;
        }

        if (current->numKeys < 1 && parent != NULL) {
            int parentIndex;
            for (parentIndex = 0; parentIndex <= parent->numKeys; parentIndex++) {
                if (parent->children[parentIndex] == current) break;
            }
            
            if (parentIndex > 0 && parent->children[parentIndex - 1]->numKeys > 1) {
                node leftSibling = parent->children[parentIndex - 1];
                root = redistributeKeys(root, leftSibling, current, parent, parentIndex - 1);
            }
            else if (parentIndex < parent->numKeys && parent->children[parentIndex + 1]->numKeys > 1) {
                node rightSibling = parent->children[parentIndex + 1];
                root = redistributeKeys(root, current, rightSibling, parent, parentIndex);
            }
            else {
                if (parentIndex > 0) {
                    root = mergeNodes(root, parent->children[parentIndex - 1], current, parent->keys[parentIndex - 1]);
                    for (int i = parentIndex - 1; i < parent->numKeys - 1; i++) {
                        parent->keys[i] = parent->keys[i + 1];
                        parent->children[i + 1] = parent->children[i + 2];
                    }
                    parent->numKeys--;
                }
                else {
                    root = mergeNodes(root, current, parent->children[1], parent->keys[0]);
                    for (int i = 0; i < parent->numKeys - 1; i++) {
                        parent->keys[i] = parent->keys[i + 1];
                        parent->children[i + 1] = parent->children[i + 2];
                    }
                    parent->numKeys--;
                }
                
                if (parent == root && parent->numKeys == 0) {
                    node newRoot = parent->children[0];
                    free(parent);
                    return newRoot;
                }
            }
        }
    }
    else {
        node successor = current->children[keyIndex + 1];
        while (successor->children[0] != NULL) {
            successor = successor->children[0];
        }
        current->keys[keyIndex] = successor->keys[0];
        root = deleteNode(root, successor->keys[0]);
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