#ifndef HEAP_H
#define HEAP_H
#include "Node.h"
#include <iostream>
#include <new>

using namespace std;

// Definition of Heap (Min-Heap) class
class Heap {
public:
    Node* arr;
    int size; // Actual size of the dynamic array
    int capacity; // Max size of the dynamic array

    // Helper Functions to get the index of parent, left and right child
    int getLeftChildIndex(int parentIndex) { return 2 * parentIndex + 1; }
    int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 2; }
    int getParentIndex(int childIndex) { return (childIndex - 1) / 2; };

    // Helper Functions to check if parent, left and right child are already in the array
    bool hasLeftChild(int parentIndex)
    {
        if (getLeftChildIndex(parentIndex) < size)
            return true;
        return false;
    }

    bool hasRightChild(int parentIndex)
    {
        if (getRightChildIndex(parentIndex) < size)
            return true;
        return false;
    }
    bool hasParent(int childIndex)
    {
        if (getParentIndex(childIndex) >= 0)
            return true;
        return false;
    }

    // Helper Function to check if there is enough space + Adjust heap otherwise
    void ensureHeapCapacity()
    {
        if (size < capacity)
            return;

        Node* newArr = new (nothrow) Node[capacity * 2];

        if (newArr != nullptr) {
            capacity *= 2;

            for (int i = 0; i < size; i++)
                newArr[i] = arr[i];

            delete[] arr;
            arr = newArr;
        }
    }

    // Helper Function to swap two nodes in the array
    void swap(int i1, int i2)
    {
        Node temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }

    // Helper Function to make sure that the smallest value is always at first
    void heapifyUp()
    {
        int index = size - 1;

        while (hasParent(index) && arr[getParentIndex(index)].freq > arr[index].freq) {
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }

    // Helper Function to make sure that the new root is the right order
    void heapifyDown()
    {
        int index = 0;
        while (hasLeftChild(index)) {
            int smallestChildIndex = getLeftChildIndex(index);
            if (hasRightChild(index)
                && arr[getRightChildIndex(index)].freq < arr[smallestChildIndex].freq) {
                smallestChildIndex = getRightChildIndex(index);
            }
            if (arr[index].freq < arr[smallestChildIndex].freq) {
                break;
            } else {
                swap(index, smallestChildIndex);
                index = smallestChildIndex;
            }
        }
    }

    // Constructor
    Heap()
    {
        size = 0;
        capacity = 10;
        arr = new (nothrow) Node[capacity];
    }

    ~Heap() { delete[] arr; }

    Heap(const Heap& other)
    {
        size = other.size;
        capacity = other.capacity;
        arr = new (nothrow) Node[capacity];
        if (arr != nullptr) {
            for (int i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }
    }

    Heap& operator=(const Heap& other)
    {
        if (this != &other) {
            delete[] arr;

            size = other.size;
            capacity = other.capacity;
            arr = new (nothrow) Node[capacity];
            if (arr != nullptr) {
                for (int i = 0; i < size; i++) {
                    arr[i] = other.arr[i];
                }
            }
        }
        return *this;
    }
    // Adds a new item to the heap
    void Add(Node item)
    {
        ensureHeapCapacity();

        arr[size] = item;
        size++;

        heapifyUp();
    }

    // Removing and returning the minimum element from the heap
    Node Poll()
    {
        if (size == 0)
            return Node('\0', (ll)-1); // Return sentinel value indicating empty

        Node item = arr[0];
        arr[0] = arr[size - 1];
        size--;
        heapifyDown();
        return item;
    }
};
#endif // HEAP_H
