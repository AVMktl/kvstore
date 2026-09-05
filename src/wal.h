#pragma once

#include<bits/stdc++.h>
using namespace std;

struct RecordHeader{
    int operation;
    int key_size;
    int value_size;
    string key;
    string value;
};

void append(RecordHeader rcd, ofstream &outFile);

void recover(unordered_map<string, string> &mp);