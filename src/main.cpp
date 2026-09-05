#include<bits/stdc++.h>
using namespace std;

void del(unordered_map<string, string> &mp, const string key){
    mp.erase(key);
    return;
}

void put(unordered_map<string, string> &mp, const string &key, const string &value){
    mp[key] = value;
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

    while(true){
        cout << "> ";
        getline(cin, command);
        stringstream ss(command);
        string optr, key, value;
        ss >> optr;

        if(optr == "exit"){
            break;
        }else if(optr == "get"){
            ss >> key;
            if(get(mp, key, value)){
                cout << value;
            }else{
                cout << "Key don't exist";
            }
        }else if(optr == "put"){
            ss >> key >> value;
            put(mp, key, value);
            cout << "Put Done";
        }else if(optr == "del"){
            ss >> key;
            del(mp, key);
            cout << "Delete Done";
        }else{
            cout << "Not a valid operator";
        }

        cout << "\n";
    }

    return 0;
}