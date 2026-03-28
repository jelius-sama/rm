CC := gcc
BIN := ./bin
PROGRAM := rm
SRC := ./src
SOURCES := $(SRC)/rm.c \
		   $(SRC)/trash/trash.c \
		   $(BIN)/bridge.o

.PHONY: all rm

all: rm

rm: $(SOURCES) bin/bridge.o
	@mkdir -p $(BIN)
	$(CC) -Wall -Wextra -O2 -L /usr/lib/swift -framework Foundation -o $(BIN)/$(PROGRAM) $(SOURCES)
	@rm $(BIN)/bridge.o

bin/bridge.o:
	swiftc -c $(SRC)/trash/bridge.swift -parse-as-library -emit-object -o $(BIN)/bridge.o
