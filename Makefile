CC := gcc
BIN := ./bin
PROGRAM := rm
SRC := ./src
SOURCES := $(SRC)/rm.c \
		   $(SRC)/fs/move.c \
		   $(SRC)/fs/trash.c \
		   $(SRC)/fs/xattr.c

.PHONY: all rm

all: rm

rm: $(SOURCES)
	@mkdir -p $(BIN)
	@$(CC) -Wall -Wextra -O2 -o $(BIN)/$(PROGRAM) $(SOURCES)
