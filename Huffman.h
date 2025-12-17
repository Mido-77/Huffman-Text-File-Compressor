//
// Created by Ahmed Ibrahim on 16/12/2025.
//

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Heap.h"
#include "Node.h"
#include <fstream>
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
void writeFreqTableFile(const string& fileName, Heap& heap)
{
    ofstream MyFile(fileName);
    if (!MyFile.is_open())
        return;

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

    MyFile.close();
}
Heap getFrequencies(string input)
{
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
        heap.Add(Node(letter[i], freq[i]));
    }
    // writeFreqTableFile("/Users/0ne83/CLionProjects/Huffman-Text-File-Compressor/output.txt",
    // heap);
    return heap;
}

void postOrder(Node* recNode)
{
    if (recNode == nullptr)
        return;

    postOrder(recNode->left);
    postOrder(recNode->right);
    cout << recNode->data << "\t";
}

Node* tree(Heap heap)
{
    Node* parent;
    cout << heap.size << endl;
    while (heap.size > 1) {
        Node* left = heap.Poll();
        Node* right = heap.Poll();

        parent = new Node(left->freq + right->freq, left, right);
        heap.Add(*parent);
        cout << "Heap Size: " << heap.size << " " << parent->data << "-" << parent->freq << " "
             << left->data << "|" << right->data << endl;
    }
    parent = heap.Poll();

    cout << "\n" <<  parent->left->right->data   << endl;
    
    
    // postOrder(parent);
    return parent;
}

#endif // HUFFMAN_H
