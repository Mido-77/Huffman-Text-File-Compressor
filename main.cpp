#include "Huffman.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
    int choice;
    string filename, codeFile, compressedFile;

    cout << "   Huffman Compression/Decompression Tool" << endl;
    cout << "===============================================" << endl;
    while (true) {
        cout << "\nMenu:" << endl;
        cout << "1. Compress a file" << endl;
        cout << "2. Decompress a file" << endl;
        cout << "3. Compress a file 5 TIMES (Recursive)" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) // compressing
        {
            cout << "Enter filename to compress (e.g., input.txt): ";
            cin >> filename;
            codeFile = filename + ".cod";
            compressedFile = filename + ".com";

            cout << "Compressing " << filename << "..." << endl;
            Compress(filename, codeFile, compressedFile);
            cout << "Done! Created: " << codeFile << ", " << compressedFile << endl;
        } else if (choice == 2) // decompressing
        {
            cout << "Enter filename to decompress (e.g., input.txt.com): ";
            cin >> compressedFile;

            cout << "Enter code file name (e.g., input.txt.cod): ";
            cin >> codeFile;

            cout << "Enter output filename (e.g., input_restored.txt): ";
            string outputFile;
            cin >> outputFile;

            cout << "Decompressing..." << endl;
            Decompress(compressedFile, codeFile, outputFile);
            cout << "Done! Created: " << outputFile << endl;
        } else if (choice == 4) // terminate the program
        {
            return 0;
        } else {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
