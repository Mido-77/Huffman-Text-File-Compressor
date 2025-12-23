#ifndef NODE_H
#define NODE_H

// Definition of Node class
class Node {
public:
    int freq;
    char data;
    Node* left;
    Node* right;

    Node(char d = 0, int f = 0)
    {
        freq = f;
        data = d;
        left = right = nullptr;
    }
    Node(int f, Node* l, Node* r)
    {
        freq = f;
        data = 0;
        left = l;
        right = r;
    }
};
#endif // NODE_H
