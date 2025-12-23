#Huffman Text File Compressor

##📌 Overview
This is a C++ implementation of a Huffman coding-based text file compression and decompression tool. It uses Huffman's algorithm to build an optimal prefix code for characters in a text file, compressing the file while maintaining lossless reconstruction.

##🚀 Features
- Compression: Converts text files into compressed binary format (.com)

- Decompression: Reconstructs original text from compressed files

- Frequency Analysis: Displays character frequencies in the terminal

- Code Generation: Creates a code mapping file (.cod) for Huffman codes

- Menu-Driven Interface: User-friendly command-line interface

##📁 Project Structure
Huffman-Text-File-Compressor/
├── CMakeLists.txt
├── main.cpp
├── Huffman.h
├── Heap.h
├── Node.h
├── input.txt          # Example input file
├── input.cod          # Generated Huffman codes
├── input.com          # Compressed output
├── input2.txt         # Decompressed output
└── README.md


##🔧 Requirements
- C++14 or higher
- CMake 3.29 or higher
- Standard C++ libraries

##🛠️ Installation & Compilation
Using CMake:

mkdir build
cd build
cmake ..
make

Direct Compilation:
g++ -std=c++14 main.cpp -o HuffmanCompressor

##📖 Usage
Running the Program:
./Huffman_Text_File_Compressor



##Program Menu:

Huffman Compression/Decompression Tool
===============================================

Menu:
1. Compress a file
2. Decompress a file
3. Compress a file 5 TIMES (Bonus - currently commented)
4. Exit


##Input/Output Files:
###Input Files:
- input.txt: The text file to compress
Example content: Huffman-Text-File-Compressor\nlinks:\n

###Generated Files:
- input.cod: Huffman code mapping:
o:0000
H:00010
u:00011
r:0010
::00110
... (character:binary_code pairs)


- input.com: Compressed binary file
Contains padding information + ASCII-encoded binary data
Example: 6êžw°õ/X™úÐx—÷bYø€

- input2.txt: Decompressed output (should match original)


##🔄 How It Works
1. Frequency Analysis
- Reads input file character by character
- Counts frequency of each character
- Builds frequency table displayed in terminal

2. Huffman Tree Construction
- Creates a min-heap of character nodes
- Repeatedly merges two lowest frequency nodes
- Builds binary tree where left=0, right=1

3. Code Generation
- Traverses tree to assign binary codes to characters
- Stores mapping in .cod file
- Shorter codes for frequent characters, longer for rare ones

4. Compression
- Replaces each character with its Huffman code
- Converts binary string to 8-bit ASCII characters
- Adds padding information at start of .com file

5. Decompression
- Reads padding and compressed data
- Converts back to binary string
- Traverses Huffman tree using binary codes to reconstruct text

##📊 Key Components
1. Heap.h (Min-Heap Implementation)
- Dynamic array-based min-heap
- Supports Add() and Poll() operations
- Automatic capacity expansion
- Heapify operations for maintaining heap property

2. Node.h (Huffman Tree Node)
class Node {
    int freq;      // Character frequency
    char data;     // Character (0 for internal nodes)
    Node* left;    // Left child (0 bit)
    Node* right;   // Right child (1 bit)
};






