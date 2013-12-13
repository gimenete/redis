#include "rocksdb/db.h"
#include "rocksdb/options.h"

rocksdb::DB* db;
rocksdb::Options options;
options.create_if_missing = true;

rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
// printf("opened!\n");

