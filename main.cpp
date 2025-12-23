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

     while (true) {
         printf("\nMenu:\n");
         printf("1. Compress a file\n");
         printf("2. Decompress a file\n");
         printf("3. Compress a file 5 TIMES\n");
         printf("4. Exit\n");
         printf("Enter your choice: ");
         scanf("%d", &choice);
         getchar();
         if (choice == 1) // compressing
         {
             // 1-Read File
             string input = readFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.txt");
             Compress("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.txt",
                 "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.cod",
                 "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.com");
         } 
         else if (choice == 2) // decompressing
         {
             Decompress("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.com",
                 "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input.cod",
                 "/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/input2.txt", root);
         } 
         //else if (choice == 3) // recursive compressing (bonus)
         //{
    
         //} 
         else if (choice == 4) // terminate the program
         {
             return 0;
         } 
         else // re-enter a correct input
         {
             printf("You have entered a worng input");
             // go back to choices
         }
     }


    return 0;
}
