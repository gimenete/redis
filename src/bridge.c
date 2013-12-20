#include "rocksdb/c.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

rocksdb_t *db;

void bridgeOpen() {
    char *err = NULL;
    rocksdb_options_t *options;

    options = rocksdb_options_create();
    rocksdb_options_set_create_if_missing(options, 1);
    db = rocksdb_open(options, "/tmp/testdb", &err);

    if (err != NULL) {
      fprintf(stderr, "Open fail.\n");
      return;
    }
}

int bridgeSet(const char* key, size_t keylen, const char* val, size_t vallen) {
    char *err = NULL;
    rocksdb_writeoptions_t *woptions = rocksdb_writeoptions_create();
    rocksdb_put(db, woptions, key, keylen, val, vallen, &err);
    if (err != NULL) {
        return 0;
    }
    return 1;
}

char* bridgeGet(const char* key, size_t keylen, size_t* read_len) {
    char *err = NULL;
    rocksdb_readoptions_t *roptions = rocksdb_readoptions_create();
    char *read = rocksdb_get(db, roptions, key, keylen, read_len, &err);

    if (err != NULL) {
      return NULL;
    }

    return read;
}

void bridgeDel() {

}

void bridgeClose() {

}
