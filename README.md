What is this?
-------------

This is a **very experimental** redis fork. Redis is a blazing-fast in-memory database. Redis has had some some attempts to provide mechanisms to have datasets bigger than the available RAM but all have been discontinued. For example: [vm](http://redis.io/topics/virtual-memory) (virtual-memory) and [diskstore](https://groups.google.com/forum/#!topic/redis-db/jJJErYbVUY4). And of course letting the operating system [swap your dataset](http://antirez.com/news/52) is not a good idea.

The intention of this fork is to provide a way to store things on disk rather on having everything in memory. We have chosen a disk-based key-value store that you can use with some additional commands

    ddbopen // opens the disk-based database
    ddbget key // gets a key
    ddbset key value // sets the value of a key

The chosen disk-based database is [RocksDB](http://rocksdb.org) from Facebook.

**Why not using redis and rocks-db separately in the application layer?**

We decided to make this fork that embeds the disk-based database because this way you can use the embedded database from LUA scripts.

**One possible usage**

For example if you have tons of small hashes and many of them are rarely read, but sometimes you will want to operate with them you can keep the "fresh" hashes in memory and keep the rarely used in the disk-based db.

You could read a hash this way:

    local ttl = 24*60*60*1000 // one day
    local obj = redis.hgetall(key);
    if obj == nil then // hash not in redis
    	// check the disk-based database
        local dump = redis.call("ddbget", key);
        if dump != nil then
            redis.restore(key, ttl, dump); // restore to redis with a ttl
            obj = redis.hgetall(key);
        else
            // objet not found in the disk-based db
        end
    end

You could store this way:

    local ttl = 24*60*60*1000 // one day
    // modify the hash in some way (hset, hincrby,...)
    
    local dump = redis.dump(key)
    redis.call("ddbset", key, dump)
    
    // make the key expire. It is already backed up
    // in the disk-based database
    redis.call("pexpire", key)

**Why rocks-db?**

Becuase it has [great performance](https://github.com/facebook/rocksdb/wiki/Performance-Benchmarks). Nevertheless our intention is to be easy to change the underlaying disk-based database. So all the communication is done in a file called `bridge.c` that you could reimplement with another database engine. That's why the file is called *bridge*.

**What about redis-nds?**

[Redis nds](https://github.com/mpalmer/redis/tree/nds-2.6) is another fork of redis. The idea is similar but the implementation is very different. NDS does not add new commands. It instead implements a totally transparent mechanism. This is good for many things but you don't have total control over which keys are in memory or not. NDS is a more mature project and it's being used in production.

**TODO**

* Implement more commands: `ddbdel key`
* Make the disk-database path configurable
* Open and close the disk-database automatically
* Integrate the disk-based db in the replication process

---

Here gores the original redis README

Where to find complete Redis documentation?
-------------------------------------------

This README is just a fast "quick start" document. You can find more detailed
documentation at http://redis.io

Building Redis
--------------

Redis can be compiled and used on Linux, OSX, OpenBSD, NetBSD, FreeBSD.
We support big endian and little endian architectures.

It may compile on Solaris derived systems (for instance SmartOS) but our
support for this platform is "best effort" and Redis is not guaranteed to
work as well as in Linux, OSX, and *BSD there.

It is as simple as:

    % make

You can run a 32 bit Redis binary using:

    % make 32bit

After building Redis is a good idea to test it, using:

    % make test

Fixing problems building 32 bit binaries
---------

If after building Redis with a 32 bit target you need to rebuild it
with a 64 bit target, or the other way around, you need to perform a
"make distclean" in the root directory of the Redis distribution.

In case of build errors when trying to build a 32 bit binary of Redis, try
the following steps:

* Install the packages libc6-dev-i386 (also try g++-multilib).
* Try using the following command line instead of "make 32bit":

    make CFLAGS="-m32 -march=native" LDFLAGS="-m32"

Allocator
---------

Selecting a non-default memory allocator when building Redis is done by setting
the `MALLOC` environment variable. Redis is compiled and linked against libc
malloc by default, with the exception of jemalloc being the default on Linux
systems. This default was picked because jemalloc has proven to have fewer
fragmentation problems than libc malloc.

To force compiling against libc malloc, use:

    % make MALLOC=libc

To compile against jemalloc on Mac OS X systems, use:

    % make MALLOC=jemalloc

Verbose build
-------------

Redis will build with a user friendly colorized output by default.
If you want to see a more verbose output use the following:

    % make V=1

Running Redis
-------------

To run Redis with the default configuration just type:

    % cd src
    % ./redis-server
    
If you want to provide your redis.conf, you have to run it using an additional
parameter (the path of the configuration file):

    % cd src
    % ./redis-server /path/to/redis.conf

It is possible to alter the Redis configuration passing parameters directly
as options using the command line. Examples:

    % ./redis-server --port 9999 --slaveof 127.0.0.1 6379
    % ./redis-server /etc/redis/6379.conf --loglevel debug

All the options in redis.conf are also supported as options using the command
line, with exactly the same name.

Playing with Redis
------------------

You can use redis-cli to play with Redis. Start a redis-server instance,
then in another terminal try the following:

    % cd src
    % ./redis-cli
    redis> ping
    PONG
    redis> set foo bar
    OK
    redis> get foo
    "bar"
    redis> incr mycounter
    (integer) 1
    redis> incr mycounter
    (integer) 2
    redis> 

You can find the list of all the available commands here:

    http://redis.io/commands

Installing Redis
-----------------

In order to install Redis binaries into /usr/local/bin just use:

    % make install

You can use "make PREFIX=/some/other/directory install" if you wish to use a
different destination.

Make install will just install binaries in your system, but will not configure
init scripts and configuration files in the appropriate place. This is not
needed if you want just to play a bit with Redis, but if you are installing
it the proper way for a production system, we have a script doing this
for Ubuntu and Debian systems:

    % cd utils
    % ./install_server

The script will ask you a few questions and will setup everything you need
to run Redis properly as a background daemon that will start again on
system reboots.

You'll be able to stop and start Redis using the script named
/etc/init.d/redis_<portnumber>, for instance /etc/init.d/redis_6379.

Code contributions
---

Note: by contributing code to the Redis project in any form, including sending
a pull request via Github, a code fragment or patch via private email or
public discussion groups, you agree to release your code under the terms
of the BSD license that you can find in the COPYING file included in the Redis
source distribution.

Please see the CONTRIBUTING file in this source distribution for more
information.

Enjoy!
