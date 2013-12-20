
#ifndef BRIDGE_H
#define BRIDGE_H

void bridgeOpen();

int bridgeSet(const char* key, size_t keylen, const char* val, size_t vallen);

const char* bridgeGet(const char* key, size_t keylen, size_t* vallen);

void bridgeDel();

void bridgeClose();

#endif
