# Huffman Text File Compressor
https://github.com/Mido-77/Huffman-Text-File-Compressor.git

## 📌 Overview
A C++ implementation of Huffman coding for text file compression and decompression.


## 📚 Our Development Story
### 🧠 Starting with the Basics
We began by truly understanding Huffman coding from the ground up. What compression and decompression actually mean. Instead of jumping straight to coding, we spent time drawing trees on paper, calculating how many bytes we'd save, and figuring out how variable-length codes work. We visualized the whole process: counting characters, building the tree, generating codes, and packing bits. It was all about understanding the "why" before the "how.". This paper planning helped us see the big picture before writing a single line of code.

### 👥 Teamwork Strategy
With two of us working together, we had to decide our approach. Should one person handle compression and the other decompression? Instead of splitting tasks (like one does compression, one does decompression), we decided to work through everything together. We made a rule: brainstorm together, code together, and debug together.Whether meeting in person or sharing screens online, we learned from each other's problem-solving approaches.

### 🤖 Our Approach to AI Assistance
We intentionally limited our use of AI throughout the project. When we got stuck, our first step was always trying to solve it ourselves. Only if we were really stuck would we search online for specific solutions or use AI for debugging hints. We wanted this to be our own work, not just copied code. According to AI checkers, our final code is about 70-80% human-written and 20-30% AI-assisted.

### 🐛 The Debugging Journey
Debugging took more time than we expected! The real learning happened during debugging. We encountered memory leaks (forgetting to delete nodes), decompression errors (getting gibberish instead of our original text), code file format issues (special characters breaking things), and bit ordering problems. Each bug was a puzzle we had to solve together, adding debug prints and tracing through the code step by step until we found the issue.

### 💻 Cross-Platform Challenges Turned Strengths
An interesting twist in our project was that one of us uses Windows and the other uses macOS. This turned out to be a hidden strength! Sometimes code would work perfectly on one computer but crash on the other. We had to make sure everything worked smoothly on both systems, which forced us to write more robust and platform-independent code.  No "it works on my machine" excuses allowed!

### 🎯 Where We Are & Future Possibilities
Our program works reliably now, compressing and decompressing files correctly. But like any project, there's room for improvement. Given more time, we'd love to add more compression algorithms for comparison, improve the user interface, implement multi-threading for larger files, and create clearer error messages. For now, we're proud of taking an algorithm from theoretical understanding to a working implementation through collaboration, problem-solving, and plenty of debugging.

### Final Thoughts
This project taught us more than just Huffman coding. We learned about teamwork, problem-solving, and turning theoretical concepts into practical applications. It was challenging but incredibly rewarding to see our ideas become a working program that can actually compress and decompress files!


## Inspiration & Resources
These are the links and resources that inspired and helped us build this project:
- lectures codes
- https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/
- https://www.w3schools.com/dsa/dsa_ref_huffman_coding.php
- https://brilliant.org/wiki/huffman-encoding/
- https://www.youtube.com/watch?v=co4_ahEDCho
- https://www.cs.cmu.edu/~guyb/realworld/compression.pdf


## 🛠️ Implementation Process
1. Frequency Analysis
2. Heap Construction
3. Huffman Tree Building
4. Code Generation
5. Compression
6. Decompression

## 🚀 Usage
Compress: input.txt → input.cod + input.com

Decompress: input.com + input.cod → output.txt
