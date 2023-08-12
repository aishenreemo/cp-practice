INCLUDE := ./inc
DIST := ./dist

CC := gcc
LIBS := -lSDL2 -lm
FLAGS := -I$(INCLUDE)

all: $(DIST) $(DIST)/raytracing
.PHONY: clean format

$(DIST):
	mkdir -p $@

$(DIST)/%: %.c | $(DIST)
	$(CC) -g -o $@ $^ $(LIBS) $(FLAGS)

clean:
	rm $(DIST)/*

format:
	find . \( -name *.c -o -name *.h \) | xargs clang-format -i;
