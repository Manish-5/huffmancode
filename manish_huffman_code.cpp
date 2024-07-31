
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

// A Huffman tree node
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;

    Node(char data, int freq) {
        left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// Comparison object to be used to order the heap
struct compare {
    bool operator()(Node* l, Node* r) {
        return (l->freq > r->freq);
    }
};

// Function to print Huffman Codes in preorder traversal
void printCodes(Node* root, std::string str, std::unordered_map<char, std::string>& huffmanCodes) {
    if (!root)
        return;

    // If this is a leaf node, it contains one of the input characters
    if (root->data != '$')
        huffmanCodes[root->data] = str;

    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

// The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
void buildHuffmanTree(std::string S, std::vector<int> f) {
    Node* left;
    Node* right;
    Node* top;

    // Create a min heap & inserts all characters of data[]
    std::priority_queue<Node*, std::vector<Node*>, compare> minHeap;

    for (int i = 0; i < S.size(); ++i)
        minHeap.push(new Node(S[i], f[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies.
        // Make the two extracted node as left and right children of this new node. Add this node to the min heap
        top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }

    // The remaining node is the root node and the tree is complete
    Node* root = minHeap.top();

    // Print Huffman codes using the Huffman tree built above
    std::unordered_map<char, std::string> huffmanCodes;
    printCodes(root, "", huffmanCodes);

    // Print the Huffman codes
    for (auto pair: huffmanCodes)
        std::cout << pair.first << ": " << pair.second << std::endl;
}

int main() {
    std::string S = "abcdef";
    std::vector<int> f = {5, 9, 12, 13, 16, 45};

    buildHuffmanTree(S, f);

    return 0;
}
