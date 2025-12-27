cmake_minimum_required(VERSION 3.29)
project(Huffman_Text_File_Compressor)

set(CMAKE_CXX_STANDARD 14)

add_executable(Huffman_Text_File_Compressor
    main.cpp
    Huffman.cpp
        Heap.h
        Huffman.h
        Node.h)
set_target_properties(Huffman_Text_File_Compressor PROPERTIES
        VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)