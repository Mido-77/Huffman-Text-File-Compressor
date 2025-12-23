# Huffman Text File Compressor

## 📌 Overview
This is a C++ implementation of a Huffman coding-based text file compression and decompression tool. It uses Huffman's algorithm to build an optimal prefix code for characters in a text file, compressing the file while maintaining lossless reconstruction.

## 🚀 Features
- Compression: Converts text files into compressed binary format (.com)

- Decompression: Reconstructs original text from compressed files

- Frequency Analysis: Displays character frequencies in the terminal

- Code Generation: Creates a code mapping file (.cod) for Huffman codes

- Menu-Driven Interface: User-friendly command-line interface

## 📁 Project Structure

<pre>
Huffman-Text-File-Compressor/
├── CMakeLists.txt
├── main.cpp
├── Huffman.h
├── Heap.h
├── Node.h
├── input.txt # Example input file
├── input.cod # Generated Huffman codes
├── input.com # Compressed output
├── input2.txt # Decompressed output
└── README.md
</pre>



## 🔧 Requirements
- C++14 or higher
- CMake 3.29 or higher
- Standard C++ libraries

## 🛠️ Installation & Compilation
Using CMake:
<pre>
mkdir build
cd build
cmake ..
make
</pre>

Direct Compilation:
<pre>
g++ -std=c++14 main.cpp -o HuffmanCompressor
</pre>

## 📖 Usage
Running the Program:
<pre>
./Huffman_Text_File_Compressor
</pre>


## Program Menu:
<pre>
Huffman Compression/Decompression Tool
===============================================

Menu:
1. Compress a file
2. Decompress a file
3. Compress a file 5 TIMES (Bonus - currently commented)
4. Exit
</pre>

## Input/Output Files:
### Input Files:
- input.txt: The text file to compress
Example content: Huffman-Text-File-Compressor\nlinks:\n

### Generated Files:
- input.cod: Huffman code mapping:
<pre>
o:0000
H:00010
u:00011
r:0010
::00110
... (character:binary_code pairs)
</pre>

- input.com: Compressed binary file
Contains padding information + ASCII-encoded binary data
Example: 6êžw°õ/X™úÐx—÷bYø€

- input2.txt: Decompressed output (should match original)


## 🔄 How It Works
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

## 📊 Key Components
1. Heap.h (Min-Heap Implementation)
- Dynamic array-based min-heap
- Supports Add() and Poll() operations
- Automatic capacity expansion
- Heapify operations for maintaining heap property

2. Node.h (Huffman Tree Node)
```cpp
class Node {
    int freq;      // Character frequency
    char data;     // Character (0 for internal nodes)
    Node* left;    // Left child (0 bit)
    Node* right;   // Right child (1 bit)
};
```

4. Huffman.h (Core Algorithms)
- getFrequencies(): Builds character frequency table
- tree(): Constructs Huffman tree
- Compress(): Performs file compression
- Decompress(): Performs file decompression
- printCodes(): Generates code mapping

## 📝 Example Workflow
1. Compression:
- Read input.txt → "Huffman-Text-File-Compressor\nlinks:\n"
- Calculate frequencies → H:1, u:1, f:2, ...
- Build Huffman tree
- Generate codes → H=00010, u=00011, ...
- Encode text → 000100001100101...
- Convert to ASCII, add padding → 6êžw°õ/X™úÐx—÷bYø€
- Save to input.com

2. Decompression:
- Read input.com → extract padding and data
- Convert ASCII to binary string
- Remove padding zeros
- Use input.cod mapping to decode binary
- Reconstruct original text → "Huffman-Text-File-Compressor\nlinks:\n"

## ⚠️ Current Limitations & Issues
1. Fixed File Paths
The code uses hardcoded absolute paths:
<pre>
"/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.txt"
</pre>
Solution: Should use relative paths or command-line arguments

3. Memory Leaks
The Poll() function in Heap.h creates a new Node but doesn't track deletion:
<pre>
Node* Poll() {
    Node* item = new Node(arr[0]);  // Memory allocated
    return item;  // Caller must delete
}
</pre>

4. Character Range Limitation
- Uses 256-sized arrays assuming ASCII
- May not handle extended character sets

4. Code File Dependency
- Decompression requires the .cod file
- Not self-contained like many compressors
- Could embed tree structure in compressed file

5. Unused Function
writeFreqTableFile() has commented-out file writing code

## 🔮 Future Improvements
- Command-line arguments: ./compressor -c input.txt output.com
- Binary file support: Extend beyond text files
- Embed tree in compressed file: Eliminate .cod dependency
- Progress indicators: Show compression ratio
- Stream processing: Handle large files without loading entire file
- Multi-threading: Parallel frequency counting and encoding

## 📊 Compression Performance
- Compression ratio depends on input file entropy
- Best for text with repeated characters
- Overhead: Padding byte + code mapping file
- Example: Small files may not compress well due to overhead

## 🤝 Contributing
- Fork the repository
- Create a feature branch
- Implement improvements
- Test thoroughly
- Submit pull request

## 📄 License
This project is for educational purposes. Modify and distribute as needed.

## 🎓 Educational Value
This implementation demonstrates:
- Huffman coding algorithm
- Binary tree construction and traversal
- Heap data structure
- Bit manipulation
- File I/O operations
- Lossless compression principles

## 💡 Tips for Use
- Test with files >1KB for meaningful compression
- Compare file sizes: ls -lh input.txt input.com
- Verify decompression: diff input.txt input2.txt
- Try different text types (code, prose, repetitive data)



