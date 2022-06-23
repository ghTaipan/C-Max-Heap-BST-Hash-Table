#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int minute;
    string team; 
    int shirt_no;
    string event_code;
    int goals = 0;
    int assists = 0;
    int score = 0;
};

Node hash_table[28];

string repeat(int n,string text){
    int i = 0;
    string s;
    for(i;i<n;i++){
        s = s + text;
    }
    return s;
}

int hashing(Node player){
    if ( player.team == "H"){
        return (player.shirt_no) % 28;
    }
    else{
        return (99+player.shirt_no) % 28;
    }
}
int put(Node player){
    
    int index = hashing(player);
    if(hash_table[index].shirt_no == 0){
        hash_table[index] = player;
        return 1;
    }
    else{
        int shifting = 0;
        while(hash_table[index+shifting*shifting].shirt_no != 0){
            if(hash_table[index+shifting*shifting].shirt_no == player.shirt_no && hash_table[index+shifting*shifting].team == player.team){break;}
            shifting++;
            if(shifting >9){
                    return 0;
                }
        }
        if(hash_table[index+shifting*shifting].shirt_no == player.shirt_no && hash_table[index+shifting*shifting].team == player.team){
            hash_table[index+shifting*shifting].assists = hash_table[index+shifting*shifting].assists + player.assists;
            hash_table[index+shifting*shifting].goals = hash_table[index+shifting*shifting].goals + player.goals;
             hash_table[index+shifting*shifting].score = hash_table[index+shifting*shifting].score + player.score;
        }
        else{
            hash_table[index+shifting*shifting] = player;
        }
    }
    
    return 0;
}
void print_table(){
    int i = 0;
    cout<<"Index Team No Goals Assists Score"<<endl;
    string xD = to_string(hash_table[0].shirt_no);

    for(i;i<28;i++){
        std::cout<< i; 
        if(hash_table[i].shirt_no != 0){
            string str_index = to_string(i);
            string str_shirt_no= to_string(hash_table[i].shirt_no);
            string str_goals= to_string(hash_table[i].goals);
            string str_assists= to_string(hash_table[i].assists);
            std::cout << repeat(6-str_index.length()," ") << hash_table[i].team << repeat(4," ")
                << hash_table[i].shirt_no << repeat(3-str_shirt_no.length()," ")  << hash_table[i].goals << repeat(6-str_goals.length()," ") 
                    << hash_table[i].assists << repeat(8-str_assists.length()," ")<< hash_table[i].score << std:: endl;
        }
        else{
            std::cout << endl; 
        }
    }
}

int main(int argc, char** argv) {

    string path = argv[1];
    //cout << "path = " << path << endl;

    int min = atoi(argv[2]);
    //cout << "s_min = " << min << endl;
    // This time no utility functions are provided.

    // Do not forget to parse the command line argument.

    // Consider defining 
    // Key as a struct or a class that contains two fields: team and shirt number, and
    // Value as a struct or a class that contains three fields: goals, assists and score.
    // The hash table is an array of 28 such (Key, Value) pairs.

    vector<string> arr;
    vector<vector<string>> arr1;
    string minute;
    string team;
    string shirtno;
    string event_code;  
    ifstream myFile;
    myFile.open(path);
    while(getline(myFile, minute, ',')){
        if(minute == "\n"){
            break;
        }
        getline(myFile, team, ',');
        getline(myFile, shirtno, ',');
        getline(myFile, event_code, '\n');
        arr.push_back(minute);
        arr.push_back(team);
        arr.push_back(shirtno);
        arr.push_back(event_code);
        arr1.push_back(arr);
        arr.clear();
    }
    arr1.erase(arr1.begin());

    for(int i = 0;i<arr1.size();i++){
        Node entry;
        entry.minute = std::stoi(arr1[i][0]);
        if(entry.minute>min){
            break;
        }
        entry.team = arr1[i][1];
        entry.shirt_no = std::stoi(arr1[i][2]);
        entry.event_code = arr1[i][3];
        if(entry.event_code == "S"){
            entry.score = 20;
            entry.goals++;
        }
        else if(entry.event_code == "A"){
            entry.score = 10;
            entry.assists++;
        }
        else if(entry.event_code == "T"){
            entry.score = 1;
        }
        else if(entry.event_code == "P"){
            entry.score = 1;
        }
        else if(entry.event_code == "SH"){
            entry.score = 2;
        }
        else if(entry.event_code == "SG"){
            entry.score = 3;
        }
        else if(entry.event_code == "IP"){
             entry.score = -1;
        }
        else if(entry.event_code == "YC"){
            entry.score = -10;
        }
        else if(entry.event_code == "RC"){
            entry.score = -20;
        }
        else if(entry.event_code == "L"){
            entry.score = -2;
        }
        else if(entry.event_code == "CG"){
            entry.score = -5;
        }
        else{
            entry.score = 0;
        }
        put(entry);
    }
    
    print_table();
 

    return 0;
}
