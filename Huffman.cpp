#include "Huffman.h"

const int BUFFER_SIZE = 65536; // 64KB buffer

// delete Huffman tree and free memory so that there are no memory leaks
void deleteTree(Node* node)
{
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

// get file size
ll getFileSize(string fileName)
{
    ifstream file(fileName, ios::binary | ios::ate);
    if (!file.is_open())
        return 0;
    ll size = file.tellg();
    file.close();
    return size;
}

// print frequency table
void writeFreqTableFile(string fileName, Heap heap)
{
    cout << "Frequencies" << endl;
    while (heap.size > 0) {
        Node value = heap.Poll();
        if (value.freq == (ll)-1)
            break;

        if (value.data == '\n') {
            cout << "\\n | " << value.freq << endl;
        } else if (value.data == '\t') {
            cout << "\\t | " << value.freq << endl;
        } else if (value.data == ' ') {
            cout << "SPACE | " << value.freq << endl;
        } else {
            cout << value.data << " | " << value.freq << endl;
        }
    }
}

// Write codes to .cod
void writeCodesBatch(string fileName, string codes[256])
{
    ofstream codeFile(fileName);
    for (int i = 0; i < 256; i++) {
        if (codes[i] != "") {
            char c = (char)i;
            if (c == '\n') {
                codeFile << "\\n:" << codes[i] << endl;
            } else if (c == '\t') {
                codeFile << "\\t:" << codes[i] << endl;
            } else if (c == '\\') {
                codeFile << "\\\\:" << codes[i] << endl;
            } else {
                codeFile << c << ":" << codes[i] << endl;
            }
        }
    }
    codeFile.close();
}

// get character frequencies from input file
Heap getFrequencies(string fileName)
{
    ll freq[256] = {0};

    ifstream file(fileName, ios::binary);

    char buffer[BUFFER_SIZE];
    while (file) {
        file.read(buffer, BUFFER_SIZE);
        int count = file.gcount();
        for (int i = 0; i < count; i++) {
            freq[(unsigned char)buffer[i]]++;
        }
    }
    file.close();

    // Add all characters with freq > 0 to heap
    Heap heap;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            heap.Add(Node((char)i, freq[i]));
        }
    }
    return heap;
}

void generateCodes(Node* node, string code, string codes[256])
{
    if (node == nullptr)
        return;

    if (node->left == nullptr && node->right == nullptr) {
        if (code == "")
            codes[(unsigned char)node->data] = "0";
        else
            codes[(unsigned char)node->data] = code;
        
        char c = node->data;
        if (c == '\n')
            cout << "\\n : " << codes[(unsigned char)c] << endl;
        else if (c == '\t')
            cout << "\\t : " << codes[(unsigned char)c] << endl;
        else if (c == ' ')
            cout << "SPACE : " << codes[(unsigned char)c] << endl;
        else
            cout << c << " : " << codes[(unsigned char)c] << endl;
        
        return;
    }

    generateCodes(node->left, code + "0", codes);
    generateCodes(node->right, code + "1", codes);
}

// Build Huffman tree from heap
Node* tree(Heap heap)
{
    if (heap.size == 0)
        return nullptr;

    // Build tree by combining two smallest nodes
    while (heap.size > 1) {
        Node leftVal = heap.Poll();
        Node rightVal = heap.Poll();

        Node* left = new Node(leftVal.data, leftVal.freq);
        left->left = leftVal.left;
        left->right = leftVal.right;

        Node* right = new Node(rightVal.data, rightVal.freq);
        right->left = rightVal.left;
        right->right = rightVal.right;

        // Create parent node
        Node* parent = new Node(left->freq + right->freq, left, right);
        heap.Add(*parent);
    }

    // Get root
    Node rootVal = heap.Poll();
    Node* root = new Node(rootVal.data, rootVal.freq);
    root->left = rootVal.left;
    root->right = rootVal.right;
    return root;
}

string decToBinary(unsigned char n)
{
    string binary = "00000000";
    for (int i = 7; i >= 0; i--) {
        if (n % 2 == 1)
            binary[i] = '1';
        n = n / 2;
    }
    return binary;
}

