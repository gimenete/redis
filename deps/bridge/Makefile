WARNING_FLAGS = -Wall -Werror
CXXFLAGS += -g $(WARNING_FLAGS) $(PLATFORM_CXXFLAGS) $(OPT) -Woverloaded-virtual -std=gnu++11

default:
	g++ -o bridge.o bridge.cc ../rocksdb/librocksdb.a $(CXXFLAGS) -I. -I../rocksdb/include
