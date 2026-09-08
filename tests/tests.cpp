#include <gtest/gtest.h>
#include "wal.h"
#include "kvstore.h"

class KVStoreTest : public testing::Test {
    protected: 
        KVStoreTest() : store("test.bin"){}
        
        KVStore store;
};

TEST_F(KVStoreTest, PutOperation) {
    store.put("Key1", "Value1");
    string val = "";
    store.get("Key1", val);

    ASSERT_EQ(val, "Value1");
}

TEST_F(KVStoreTest, GetOperation) {
    store.put("Key2", "Value2");
    string val = "";
    store.get("Key2", val);

    ASSERT_EQ(val, "Value2");

    ASSERT_NE(val, "Value1");
}

TEST_F(KVStoreTest, DeleteOperation) {
    store.put("Key3", "Value3");
    string val = "";
    store.get("Key3", val);
    store.del("Key3");

    val = "";
    store.get("Key3", val);

    ASSERT_EQ(val, "");
}

TEST_F(KVStoreTest, RecoveryOperation) {
    string val = "";
    KVStore store2("test.bin");

    store2.get("Key2", val);

    ASSERT_EQ(val, "Value2");
}