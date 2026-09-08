# KV Store

A single-node persistent key-value store implemented in C++, using an append-only write-ahead log (WAL) and an in-memory hash index.

## Features

- PUT / GET / DELETE
- Append-only WAL
- Durable writes using fsync()
- Crash recovery through WAL replay
- Truncation of incomplete final records
- In-memory hash index
- CMake build

## Architecture
```mermaid
flowchart TD
    User([User / CLI]) -->|PUT / GET / DEL| KVS[KVStore Engine]

    subgraph Memory["In-Memory RAM"]
        HashIndex["Hash Index<br/>std::unordered_map&lt;string, string&gt;"]
    end

    subgraph WAL["Write-Ahead Logging"]
        WALMgr["WAL Manager<br/>wal.cpp"]
    end

    subgraph Storage["Persistent Storage"]
        LogFile[("wal.bin<br/>Append-Only Log")]
    end

    %% Write Path
    KVS -->|"1. append(record)"| WALMgr
    WALMgr -->|"2. write() + fsync()"| LogFile
    KVS -->|"3. update index"| HashIndex

    %% Read Path
    KVS -->|"GET: direct lookup"| HashIndex

    %% Recovery Path
    LogFile -.->|"Read WAL records on startup"| WALMgr
    WALMgr -.->|"Replay PUT / DELETE"| HashIndex
    WALMgr -.->|"ftruncate() invalid tail"| LogFile
```

## Build

```bash
cmake -S . -B build
cmake --build build
cd build
```

## Run

Run the KV Store:
```bash
./kvstore
```

Run the benchmarks:
```bash
./kvstore_bench
```

Run the tests:
```bash
ctest
```

## Example

<img width="400" height="310" alt="image" src="https://github.com/user-attachments/assets/591f5ac5-00c1-42f3-8340-39e9945f9660" />

```text
> put name Alice
> get name
Alice

> del name
> get name
Key don't exist
```

## Benchmarks

The project includes benchmarks for:

- PUT throughput
- GET throughput
- WAL recovery time

### Workload

| Benchmark | Operations | Workload |
|---|---:|---|
| PUT | 10,000 | Insert unique `Key0` ... `Key9999` with corresponding values |
| GET | 10,000 | Read the same 10,000 existing keys from the in-memory hash index |
| Recovery | 10,000 WAL records | Replay the WAL and rebuild the in-memory hash index |

Each PUT appends a record to the WAL and calls `fsync()` before updating the in-memory index.

### Results

| Benchmark | Azure VM | MacBook Air M4 |
|---|---:|---:|
| PUT throughput | 355 ops/sec | 44,643 ops/sec |
| GET throughput | 3.33M ops/sec | 5.0M ops/sec |
| WAL recovery | 7 ms | 12 ms |

### Benchmark Environments

**Azure VM**
- CPU: AMD EPYC 7763
- vCPU: 2
- Memory: 8 GB
- Architecture: x86_64
- Environment: Microsoft Azure VM

**MacBook Air M4**
- Chip: Apple M4
- CPU cores: 10 (4 performance, 6 efficiency)
- Memory: 16 GB
- Architecture: arm64
- Operating system: macOS

Benchmark results are environment-dependent and can vary with storage performance, virtualization, filesystem behavior and system load. PUT performance is particularly affected by the latency of `fsync()`.
