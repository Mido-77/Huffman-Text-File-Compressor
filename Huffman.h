#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Heap.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Printing frequency table in terminal
void writeFreqTableFile(const string& fileName, Heap heap);

// Writing codes to .cod file
void writeCodes(const string& fileName, string code);

// Getting frequencies of each character from the input file (Streaming)
Heap getFrequencies(const string& fileName);

// Generating Huffman Codes by traversing the tree (pre-order)
void printCodes(Node* recNode, string output, string fileName);

// Building Huffman Tree
Node* tree(Heap heap);

// Converting binary string to decimal
int getDecimal(string input);

// Converting binary string to ASCII characters
string stringtoASCII(string str, int& pad);

// Compressing input file using the generated codes
void Compress(string inputFile, string codeFile, string outputFile);

// Converting decimal to binary string
string decToBinary(unsigned char n);

// Rebuild Huffman tree from code file
Node* rebuildTreeFromCodeFile(string codeFile);

// Decompressing .com file using the Huffman Tree rebuilt from code file
void Decompress(string inputFile, string codeFile, string outputFile);

#endif // HUFFMAN_H