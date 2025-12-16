//
// Created by Ahmed Ibrahim on 16/12/2025.
//
#include <iostream>
#include "Heap.h"
#include <fstream>
#include "Huffman.h"
bool inArr()
{
    
}
int main()
{


    
    // Compression
    // 1-Read File
    string input = readFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/filename.txt");

    getFrequencies(input);

    
    //Write File
    // ofstream MyFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/filename.txt");
    // MyFile << "Hello World!\n";
    // MyFile.close();


    // Heap h;
    
    // // Insert elements
    // h.Add(1);
    // h.Add(1);
    // h.Add(3);
    // h.Add(2);
    // h.Add(1);
    // h.Add(1);
    // h.Add(1);
    //
    // std::cout << "Polling elements (Min Heap order):\n";
    //
    // int value;
    // while (h.Poll(&value))
    // {
    //     std::cout << value << " ";
    // }
    //
    // std::cout << "\n";
    //
    // // Test polling from empty heap
    // if (!h.Poll(&value))
    // {
    //     std::cout << "Heap is empty, nothing to poll.\n";
    // }

    return 0;
}