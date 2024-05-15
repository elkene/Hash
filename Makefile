BANDERAS = -Wall -Werror -pedantic -std=c99 -g
LINK = -lm

SOURCE =  $(wildcard *.c) $(wildcard **/*.c)
HEADERS = $(wildcard *.h) $(wildcard **/*.h)

leak := 
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	leak += valgrind --leak-check=full
endif
ifeq ($(UNAME_S),Darwin)
	leak += leaks --atExit --
endif

all: $(HEADERS)
	gcc $(BANDERAS) $(SOURCE) -o main

fuga: all
	$(leak) ./main
