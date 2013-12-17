#include "rocksdb/c.h"
#include <stdio.h>
#include <string.h>

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

    /* reset error var */
    // rocksdb_free(err); err = NULL;
    printf("Rocksdb database opened!!!!!\n");
}

int bridgeSet(const char* key, const char* val) {
    printf("Rocksdb set %s -> %s\n", key, val);
    char *err = NULL;
    rocksdb_writeoptions_t *woptions = rocksdb_writeoptions_create();
    rocksdb_put(db, woptions, key, strlen(key), val, strlen(val), &err);
    if (err != NULL) {
        return 0;
    }
    return 1;
}

char* bridgeGet(const char* key) {
    printf("Rocksdb get %s\n", key);
    char *err = NULL;
    char *read;
    size_t read_len;
    rocksdb_readoptions_t *roptions = rocksdb_readoptions_create();
    read = rocksdb_get(db, roptions, key, strlen(key), &read_len, &err);

    if (err != NULL) {
      fprintf(stderr, "Read fail.\n");
      return NULL;
    }

    printf("key: %s\n", read);
    return read;
}

void bridgeDel() {

}

void bridgeClose() {

}
