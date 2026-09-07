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

```cmd
mkdir build
cd build
cmake ..
cmake --build .
```

## Run

./kvstore

## Example

<img width="402" height="310" alt="image" src="https://github.com/user-attachments/assets/591f5ac5-00c1-42f3-8340-39e9945f9660" />

```text
> put name Alice
> get name
Alice

> del name
> get name
Key don't exist
```
