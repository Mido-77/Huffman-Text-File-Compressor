#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Heap.h"
#include "Node.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// Delete Huffman tree to free memory
void deleteTree(Node* node);

// Get file size
ll getFileSize(string fileName);

// Print frequency table
void writeFreqTableFile(string fileName, Heap heap);

// Write codes to file
void writeCodesBatch(string fileName, string codes[256]);

// Count character frequencies
Heap getFrequencies(string fileName);

// Generate Huffman codes from tree
void generateCodes(Node* node, string code, string codes[256]);

// Build Huffman tree
Node* tree(Heap heap);

// Convert byte to binary string
string decToBinary(unsigned char n);

// Compress a file
void Compress(string inputFile, string codeFile, string outputFile);

// Rebuild tree from code file
Node* rebuildTreeFromCodeFile(string codeFile);

// Decompress a file
void Decompress(string inputFile, string codeFile, string outputFile);

#endif // HUFFMAN_H