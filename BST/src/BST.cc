#include "BST_utils.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
int search_array_size = 0;

void put(Node* parent, Node* entry){
    while(true){
        if(entry->score > parent->score){
            if( parent->right == nullptr){
                parent->right = entry;
                return;
            }
            else{
                put(parent->right,entry);
                 break;
            }
        }
        else{
            if(parent->left == nullptr){
                parent->left = entry;
                return;
            }
            else {
                put(parent->left,entry);
                 break;
            }
        }
    }
}
void query(Node* root,int s_min,int s_max,Node* search_array){
    int array_is_empty = 0; // Checks if array is empty. 0 for not empty.
    while(true){
        if(root->score >= s_min && root->score <= s_max){
            search_array[search_array_size] = *root;
            search_array_size++;
        }
        if(root->left != nullptr){
            query(root->left,s_min,s_max,search_array);
            break;
        }
        else if(root->right != nullptr){
            query(root->right,s_min,s_max,search_array);
            break;
        }
        else{
            break;
        }
    }
}   
void print_query(Node* search_array){
    int array_is_empty = 0; // Checks if array is empty. 0 for not empty.
    while(array_is_empty == 0){
        int i = 0;
        int max_index = 0;
        int min_index;
        for(i;i<search_array_size;i++){
            if(search_array[i].score>search_array[max_index].score){
                max_index = i;
            }
        }
        if(search_array[max_index].score == 0){
            array_is_empty = 1;
            break;
        }
        min_index = max_index;
        i = 0;
        for(i;i<search_array_size;i++){
            if(search_array[i].score< search_array[min_index].score && search_array[i].score != 0){
                min_index = i;
            }
        }

        cout << (search_array[min_index].is_home ? "H " : "A ") <<search_array[min_index].shirt_no << " "  << search_array[min_index].score << endl;
        Node newNode;
        newNode.score = 0;
        search_array[min_index] = newNode;
    }
}

int main(int argc, char** argv) {

    string path = argv[1];
    //cout << "path = " << path << endl;

    int s_min = atoi(argv[2]);
    //cout << "s_min = " << s_min << endl;

    int s_max = atoi(argv[3]);
    //cout << "s_max = " << s_max << endl;

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
    
   Node root;
    if(arr1[0][0] == "H"){
            root.is_home = true;
        }
        else{
            root.is_home = false;
        }
    root.shirt_no = std::stoi(arr1[0][1]);
    root.score = std::stoi(arr1[0][2]);
    root.left = nullptr;
    root.right = nullptr;
    print_binary_tree(root);
    cout <<endl;
    int i = 1;
    Node* bst = new Node[100];
   for(i;i<arr1.size();i++){
        if(arr1[i][0] == "H"){
            bst[i-1].is_home = true;
        }
        else{
            bst[i-1].is_home = false;
        }
        bst[i-1].shirt_no = std::stoi(arr1[i][1]);
        bst[i-1].score = std::stoi(arr1[i][2]);
        bst[i-1].left = nullptr;
        bst[i-1].right = nullptr;
       
        put(&root,&bst[i-1]);
        print_binary_tree(root);
        cout <<endl;
    }

    Node* search_array = new Node[10];
    query(&root,s_min,s_max,search_array);
    print_query(search_array);

    return 0;
}
