#include <bits/stdc++.h>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node *a, Node *b) {
        return a->freq > b->freq;
    }
};

void buildHuffmanCodes(Node *root, const string &code, unordered_map<char, string> &huffmanCodes) {
    if (!root)
        return;
    if (!root->left && !root->right) {  
        huffmanCodes[root->ch] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffmanCodes);
    buildHuffmanCodes(root->right, code + "1", huffmanCodes);
}

unordered_map<char, string> generateHuffmanCodes(const string &text) {
    unordered_map<char, int> freqMap;

    for (char ch : text)
        freqMap[ch]++;

    priority_queue<Node *, vector<Node *>, compare> pq;

    for (const auto &pair : freqMap)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();
        Node *merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    Node *root = pq.top();
    unordered_map<char, string> huffmanCodes;
    buildHuffmanCodes(root, "", huffmanCodes);  

    return huffmanCodes;
}

string compress(const string &text, const unordered_map<char, string> &huffmanCodes) {
    string compressedData = "";
    for (char ch : text) {
        compressedData += huffmanCodes.at(ch);
    }
    return compressedData;
}

string decompress(const string &compressedData, Node *root) {
    string decompressedText = "";
    Node *current = root;

    for (char bit : compressedData) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {  
            decompressedText += current->ch;
            current = root;
        }
    }
    return decompressedText;
}

void saveToFile(const string &filename, const string &data) {
    ofstream outFile(filename, ios::binary);
    outFile << data;
    outFile.close();
}

string loadFromFile(const string &filename) {
    ifstream inFile(filename, ios::binary);
    string data((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();
    return data;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string inputFile = "C:/Users/KIIT/Desktop/input.txt";
    string compressedFile = "C:/Users/KIIT/Desktop/Compressed_Text.bin";
    string decompressedFile = "C:/Users/KIIT/Desktop/Decompressed_Text.txt";
    string char_code = "C:/Users/KIIT/Desktop/char_code.txt";

    string text = loadFromFile(inputFile);
    if (text.empty()) {
        cerr << "Error: Input file is empty or cannot be read.\n";
        return 1;
    }
    cout << "Original Text: " << text << endl;

    unordered_map<char, string> huffmanCodes = generateHuffmanCodes(text);
    cout << "\nHuffman Codes:\n";

    stringstream ss;
    for (const auto &pair : huffmanCodes) {
        cout << pair.first << ": " << pair.second << "\n";
        ss << pair.first << ": " << pair.second << "\n"; 
    }
    string huffmanCodeString = ss.str();

    saveToFile(char_code, huffmanCodeString);
    cout << "\nCode is saved to: " << char_code << "\n";
    cout << "Code Length (in characters): " << huffmanCodeString.size() << "\n";

    string compressedData = compress(text, huffmanCodes);
    saveToFile(compressedFile, compressedData);
    cout << "\nCompressed Data saved to: " << compressedFile << "\n";
    cout << "Compressed Data Length (in bits): " << compressedData.size() << "\n";


    Node *root = new Node('\0', 0);  
    for (const auto &pair : huffmanCodes) {
        Node *current = root;
        string code = pair.second;

        for (char bit : code) {
            if (bit == '0') {
                if (!current->left)
                    current->left = new Node('\0', 0);
                current = current->left;
            } else {
                if (!current->right)
                    current->right = new Node('\0', 0);
                current = current->right;
            }
        }
        current->ch = pair.first;  
    }

    string decompressedText = decompress(compressedData, root);
    saveToFile(decompressedFile, decompressedText);
    cout << "\nDecompressed Data saved to: " << decompressedFile << "\n";

    // Step 6: Verify correctness
    if (text == decompressedText) {
        cout << "Decompression successful: The original and decompressed texts match.\n";
    } else {
        cout << "Decompression failed: The original and decompressed texts do not match.\n";
    }

    return 0;
}
