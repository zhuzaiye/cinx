CC=g++
CFLAGS=-g -DDEBUG -W -Wall -fPIC -I.
TARGET=concurrent
CCSRC=hello.cpp

$(TARGET): $(CCSRC)
	$(CC) -O2 -o $@ $< $(CFLAGS)
clean:
	rm -f $(TARGET)