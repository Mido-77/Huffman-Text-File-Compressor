#include "Huffman.h"

// Printing frequency table in terminal
void writeFreqTableFile(const string& fileName, Heap heap)
{
    cout << "Frequencies (Sorted):" << endl;
    while (heap.size > 0) {
        Node value = heap.Poll();
        if (value.freq == (ll)-1)
            break; // Empty heap sentinel

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

// Writing codes to .cod file
void writeCodes(const string& fileName, string code)
{
    ofstream MyFile(fileName, ios::app);

    char symbol = code.at(0);
    if (symbol == '\n') {
        MyFile << "\\n" << code.substr(1) << "\n";
    } else if (symbol == '\t') {
        MyFile << "\\t" << code.substr(1) << "\n";
    } else if (symbol == '\\') {
        MyFile << "\\\\" << code.substr(1) << "\n";
    } else {
        MyFile << code << "\n";
    }
    MyFile.close();
}

// Getting frequencies of each character from the input file (Streaming)
Heap getFrequencies(const string& fileName)
{
    ll freq[256] = { 0 };

    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return Heap();
    }

    const size_t BUFFER_SIZE = 4096 * 4;
    char buffer[BUFFER_SIZE];

    while (file.read(buffer, BUFFER_SIZE) || file.gcount()) {
        size_t count = file.gcount();
        for (size_t i = 0; i < count; ++i) {
            unsigned char ch = (unsigned char)buffer[i];
            freq[ch]++;
        }
    }
    file.close();

    Heap heap;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            heap.Add(Node((char)i, freq[i]));
        }
    }

    return heap;
}

// Generating Huffman Codes by traversing the tree (pre-order)
void printCodes(Node* recNode, string output, string fileName)
{
    if (recNode == nullptr)
        return;
    if (recNode->data != '\0') {
        string code;
        code.append(1, recNode->data);
        code += ":" + output;
        writeCodes(fileName, code);
    }
    printCodes(recNode->left, output + "0", fileName);
    printCodes(recNode->right, output + "1", fileName);
}

// Building Huffman Tree
Node* tree(Heap heap)
{
    Node* parent = nullptr;
    while (heap.size > 1) {
        Node leftVal = heap.Poll();
        Node rightVal = heap.Poll();

        Node* left = new Node(leftVal.data, leftVal.freq);
        left->left = leftVal.left;
        left->right = leftVal.right;

        Node* right = new Node(rightVal.data, rightVal.freq);
        right->left = rightVal.left;
        right->right = rightVal.right;

        parent = new Node(left->freq + right->freq, left, right);
        heap.Add(*parent);
    }

    if (heap.size == 1) {
        Node rootVal = heap.Poll();
        if (parent == nullptr) {
            parent = new Node(rootVal.data, rootVal.freq);
            parent->left = rootVal.left;
            parent->right = rootVal.right;
        }
    }
    return parent;
}

// Converting binary string to decimal
int getDecimal(string input)
{
    string num = input;
    int dec_value = 0;
    int base = 1;
    int len = num.length();

    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}

// Converting binary string to ASCII characters
string stringtoASCII(string str, int& pad)
{
    pad = 0;
    if (str.length() % 8 != 0) {
        int padding = 8 - (str.length() % 8);
        pad = padding;
        for (int i = 0; i < padding; i++) {
            str += '0';
        }
    }
    string res = "";
    int N = str.length();

    for (int i = 0; i < N; i += 8) {
        int decimal_value = getDecimal(str.substr(i, 8));
        res += char(decimal_value);
    }

    return res;
}

// Reading file content into a string
string readFile(const string& fileName)
{
    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << fileName << endl;
        return "";
    }
    string content;
    file.seekg(0, ios::end);
    content.resize(file.tellg());
    file.seekg(0, ios::beg);
    file.read(&content[0], content.size());
    file.close();
    return content;
}

// Compressing input file using the generated codes
void Compress(string inputFile, string codeFile, string outputFile)
{
    ofstream codeClear(codeFile, ios::trunc);
    codeClear.close();

    string input = readFile(inputFile);
    Heap freqHeap = getFrequencies(inputFile);

    writeFreqTableFile("", freqHeap);

    Node* root = tree(freqHeap);
    printCodes(root, "", codeFile);
    ifstream code(codeFile);
    ofstream outputStream(outputFile, ios::trunc);
    string output;

    string arr[256];
    string line;
    while (getline(code, line)) {
        if (line.empty()) {
            continue;
        }

        char symbol;
        string binaryCode;

        if (line.length() >= 2 && line.at(0) == '\\') {
            char escaped = line.at(1);
            if (escaped == 'n') {
                symbol = '\n';
                binaryCode = line.substr(3);
            } else if (escaped == 't') {
                symbol = '\t';
                binaryCode = line.substr(3);
            } else if (escaped == '\\') {
                symbol = '\\';
                binaryCode = line.substr(3);
            } else {
                symbol = line.at(0);
                binaryCode = line.substr(2);
            }
        } else {
            symbol = line.at(0);
            binaryCode = line.substr(2);
        }
        arr[(unsigned char)symbol] = binaryCode;
    }

    for (int i = 0; i < input.length(); i++) {
        output += arr[input.at(i)];
    }

    cout << endl;

    int padding;
    string compressed = stringtoASCII(output, padding);
    outputStream << padding;
    outputStream << compressed;

    cout << endl;
}

// Converting decimal to binary string
string decToBinary(unsigned char n)
{
    string binary = "00000000";
    for (int i = 7; i >= 0; i--) {
        if (n % 2 == 1)
            binary[i] = '1';
        n /= 2;
    }
    return binary;
}

// Rebuild Huffman tree from code file
Node* rebuildTreeFromCodeFile(string codeFile)
{
    ifstream file(codeFile);
    Node* root = new Node();
    string line;

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        char symbol;
        string binaryCode;

        if (line.length() >= 2 && line.at(0) == '\\') {
            char escaped = line.at(1);
            if (escaped == 'n') {
                symbol = '\n';
                binaryCode = line.substr(3);
            } else if (escaped == 't') {
                symbol = '\t';
                binaryCode = line.substr(3);
            } else if (escaped == '\\') {
                symbol = '\\';
                binaryCode = line.substr(3);
            } else {
                symbol = line.at(0);
                binaryCode = line.substr(2);
            }
        } else {
            symbol = line.at(0);
            binaryCode = line.substr(2);
        }

        Node* current = root;
        for (int i = 0; i < binaryCode.length(); i++) {
            if (binaryCode[i] == '0') {
                if (current->left == nullptr) {
                    current->left = new Node();
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node();
                }
                current = current->right;
            }
        }
        current->data = symbol;
    }

    file.close();
    return root;
}

// Decompressing .com file using the Huffman Tree rebuilt from code file
void Decompress(string inputFile, string codeFile, string outputFile)
{
    Node* root = rebuildTreeFromCodeFile(codeFile);

    string input = readFile(inputFile);
    ofstream outputStream(outputFile, ios::app);

    int padding = input.at(0) - '0';
    string compressed = input.substr(1);
    string binary = "";

    for (int i = 0; i < compressed.length(); i++) {
        int num = (unsigned char)compressed[i];
        binary += decToBinary(num);
    }

    binary = binary.substr(0, binary.length() - padding);

    Node* it = root;
    for (int i = 0; i < binary.length(); i++) {
        if (binary.at(i) == '1') {
            it = it->right;
        } else {
            it = it->left;
        }

        if (it->right == nullptr && it->left == nullptr) {
            outputStream << it->data;
            it = root;
        }
    }
    outputStream.close();
}
