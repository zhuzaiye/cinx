CC=g++
CFLAGS=-g -DDEBUG -W -Wall -fPIC -I.
# 变量循环判断等基础
# TARGET=gcd_lcm
# CCSRC=gcd_lcm.cpp

# 原型, 重载
# TARGET=overload
# CCSRC=overload.cpp

# TARGET=preprocess
# CCSRC=preprocess.cpp

# TARGET=slice
# CCSRC=slice.cpp

TARGET=slice_str
CCSRC=slice_str.cpp

$(TARGET): $(CCSRC)
	$(CC) -O2 -o $@ $< $(CFLAGS)
clean:
	rm -f $(TARGET)