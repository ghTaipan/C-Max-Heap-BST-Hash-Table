#include "exercise1_utils.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>


using namespace std;

int heap_size = 0;

// Your heap functions can (but don't have to) be in these forms:
Node* create_heap(int capacity){
    Node* heap = new Node[capacity];
    return heap;
}
void push(Node* heap, Node entry){
    Node tempNode ;
    int index = heap_size;
    heap[index] = entry;
    int i ;
    while(true){
        if(index == 0){
            heap[index] = entry;
            break;
        }
        if(index%2 == 1){
            
            i = (index-1)/2;
        }
        else{
            i = (index-2)/2;
        }
        if(heap[index].score>heap[i].score){
            tempNode = heap[i];
            heap[i] = heap[index];
            heap[index] = tempNode;
            if(i == 0){break;}
            else{index = i;}
        }
        else{break;}
    }
    heap_size++;
}
Node pop(Node* heap){
    if(heap_size == 0){
        cout << "Size of the heap is 0. Pop function can not be done!" << endl;
        Node returnEmptyNode;
        return returnEmptyNode;
    }
    Node tempNode = heap[0];
    Node tempNode2;
    tempNode2.score = 0;
    heap[0] = heap[heap_size-1];
    heap[heap_size-1] = tempNode2;
    heap_size--;
    if(heap_size == 0){
            cout << (tempNode.is_home ? "H":"A") <<" "<< tempNode.shirt_no<<" "<< tempNode.score << endl;
            return tempNode;
        }
    int index = 0;
    while(true){
        if(heap[2*index+1].score >= heap[2*index+2].score && heap[2*index+1].score > heap[index].score){
            tempNode2 = heap[index];
            heap[index] = heap[2*index+1];
            heap[2*index+1] = tempNode2;
            index = 2*index+1;
            if(2*index+1 >heap_size-1){break;}
        }
        else if(heap[2*index+2].score > heap[2*index+1].score && heap[2*index+2].score > heap[index].score){
            tempNode2 = heap[index];
            heap[index] = heap[2*index+2];
            heap[2*index+2] = tempNode2;
            index = 2*index+2;
            if(2*index+1 >heap_size-1){break;}
        }
        else{
            cout << (tempNode.is_home ? "H" : "A") << " "<< tempNode.shirt_no<<" "<< tempNode.score << endl;
            return tempNode;
        }

    }
    cout << (tempNode.is_home ? "H":"A") <<" "<< tempNode.shirt_no<<" "<< tempNode.score << endl;
    return tempNode;
}


int main(int argc, char** argv) {

    string path = argv[1];
    // cout << "path = " << path << endl;

    int k = atoi(argv[2]);
    cout << "k = " << k << endl;
    vector<string> arr;
    vector<vector<string>> arr1;
    string h_a;
    string shirt_number;
    string score;


    ifstream myFile;
    myFile.open(path);
    while(getline(myFile, h_a, ',')){
        if(h_a == "\n"){
            break;
        }
        getline(myFile, shirt_number, ',');
        getline(myFile, score, '\n');
        arr.push_back(h_a);
        arr.push_back(shirt_number);
        arr.push_back(score);
        arr1.push_back(arr);
        arr.clear();
    }
    arr1.erase(arr1.begin());

    // Do this:
    // (1) Construct the heap using the file.
    // (2) Display top k players.

    // This is a simple demo for displaying a heap using dummy data entered manually
    // rather than reading the actual CSV file and relying on heap operations.
    // You code will be completely different!
    


    int heap_capacity = 10; 
    //Node* heap = new Node[heap_capacity];
    
    int i = 0;
    Node* heap = create_heap(heap_capacity);
    for(i;i<arr1.size();i++){
        Node entry;
        if(arr1[i][0] == "H"){
            entry.is_home = true;
        }
        else{
            entry.is_home = false;
        }
        entry.shirt_no = std::stoi(arr1[i][1]);
        entry.score = std::stoi(arr1[i][2]);
        push(heap,entry);
        print_complete_binary_tree(heap, heap_size);
    }
    i = 0;
   
    for(i;i<k;i++){
        pop(heap);
    }
    return 0;
}
