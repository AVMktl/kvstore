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
    if(!inFile.is_open()){
       return;
    }
    Operation operation; 
    uint32_t key_size, value_size;
    streampos last_valid_pos = 0; 

    while(inFile.read(reinterpret_cast<char*>(&operation), sizeof(operation))){
        if(!inFile.read(reinterpret_cast<char*>(&key_size), sizeof(key_size))) break;
        if(!inFile.read(reinterpret_cast<char*>(&value_size), sizeof(value_size))) break;

        string key(key_size, '\0');
        string value(value_size, '\0');
        if(!inFile.read(reinterpret_cast<char*>(key.data()), key_size)) break;
        if(value_size > 0 && !inFile.read(reinterpret_cast<char*>(value.data()), value_size)) break;

        if(operation == Operation::Put){
            mp[key] = value;
        }else if(operation == Operation::Delete){
            mp.erase(key);
        }

        last_valid_pos = inFile.tellg();
    }

    inFile.close();

    int fd = open("wal.bin", O_RDWR);
    if(fd >= 0){
        ftruncate(fd, last_valid_pos);
        close(fd);
    }
}