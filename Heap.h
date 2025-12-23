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

    // Helper Functions:To get the index of parent,left and right child
    int getLeftChildIndex(int parentIndex) { return 2 * parentIndex + 1; }
    int getRightChildIndex(int parentIndex) { return 2 * parentIndex + 2; }
    int getParentIndex(int childIndex) { return (childIndex - 1) / 2; };

    // Helper Functions:To check if parent,left and right child are already in the array
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

    // Helper Function:To check if there is enough space + Adjust heap otherwise
    void ensureHeapCapacity()
    {
        // if the actual size is smaller than the full capacity then there is enough space
        if (size < capacity)
            return;

        // OtherWise:
        Node* newArr = new (nothrow) Node[capacity * 2];

        if (newArr != nullptr) {
            capacity *= 2;

            for (int i = 0; i < size; i++)
                newArr[i] = arr[i];

            delete[] arr;
            arr = newArr;
        }
    }

	// Helper Function:To swap two nodes in the array
    void swap(int i1, int i2)
    {
        Node temp = arr[i1];
        arr[i1] = arr[i2];
        arr[i2] = temp;
    }

    // Helper Function:To make sure that the smallest value is always at first
    void heapifyUp()
    {
        int index = size - 1;

        while (hasParent(index) && arr[getParentIndex(index)].freq > arr[index].freq) {
            // If true,then we must swap
            swap(getParentIndex(index), index);
            index = getParentIndex(index);
        }
    }

    // Helper Function:To make sure that the new root is the right order
    void heapifyDown()
    {
        int index = 0;
        while (hasLeftChild(index)) {
            int smallestChildIndex = getLeftChildIndex(index);
            if (hasRightChild(index)
            {
                && arr[getRightChildIndex(index)].freq < arr[smallestChildIndex].freq)
                smallestChildIndex = getRightChildIndex(index);
            }
            if (arr[index].freq < arr[smallestChildIndex].freq)
            {
                break;
            }
            else {
                swap(index, smallestChildIndex);
                index = smallestChildIndex;
            }
        }
    }

	// Constructor and Destructor
    Heap()
    {
        size = 0;
        capacity = 10;
        arr = new (nothrow) Node[capacity];
    }

    ~Heap() { delete[] arr; }
    void Add(Node item)
    {
        // 1st step:we need to check if there is enough space to add a new item
        ensureHeapCapacity();

        // 2nd step:we add the new item
        arr[size] = item; // Last Index => O(1)
        size++;

        // 3rd step:we ensure that heap characteristic is done after adding the new item (Min Heap)
        heapifyUp();
    }


	// Removing and returning the minimum element from the heap
    Node* Poll()
    {
        // Check if the array is empty
        if (size == 0)
            return nullptr;

        Node* item = new Node(arr[0]);
        // We always extract the first element => O(1)

        // We assume that the last index is the new root
        arr[0] = arr[size - 1];
        size--;
        heapifyDown();
        return item;
    }
};
#endif // HEAP_H