// Compress a file
void Compress(string inputFile, string codeFile, string outputFile)
{
    Heap freqHeap = getFrequencies(inputFile);
    Node* root = tree(freqHeap);

    cout << "Generated Codes:" << endl;
    string codes[256];
    generateCodes(root, "", codes);
    writeCodesBatch(codeFile, codes);
    deleteTree(root);


    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);

    unsigned char padding = 0;
    out.write((char*)&padding, 1);

    char buffer[BUFFER_SIZE];
    unsigned char bitBuffer = 0;
    int bitCount = 0;
    ll bytesRead = 0;

    while (in) {
        in.read(buffer, BUFFER_SIZE);
        int count = in.gcount();
        if (count == 0)
            break;

        bytesRead += count;

        // Encode each byte
        for (int i = 0; i < count; i++) {
            string& code = codes[(unsigned char)buffer[i]];
            int codeLen = code.length();

            // Add each bit of code to buffer
            for (int j = 0; j < codeLen; j++) {
                bitBuffer = bitBuffer << 1;
                if (code[j] == '1')
                    bitBuffer = bitBuffer | 1;
                bitCount++;

                // Write byte when buffer is full
                if (bitCount == 8) {
                    out.put(bitBuffer);
                    bitBuffer = 0;
                    bitCount = 0;
                }
            }
        }
    }

    // Handle remaining bits
    if (bitCount > 0) {
        padding = 8 - bitCount;
        bitBuffer = bitBuffer << padding;
        out.put(bitBuffer);
    }

    // Write padding at start of file
    out.seekp(0);
    out.write((char*)&padding, 1);

    in.close();
    out.close();
}

// Rebuild tree from code file
Node* rebuildTreeFromCodeFile(string codeFile)
{
    ifstream file(codeFile);

    Node* root = new Node();
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        char symbol;
        string code;

        if (line[0] == '\\' && line.length() >= 2) {
            if (line[1] == 'n') {
                symbol = '\n';
                code = line.substr(3);
            } else if (line[1] == 't') {
                symbol = '\t';
                code = line.substr(3);
            } else if (line[1] == '\\') {
                symbol = '\\';
                code = line.substr(3);
            } else {
                symbol = line[0];
                code = line.substr(2);
            }
        } else {
            symbol = line[0];
            code = line.substr(2);
        }

        
        Node* current = root;
        for (int i = 0; i < code.length(); i++) {
            if (code[i] == '0') {
                if (current->left == nullptr)
                    current->left = new Node();
                current = current->left;
            } else {
                if (current->right == nullptr)
                    current->right = new Node();
                current = current->right;
            }
        }
        current->data = symbol;
    }
    file.close();
    return root;
}

// Decompress a file
void Decompress(string inputFile, string codeFile, string outputFile)
{
    Node* root = rebuildTreeFromCodeFile(codeFile);

    ifstream in(inputFile, ios::binary);
    ofstream out(outputFile, ios::binary);


    // Read padding byte
    unsigned char padding;
    in.read((char*)&padding, 1);

    ll totalSize = getFileSize(inputFile);
    ll bytesRead = 1;

    Node* current = root;
    char buffer[BUFFER_SIZE];
    char outBuffer[BUFFER_SIZE];
    int outPos = 0;

    while (in) {
        in.read(buffer, BUFFER_SIZE);
        int count = in.gcount();
        if (count == 0)
            break;

        bytesRead += count;

        bool isLastChunk = (in.peek() == EOF);


        for (int i = 0; i < count; i++) {
            unsigned char byte = (unsigned char)buffer[i];

            // How many bits to read from this byte
            int bitsToRead = 8;
            if (isLastChunk && i == count - 1) {
                bitsToRead = 8 - padding;
            }

            for (int bit = 7; bit >= 8 - bitsToRead; bit--) {
                int bitVal = (byte >> bit) & 1;

                if (bitVal == 0)
                    current = current->left;
                else
                    current = current->right;

                // If leaf node, output character
                if (current != nullptr && current->left == nullptr && current->right == nullptr) {
                    outBuffer[outPos++] = current->data;
                    current = root;

                    if (outPos >= BUFFER_SIZE) {
                        out.write(outBuffer, outPos);
                        outPos = 0;
                    }
                }
            }
        }
    }

    if (outPos > 0) {
        out.write(outBuffer, outPos);
    }
    in.close();
    out.close();
    deleteTree(root);

    cout << "Decompression done" << endl;
}
