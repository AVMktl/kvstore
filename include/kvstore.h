#pragma once
#include "wal.h"
using namespace std;

class KVStore {
    private:
        unordered_map<string, string>mp;
        int fd;
        WAL wal;
        
    public:
        KVStore(string filename);

        void put(
            const string &key, 
            const string &value);

        void del(const string key);

        bool get(
            const string &key, 
            string &value);

        void exit();
};
