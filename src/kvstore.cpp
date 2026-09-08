#include "kvstore.h"

KVStore::KVStore(string filename) : wal(filename) {
    wal.recover(mp);
    fd = open(filename.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0644);
    if(fd < 0){
        cerr << "Failed to open WAL file.\n";
    }
}

void KVStore::put(const string &key, const string &value){
    wal.append({Operation::Put, (uint32_t)key.size(), (uint32_t)value.size(), key, value}, fd);
    mp[key] = value;
    return;
}

void KVStore::del(const string key){
    wal.append({Operation::Delete, (uint32_t)key.size(), 0, key, ""}, fd);
    mp.erase(key);
    return;
}

bool KVStore::get(const string &key, string &value){
    if(mp.count(key)){
        value = mp[key];
        return true;
    }
    return false;
}

void KVStore::exit(){
    close(fd);
    mp.clear();
}