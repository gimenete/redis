
#ifndef BRIDGE_H
#define BRIDGE_H

void bridgeOpen();

int bridgeSet(const char* key, const char* val);

char* bridgeGet();

void bridgeDel();

void bridgeClose();

#endif
