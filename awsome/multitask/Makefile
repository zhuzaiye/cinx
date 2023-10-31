CC=g++
CFLAGS=-g -DDEBUG -W -Wall -fPIC -I.

TARGET=concorrent_hello
CCSRC=concorrent_hello.cpp

$(TARGET): $(CCSRC)
	$(CC) -O2 -o $@ $< $(CFLAGS)
clean:
	rm -f $(TARGET)