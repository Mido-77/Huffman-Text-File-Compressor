// ============================================================
// ARCHIVED CODE - Not used in current implementation
// ============================================================

#include "Huffman.h"

// void Compress(string inputFile, string codeFile, string outputFile)
// {
//     ofstream codeClear(codeFile, ios::trunc);
//     codeClear.close();
//
//     string input = readFile(inputFile);
//     Heap freqHeap = getFrequencies(inputFile);
//
//     writeFreqTableFile("", freqHeap);
//
//     Node* root = tree(freqHeap);
//     printCodes(root, "", codeFile);
//     ifstream code(codeFile);
//     ofstream outputStream(outputFile, ios::trunc);
//     string output;
//
//     string arr[256];
//     string line;
//     while (getline(code, line)) {
//         if (line.empty()) {
//             continue;
//         }
//
//         char symbol;
//         string binaryCode;
//
//         if (line.length() >= 2 && line.at(0) == '\\') {
//             char escaped = line.at(1);
//             if (escaped == 'n') {
//                 symbol = '\n';
//                 binaryCode = line.substr(3);
//             } else if (escaped == 't') {
//                 symbol = '\t';
//                 binaryCode = line.substr(3);
//             } else if (escaped == '\\') {
//                 symbol = '\\';
//                 binaryCode = line.substr(3);
//             } else {
//                 symbol = line.at(0);
//                 binaryCode = line.substr(2);
//             }
//         } else {
//             symbol = line.at(0);
//             binaryCode = line.substr(2);
//         }
//         arr[(unsigned char)symbol] = binaryCode;
//     }
//
//     for (int i = 0; i < input.length(); i++) {
//         output += arr[input.at(i)];
//     }
//
//     cout << endl;
//
//     int padding;
//     string compressed = stringtoASCII(output, padding);
//     outputStream << padding;
//     outputStream << compressed;
//
//     cout << endl;
// }

// void Decompress(string inputFile, string codeFile, string outputFile)
// {
//     Node* root = rebuildTreeFromCodeFile(codeFile);
//
//     string input = readFile(inputFile);
//     ofstream outputStream(outputFile, ios::app);
//
//     int padding = input.at(0) - '0';
//     string compressed = input.substr(1);
//     string binary = "";
//
//     for (int i = 0; i < compressed.length(); i++) {
//         int num = (unsigned char)compressed[i];
//         binary += decToBinary(num);
//     }
//
//     binary = binary.substr(0, binary.length() - padding);
//
//     Node* it = root;
//     for (int i = 0; i < binary.length(); i++) {
//         if (binary.at(i) == '1') {
//             it = it->right;
//         } else {
//             it = it->left;
//         }
//
//         if (it->right == nullptr && it->left == nullptr) {
//             outputStream << it->data;
//             it = root;
//         }
//     }
//     outputStream.close();
// }
