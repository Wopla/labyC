# ENSICAEN
# 6 Boulevard Marechal Juin
# F-14050 Caen Cedex
#
# This file is owned by ENSICAEN students.
# No portion of this document may be reproduced, copied
# or revised without written permission of the authors.
#
# @author Cochepain Esteban <esteban.cochepain@ecole.ensicaen.fr>
# @version 01.00
# @date 30/10/2022

CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -ansi -g
CPPFLAGS=-I$(HEADER_DIR)
EXEC=generator
HEADER_DIR=headers/
LDFLAGS=-lm
OBJS_DIR=objs/
SRC_DIR=c/
MAIN_DIR=mainFolder/
BIN_DIR=../bin/

SRC_FILES:= $(shell find c/ -type f -name "*.c")
OBJS_LIST_FILES:= $(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC_FILES))

$(BIN_DIR)$(EXEC): $(OBJS_DIR)gen.o $(OBJS_LIST_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
#

$(OBJS_DIR)gen.o: $(MAIN_DIR)gen.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJS_DIR) $(BIN_DIR)