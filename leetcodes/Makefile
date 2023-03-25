
# .PHONY: clean

# CC=g++
# BIN=exec
# OBJS=AddTwoSum.o utils.o

# $(BIN): $(OBJS)
# 	@echo "start compiling..."
# 	@echo $(CC)
# 	$(CC) -o $(BIN) $(OBJS)
# 	@echo "compile done"
# AddTwoSum.o: AddTwoSum.cpp
# 	$(CC) -c -o $@ $<
# utils.o: utils.cpp
# 	$(CC) -c -o $@ $<
# clean:
# 	rm -f $(BIN) $(OBJS)

# 如果当前目录中，正好有一个文件叫做clean，那么这个命令不会执行。
# 因为Make发现clean文件已经存在，就认为没有必要重新构建了，就不会执行指定的rm命令
# 就有了下面的伪声明
.PHONY: clean

# 编译Cpp
CC = g++
# 设置编译参数设置
# -g表示编译时候加入调试信息,
# -DDEBUG表示编译debug版本
# -W -Wall表示输出所有警告
# -fPIC是生成dll时候用的
CFLAGS = -g -DDEBUG -W -Wall -fPIC
# 头文件的目录为./ 当前目录
HEADER  = -I./

ALGONAME = AddTwoSum
TOOLNAME = utils
OBJS= $(ALGONAME).o $(TOOLNAME).o

TARGET = algo

$(TARGET): $(OBJS)
	@echo "start compiling..."
	$(CC) $(CFLAGS) -o $@ $^
	@echo "compile done"
$(ALGONAME).o: $(ALGONAME).cpp
	$(CC) -c -o $@ $<
$(TOOLNAME).o: $(TOOLNAME).cpp
	$(CC) -c -o $@ $<
clean:
	rm -f $(TARGET) $(OBJS)