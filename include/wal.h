#pragma once

#include<bits/stdc++.h>
#include <fcntl.h>
#include <unistd.h>
using namespace std;

enum Operation {
    Put = 1,
    Delete = 2
};

struct Record{
    Operation operation;
    uint32_t key_size;
    uint32_t value_size;
    string key;
    string value;
};

class WAL {
    private:
        string fileName;
        
    public:
        WAL(string filename);

        void append(Record rcd, int fd);

        void recover(unordered_map<string, string> &mp); 
};