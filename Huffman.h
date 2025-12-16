//
// Created by Ahmed Ibrahim on 16/12/2025.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <fstream>
#include "Heap.h"
#include "Node.h"
#include <iostream>
using namespace std;



string readFile(string fileName)
{
    string input = "";
    ifstream MyReadFile(fileName);
    char ch;
    while (MyReadFile.get(ch)) {
        input += ch;
    }
    cout << input << endl;
    MyReadFile.close();
    return input;
}
void writeFile(string fileName, Heap& heap)
{
    ofstream MyFile(fileName);
    Node value;
    while (heap.Poll(&value))
    {
        if (value.data == '\n') {
            MyFile << "\\n | " << value.freq << endl;
            cout << "\\n | " << value.freq << endl;
        } else if (value.data == '\t') {
            MyFile << "\\t | " << value.freq << endl;
            cout << "\\t | " << value.freq << endl;
        } else if (value.data == ' ') {
            MyFile << "SPACE | " << value.freq << endl;
            cout << "SPACE | " << value.freq << endl;
        } else {
            MyFile << value.data << " | " << value.freq << endl;
            cout << value.data << " | " << value.freq << endl;
        }
    }
    MyFile.close();
}
Heap getFrequencies(string input)
{
    int size = 0;
    int freq[256] = {0};
    char letter[256];
    for (int i = 0; i < input.length(); i++) {
        bool found = false;
        for (int k = 0; k < size; k++) {
            if (input[i] == letter[k]) {
                found = true;
                break;
            }
        }
        if (!found) {
            letter[size] = input[i];
            freq[size] = 1;
            for ( int j = i+1; j < input.length(); j++ ) {
                if (letter[size] == input[j]) {
                    freq[size]++;
                }
            }
            size++;
        }
    }

    // for (int i = 0; i < size; i++) {
    //     if (letter[i] == '\n') {
    //         cout << "\\n | " << freq[i] << endl;
    //     } else if (letter[i] == '\t') {
    //         cout << "\\t | " << freq[i] << endl;
    //     } else if (letter[i] == ' ') {
    //         cout << "SPACE | " << freq[i] << endl;
    //     } else {
    //         cout << letter[i] << " | " << freq[i] << endl;
    //     }
    // }

    Heap heap;

    for (int i = 0; i < size; i++) {
        Node* n = new Node(letter[i], freq[i]);
        heap.Add(*n);
        delete n;
    }
    return heap;
    writeFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/output.txt", heap);
    
}

Node* tree(Heap heap)
{
    for (int i = 0; i < heap.size(); i+=2) {
        int f = heap.arr[i].freq + heap.arr[i+1].freq;
        Node* parent = new Node(f, &heap.arr[i], &heap.arr[i+1]);
        
    }
}



#endif //HUFFMAN_H
