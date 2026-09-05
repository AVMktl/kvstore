#include "wal.h"

void put(unordered_map<string, string> &mp, const string &key, const string &value, ofstream &outFile){
    append({1, (int)key.size(), (int)value.size(), key, value}, outFile);
    mp[key] = value;
    return;
}

void del(unordered_map<string, string> &mp, const string key, ofstream &outFile){
    append({2, (int)key.size(), 0, key, ""}, outFile);
    mp.erase(key);
    return;
}

bool get(unordered_map<string, string> &mp, const string &key, string &value){
    if(mp.count(key)){
        value = mp[key];
        return true;
    }
    return false;
}

int main()
{
    unordered_map<string, string> mp;
    string command;
    ofstream outFile("wal.bin", ios::binary | ios::app);
    recover(mp);

    while(true){
        cout << "> ";
        getline(cin, command);
        stringstream ss(command);
        string operation, key, value;
        ss >> operation;

        if(operation == "exit"){
            break;
        }else if(operation == "get"){
            ss >> key;
            if(get(mp, key, value)){
                cout << value;
            }else{
                cout << "Key don't exist";
            }
        }else if(operation == "put"){
            ss >> key >> value;
            put(mp, key, value, outFile);
            cout << "Put Done";
        }else if(operation == "del"){
            ss >> key;
            del(mp, key, outFile);
            cout << "Delete Done";
        }else{
            cout << "Not a valid operator";
        }

        cout << "\n";
    }
    outFile.close();

    return 0;
}