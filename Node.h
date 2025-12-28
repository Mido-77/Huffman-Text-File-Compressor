#ifndef NODE_H
#define NODE_H

#define ll unsigned long long 

// Definition of Node class
class Node {
public:
    ll freq;
    char data;
    Node* left;
    Node* right;

	// Constructor for leaf nodes
    Node(char d = 0, ll f = 0)
    {
        freq = f;
        data = d;
        left = right = nullptr;
    }

	// Constructor for internal nodes
    Node(ll f, Node* l, Node* r)
    {
        freq = f;
        data = 0;
        left = l;
        right = r;
    }
};
#endif // NODE_H
