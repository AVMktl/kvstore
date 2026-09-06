#pragma once

#include<bits/stdc++.h>
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

void append(Record rcd, ofstream &outFile);

void recover(unordered_map<string, string> &mp);