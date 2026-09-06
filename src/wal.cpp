#include "wal.h"

void append(Record rcd, int fd){
    write(fd, &rcd.operation, sizeof(rcd.operation));
    write(fd, &rcd.key_size, sizeof(rcd.key_size));
    write(fd, &rcd.value_size, sizeof(rcd.value_size));
    write(fd, rcd.key.data(), rcd.key_size);
    write(fd, rcd.value.data(), rcd.value_size);
    fsync(fd);
}

void recover(unordered_map<string, string> &mp){
    ifstream inFile("wal.bin", ios::binary);
    if(inFile.is_open()){
       return;
    }
    Operation operation; 
    uint32_t key_size, value_size;

    while(inFile.read(reinterpret_cast<char*>(&operation), sizeof(operation))){
        inFile.read(reinterpret_cast<char*>(&key_size), sizeof(key_size));
        inFile.read(reinterpret_cast<char*>(&value_size), sizeof(value_size));

        string key(key_size, '\0');
        string value(value_size, '\0');
        inFile.read(reinterpret_cast<char*>(key.data()), key_size);
        inFile.read(reinterpret_cast<char*>(value.data()), value_size);

        if(operation == Operation::Put){
            mp[key] = value;
        }else if(operation == Operation::Delete){
            mp.erase(key);
        }
    }
}