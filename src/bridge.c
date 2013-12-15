#include "rocksdb/c.h"
#include <stdio.h>

void helloWorld() {
    rocksdb_t *db;
    rocksdb_options_t *options;
    // rocksdb_readoptions_t *roptions;
    // rocksdb_writeoptions_t *woptions;
    char *err = NULL;
    // char *read;
    // size_t read_len;

    /******************************************/
    /* OPEN */

    options = rocksdb_options_create();
    rocksdb_options_set_create_if_missing(options, 1);
    db = rocksdb_open(options, "/tmp/testdb", &err);

    if (err != NULL) {
      fprintf(stderr, "Open fail.\n");
      return;
    }

    /* reset error var */
    // rocksdb_free(err); err = NULL;
    printf("Hello world!!!!!\n");
}
