#include "wal.h"

void put(unordered_map<string, string> &mp, const string &key, const string &value, int fd){
    append({Operation::Put, (uint32_t)key.size(), (uint32_t)value.size(), key, value}, fd);
    mp[key] = value;
    return;
}

void del(unordered_map<string, string> &mp, const string key, int fd){
    append({Operation::Delete, (uint32_t)key.size(), 0, key, ""}, fd);
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
    recover(mp);
    int fd = open("wal.bin", O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd < 0){
        cerr << "Failed to open WAL file.\n";
        return 1;
    }

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
            put(mp, key, value, fd);
            cout << "Put Done";
        }else if(operation == "del"){
            ss >> key;
            del(mp, key, fd);
            cout << "Delete Done";
        }else{
            cout << "Not a valid operator";
        }

        cout << "\n";
    }
    close(fd);

    return 0;
}