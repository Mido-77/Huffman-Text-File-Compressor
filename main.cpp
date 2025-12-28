#include "Huffman.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Maximum file size allowed (4GB)
ll MAX_FILE_SIZE = 4ULL * 1024 * 1024 * 1024;

// Helper to get file size
ll checkFileSize(string filename)
{
    ifstream file(filename, ios::binary | ios::ate);
    if (!file.is_open())
        return -1;
    ll size = file.tellg();
    file.close();
    return size;
}

// Helper to get base filename without extension
string removeExtension(string filename)
{
    int dotPos = -1;
    for (int i = filename.length() - 1; i >= 0; i--) {
        if (filename[i] == '.') {
            dotPos = i;
            break;
        }
    }
    if (dotPos == -1)
        return filename;
    return filename.substr(0, dotPos);
}

int main()
{
    int choice;
    string filename, codeFile, compressedFile;

    cout << "   Huffman Compression/Decompression Tool" << endl;
    cout << "=============================================" << endl;

    
    while (true) {
        cout << endl;
        cout << "Menu:" << endl;
        cout << "1. Compress a file" << endl;
        cout << "2. Decompress a file" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter choice: ";

        cin >> choice;
        
        if (choice == 1) {
            cout << "Enter filename to compress (.txt): ";
            cin >> filename;

            // Check if file exists and size
            ll fileSize = checkFileSize(filename);
            if (fileSize == -1) {
                cout << "Error: Cannot open file" << endl;
                continue;
            }
            if (fileSize == 0) {
                cout << "Error: File is empty" << endl;
                continue;
            }
            if (fileSize > MAX_FILE_SIZE) {
                cout << "Error: File too large (max 4GB)" << endl;
                continue;
            }

            // Create output filenames
            string baseName = removeExtension(filename);
            codeFile = baseName + ".cod";
            compressedFile = baseName + ".com";

            cout << "Compressing..." << endl;
            Compress(filename, codeFile, compressedFile);
            cout << "Created: " << codeFile << ", " << compressedFile << endl;

        } 
     
        else if (choice == 2) {
            cout << "Enter compressed file (.com): ";
            cin >> compressedFile;

            cout << "Enter code file (.cod): ";
            cin >> codeFile;

            cout << "Enter output filename (.txt): ";
            string outputFile;
            cin >> outputFile;

            cout << "Decompressing..." << endl;
            Decompress(compressedFile, codeFile, outputFile);
            cout << "Created: " << outputFile << endl;

        } 
        else if (choice == 3) {
            return 0;
        }
        else {
            cout << "Invalid choice" << endl;
        }
    }

    return 0;
}
