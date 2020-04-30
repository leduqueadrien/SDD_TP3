#option
CFLAGS = -Wall -Wextra -g -MMD
LIB = -lm

SRC = $(wildcard src/*.c) $(wildcard src/arbre/*.c) $(wildcard src/file/*.c) $(wildcard src/pile/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEP = $(patsubst %.o,%.d,$(OBJ))

.PHONY: all
all: bin/executable

bin/executable: $(OBJ)
	@mkdir -p $(@D)
	cc -o $@ $^ $(LIB)
	@echo "executer avec ./bin/executable"

build/%.o: src/%.c
	@mkdir -p $(@D)
	cc -c $< $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -rf build

-include $(DEP)