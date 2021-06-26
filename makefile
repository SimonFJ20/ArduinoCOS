
# 
# Makefile
#
# By Simon From Jakobsen
#

BIN=program

CC=g++
CFLAGS=-g -Wall
LFLAGS=

SRC=src
OBJ=obj
HDR=src
LIB=lib

SRCS=$(wildcard $(SRC)/*.cpp)
OBJS=$(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))
HDRS=$(wildcard $(HDR)/*.h)

$(BIN): $(OBJS) $(OBJ)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS) -L$(LIB)

$(OBJ)/%.o: $(SRC)/%.cpp $(OBJ) $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(HDR)

$(OBJ):
	mkdir -p $@

.PHONY: clean
clean:
	$(RM) -r $(OBJ)
	$(RM) $(BIN)

