cmake_minimum_required(VERSION 3.29)
project(Huffman_Text_File_Compressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Huffman_Text_File_Compressor
    main.cpp
        Heap.h
        Huffman.h
        Node.h)
