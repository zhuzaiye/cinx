CC=g++
CFLAGS=-g -DDEBUG -W -Wall -fPIC -I.
TARGET=structExe
# CCSRC=operator_overload.cpp
CCSRC=struct_definition.cpp

$(TARGET): $(CCSRC)
	$(CC) -O2 -o $@ $< $(CFLAGS)
clean:
	rm -f $(TARGET)