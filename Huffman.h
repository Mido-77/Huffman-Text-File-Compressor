#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Heap.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

// Reading file content
string readFile(string fileName)
{
    string input = "";
    ifstream MyReadFile(fileName);
    char ch;
    while (MyReadFile.get(ch)) {
        input += ch;
    }
    MyReadFile.close();
    return input;
}


// Printing frequency table in terminal
void writeFreqTableFile(const string& fileName, Heap& heap)
{
   /* ofstream MyFile(fileName);
    if (!MyFile.is_open())
        return;*/
    
    Node* value;
    while ((value = heap.Poll()) != nullptr) {

        if (value->data == '\n') {
            MyFile << "\\n | " << value->freq << endl;
            cout << "\\n | " << value->freq << endl;

        } else if (value->data == '\t') {
            MyFile << "\\t | " << value->freq << endl;
            cout << "\\t | " << value->freq << endl;

        } else if (value->data == ' ') {
            MyFile << "SPACE | " << value->freq << endl;
            cout << "SPACE | " << value->freq << endl;

        } else {
            MyFile << value->data << " | " << value->freq << endl;
            cout << value->data << " | " << value->freq << endl;
        }
    }

    //MyFile.close();
}

// Writing codes to .cod file
void writeCodes(const string& fileName, string code)
{
    ofstream MyFile(fileName, ios::app);
    MyFile << code << "\n";
    MyFile.close();
}


// Getting frequencies of each character in the input string
Heap getFrequencies(string input)
{
	// Arrays to store unique characters and their frequencies
    int size = 0;
    int freq[256] = { 0 };
    char letter[256];
    for (int i = 0; i < input.length(); i++) {
        bool found = false;
        for (int k = 0; k < size; k++) {
            if (input[i] == letter[k]) {
                found = true;
                break;
            }
        }
		// If character not found, add it to the array
        if (!found) {
            letter[size] = input[i];
            freq[size] = 1;
            for (int j = i + 1; j < input.length(); j++) {
                if (letter[size] == input[j]) {
                    freq[size]++;
                }
            }
            size++;
        }
    }
	// Creating a min-heap to store characters and their frequencies
    Heap heap;
    cout << "Frequencies:" << endl;
    for (int i = 0; i < size; i++) {
        heap.Add(Node(letter[i], freq[i]));
        cout << letter[i] << " : " << freq[i] << endl;
    }

    return heap;
}

// Generating Huffman Codes by traversing the tree (pre-order)
void printCodes(Node* recNode, string output)
{
    if (recNode == nullptr)
        return;
    if (recNode->data != '\0') {
        string code;
        code.append(1, recNode->data);
        code += ":" + output;
        writeCodes("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.cod", code); 
    }
    printCodes(recNode->left, output + "0");
    printCodes(recNode->right, output + "1");
}

// Building Huffman Tree
Node* tree(Heap heap)
{
    Node* parent;
    while (heap.size > 1) {
        Node* left = heap.Poll();
        Node* right = heap.Poll();
        parent = new Node(left->freq + right->freq, left, right);
        heap.Add(*parent);
    }

	// The last remaining node is the root of the Huffman Tree
    parent = heap.Poll();
    printCodes(parent, "");
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
	// Padding the string to make its length a multiple of 8
    if (str.length() % 8 != 0) {
        int padding = 8 - (str.length() % 8);
        pad = padding;
        for (int i = 0; i < padding; i++) {
            str += '0';
        }
    }
	// Convert every 8 bits to its corresponding ASCII character
    string res = "";
    int N = str.length();

    for (int i = 0; i < N; i += 8) {
        int decimal_value = getDecimal(str.substr(i, 8));
        res += char(decimal_value);
    }
     
    return res;
}


// Compressing input file using the generated codes
void Compress(string inputFile, string codeFile, string outputFile)
{
	// read input file
    string input =  readFile(inputFile);
    ifstream code(codeFile);
    ofstream outputStream(outputFile, ios::app);
    string output;

    // parse code file and save to ascii array
    string arr[256];
    string line;
    while (getline(code, line)) {
        if (line.empty()) {
			continue;
        }

        char symbol = line.at(0);        // before ':'
        string code = line.substr(2); // after "x:"
        arr[symbol] = code;
    }

    // get binary output
    for (int i = 0; i < input.length(); i++) {
        output += arr[input.at(i)];
    }

    cout << endl;

    // get decimal output and write to .com
    int padding;
    string compressed = stringtoASCII(output, padding);
    outputStream << padding;
    outputStream << compressed;

    cout << endl;
}

// Converting decimal to binary string
string decToBinary(unsigned char n)
{
    string binary = "00000000";  // pre-fill 8 zeros
    for (int i = 7; i >= 0; i--)
    {
        if (n % 2 == 1)
            binary[i] = '1';
        n /= 2;
    }
    return binary;
}


// Decompressing .com file using the Huffman Tree
void Decompress(string inputFile, string codeFile, string outputFile, Node* root)
{
	// read input file
    string input =  readFile(inputFile);
    ifstream code(codeFile);
    ofstream outputStream(outputFile, ios::app);
    string output;
    
    int padding = input.at(0) - '0';
    string compressed = input.substr(1);
    string binary = "";

	// convert compressed string to binary string
    for (int i = 0; i < compressed.length(); i++) {
        int num = (unsigned char)compressed[i];
        binary += decToBinary(num);
    }

    binary = binary.substr(0,binary.length()-padding);

    // traverse the tree according to the binary string
    Node* it = root;
    for (int i=0; i<binary.length() ; i++) {
        if (binary.at(i) == '1') {
            it = it->right;
        }
        else {
            it = it->left;
        }

        if (it->right == nullptr && it->left == nullptr) {
            outputStream << it->data;
            it = root; 
        }
    }
}


#endif // HUFFMAN_H