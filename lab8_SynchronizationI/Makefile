SRCS = $(wildcard *.c)

PROGS = $(patsubst %.c,%,$(SRCS))

all: $(PROGS)

CFLAGS = -lpthread

%: %.c
	gcc $< $(CFLAGS) -o $@

# .PHONY clean
clean:
	rm $(PROGS)