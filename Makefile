CC := gcc
BIN := ./bin
PROGRAM := rm
SRC := ./src
SOURCES := $(SRC)/rm.c \
		   $(SRC)/trash/trash.c \
		   $(BIN)/bridge.a

.PHONY: all rm

all: rm

rm: $(SOURCES) bin/bridge.a
	@mkdir -p $(BIN)
	@$(CC) -Wall -Wextra -O2 -L /usr/lib/swift -framework Foundation -o $(BIN)/$(PROGRAM) $(SOURCES)
	@rm $(BIN)/bridge.a $(BIN)/bridge.o

bin/bridge.o:
	swiftc -c $(SRC)/trash/bridge.swift -parse-as-library -emit-object -o $(BIN)/bridge.o

bin/bridge.a: bin/bridge.o
	ar rcs $(BIN)/bridge.a $(BIN)/bridge.o
