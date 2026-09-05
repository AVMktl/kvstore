#include "wal.h"

void append(RecordHeader rcd, ofstream &outFile){
    outFile.write(reinterpret_cast<char*>(&rcd.operation), sizeof(rcd.operation));
    outFile.write(reinterpret_cast<char*>(&rcd.key_size), sizeof(rcd.key_size));
    outFile.write(reinterpret_cast<char*>(&rcd.value_size), sizeof(rcd.value_size));
    outFile.write(reinterpret_cast<char*>(rcd.key.data()), rcd.key_size);
    outFile.write(reinterpret_cast<char*>(rcd.value.data()), rcd.value_size);
    outFile.flush();
}

void recover(unordered_map<string, string> &mp){
    ifstream inFile("wal.bin", ios::binary);
    if(inFile.is_open()){
        cout << "Reading File content: \n";
    }
    int operation, key_size, value_size;

    while(inFile.read(reinterpret_cast<char*>(&operation), sizeof(operation))){
        inFile.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));
        inFile.read(reinterpret_cast<char*>(&value_size), sizeof(value_size));

        string key(key_size, '\0');
        string value(value_size, '\0');
        inFile.read(reinterpret_cast<char*>(key.data()), key_size);
        inFile.read(reinterpret_cast<char*>(value.data()), value_size);

        cout << operation << " " << key << " " << value << "\n";

        if(operation == 1){
            mp[key] = value;
        }else if(operation == 2){
            mp.erase(key);
        }
    }
}