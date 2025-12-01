#include <stdio.h>
#include <stdlib.h>

// Structure for symbol (character + frequency)
typedef struct SYMBOL {
    char alphabet;
    int frequency;
} SYMBOL;

// Node structure for Huffman tree
typedef struct Node {
    SYMBOL symbol;
    struct Node *left, *right;
} Node;

// Function to create new node
Node* createNode(char alphabet, int frequency) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->symbol.alphabet = alphabet;
    newNode->symbol.frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Min-Heap structure
typedef struct MinHeap {
    int size;
    int capacity;
    Node** array;
} MinHeap;

// Create MinHeap
MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array = (Node**) malloc(heap->capacity * sizeof(Node*));
    return heap;
}

// Swap nodes
void swapNodes(Node** a, Node** b) {
    Node* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void heapify(MinHeap* heap, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < heap->size && heap->array[left]->symbol.frequency < heap->array[smallest]->symbol.frequency)
        smallest = left;

    if (right < heap->size && heap->array[right]->symbol.frequency < heap->array[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != i) {
        swapNodes(&heap->array[i], &heap->array[smallest]);
        heapify(heap, smallest);
    }
}

// Extract minimum
Node* extractMin(MinHeap* heap) {
    Node* temp = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    heapify(heap, 0);
    return temp;
}

// Insert node in heap
void insertHeap(MinHeap* heap, Node* node) {
    int i = heap->size;
    heap->array[i] = node;
    heap->size++;

    while (i && heap->array[i]->symbol.frequency < heap->array[(i-1)/2]->symbol.frequency) {
        swapNodes(&heap->array[i], &heap->array[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Build min heap
void buildMinHeap(MinHeap* heap) {
    int n = heap->size - 1;
    for (int i = (n-1)/2; i >= 0; i--)
        heapify(heap, i);
}

// Build Huffman Tree
Node* buildHuffmanTree(SYMBOL symbols[], int n) {
    MinHeap* heap = createMinHeap(n);

    for (int i = 0; i < n; i++)
        heap->array[i] = createNode(symbols[i].alphabet, symbols[i].frequency);
    heap->size = n;
    buildMinHeap(heap);

    while (heap->size > 1) {
        Node* left = extractMin(heap);
        Node* right = extractMin(heap);

        Node* parent = createNode('$', left->symbol.frequency + right->symbol.frequency);
        parent->left = left;
        parent->right = right;

        insertHeap(heap, parent);
    }

    return extractMin(heap);  // Root of Huffman tree
}

// Inorder Traversal
void inorderTraversal(Node* root) {
    if (root == NULL) return;
    inorderTraversal(root->left);
    if (root->symbol.alphabet != '$')
        printf("%c ", root->symbol.alphabet);
    inorderTraversal(root->right);
}

// Main function
int main() {
    int n;
    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    SYMBOL symbols[n];
    printf("Enter the alphabets: ");
    for (int i = 0; i < n; i++)
        scanf(" %c", &symbols[i].alphabet);

    printf("Enter its frequencies: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &symbols[i].frequency);

    Node* root = buildHuffmanTree(symbols, n);

    printf("In-order traversal of the tree (Huffman): ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}
