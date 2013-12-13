#include "rocksdb/db.h"
#include <stdio.h>

int main() {
	rocksdb::DB* db;
	rocksdb::Options options;
	options.create_if_missing = true;

	rocksdb::Status status = rocksdb::DB::Open(options, "/tmp/testdb", &db);
	if (status.ok()) {
		printf("ok!\n");
	} else {
		printf("nok!\n");
	}
}

