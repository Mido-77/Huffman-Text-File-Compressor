//
// Created by Ahmed Ibrahim on 16/12/2025.
//
#include "Heap.h"
#include "Huffman.h"
#include <fstream>
#include <iostream>
bool inArr() { }
int main()
{

    int choice;
    printf("   Huffman Compression/Decompression Tool\n");
    printf("===============================================\n");

    // while (true) {
    //     printf("\nMenu:\n");
    //     printf("1. Compress a file\n");
    //     printf("2. Decompress a file\n");
    //     printf("3. Compress a file 5 TIMES\n");
    //     printf("4. Exit\n");
    //     printf("Enter your choice: ");
    //     scanf("%d", &choice);
    //     getchar();
    //     if (choice == 1) // compressing
    //     {
    //
    //     } else if (choice == 2) // decompressing
    //     {
    //
    //     } else if (choice == 3) // recursive compressing (bonus)
    //     {
    //
    //     } else if (choice == 4) // terminate the program
    //     {
    //
    //     } else // re-enter a correct input
    //     {
    //         printf("You have entered a worng input");
    //         // go back to choices
    //     }
    // }

    // Compression
    // 1-Read File
    string input = readFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.txt");

    tree(getFrequencies(input));
    Compress("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.txt",
        "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.cod",
        "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.com");

    
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
