#include "wal.h"
#include "kvstore.h"

void put_benchmark(
    KVStore &store, 
    int put_ops_count, 
    string &key_string_header, 
    string &value_string_header
) {
    auto put_ops_start = chrono::steady_clock::now();

    for(auto i=0; i<put_ops_count; i++){
        store.put(key_string_header + to_string(i), value_string_header + to_string(i));
    }

    auto put_ops_end = chrono::steady_clock::now();

    auto put_ops_elapsed = chrono::duration_cast<chrono::milliseconds>(
        put_ops_end - put_ops_start
    ).count();

    cout << "======= PUT Benchmark ======" << "\n";
    cout << "Operations: " << put_ops_count << "\n";
    cout << "Elapsed: " << fixed << setprecision(3) << (double)put_ops_elapsed / 1000 << "\n";
    if(put_ops_elapsed > 0){
        cout << "Throughput: " << 1000.0*put_ops_count/put_ops_elapsed << " ops/sec\n";
    }else{
        cout << "Took zero seconds" << "\n";
    }

    return;
}

void get_benchmark(
    KVStore &store,
    int get_ops_count,
    string &key_string_header,
    string &retrieval_value
) {
    auto get_ops_start = chrono::steady_clock::now();

    for(auto i=0; i<get_ops_count; i++){
        store.get(key_string_header + to_string(i), retrieval_value);
    }

    auto get_ops_end = chrono::steady_clock::now();

    auto get_ops_elapsed = chrono::duration_cast<chrono::milliseconds>(
        get_ops_end - get_ops_start
    ).count();

    cout << "======= GET Benchmark ======" << "\n";
    cout << "Operations: " << get_ops_count << "\n";
    cout << "Elapsed: " << fixed << setprecision(3) << (double)get_ops_elapsed / 1000 << "\n";
    if(get_ops_elapsed > 0){
        cout << "Throughput: " << 1000.0*get_ops_count/get_ops_elapsed << " ops/sec\n";
    }else{
        cout << "Took zero seconds" << "\n";
    }
}

void recovery_benchmark(
    string &benchmark_wal_file,
    int put_ops_count
) {
    WAL wal(benchmark_wal_file);
    unordered_map<string, string>mp;

    auto rcv_op_start = chrono::steady_clock::now();

    wal.recover(mp);

    auto rcv_op_end = chrono::steady_clock::now();

    auto rcv_op_elapsed = chrono::duration_cast<chrono::milliseconds>(
        rcv_op_end - rcv_op_start
    ).count();

    cout << "======= Recovery Time Benchmark ======" << "\n";
    cout << "WAL Records: " << put_ops_count << "\n";
    cout << "Elapsed: " << fixed << setprecision(3) << (double)rcv_op_elapsed / 1000 << "\n";
}

int main(){

    int PUT_OPS_COUNT = 1e4;
    int GET_OPS_COUNT = 1e4;
    string KEY_STRING_HEADER = "Key";
    string VALUE_STRING_HEADER = "Value";
    string RETRIEVAL_VLAUE = "";
    
    string BENCHMARK_WAL_FILE = "bench.bin";

    remove(BENCHMARK_WAL_FILE.c_str());
    
    KVStore store(BENCHMARK_WAL_FILE);

    // PUT operation benchmark

    put_benchmark(store, PUT_OPS_COUNT, KEY_STRING_HEADER, VALUE_STRING_HEADER);

    // GET operation benchmark

    get_benchmark(store, GET_OPS_COUNT, KEY_STRING_HEADER, RETRIEVAL_VLAUE);

    store.exit();

    // Recovery operation benchmark
    
    recovery_benchmark(BENCHMARK_WAL_FILE, PUT_OPS_COUNT);

    return 0;
}