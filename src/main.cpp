#include "wal.h"
#include "kvstore.h"

int main()
{
    KVStore store("wal.bin");

    string command;

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
            if(store.get(key, value)){
                cout << value;
            }else{
                cout << "Key don't exist";
            }
        }else if(operation == "put"){
            ss >> key >> value;
            store.put(key, value);
            cout << "Put Done";
        }else if(operation == "del"){
            ss >> key;
            store.del(key);
            cout << "Delete Done";
        }else{
            cout << "Not a valid operator";
        }

        cout << "\n";
    }
    store.exit();

    return 0;
}