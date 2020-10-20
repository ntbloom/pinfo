# gcc flags
FLAGS  = -std=c99
CFLAGS += -g
#CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Werror

# valgrind flags
VFLAGS  = --quiet
VFLAGS += -v
VFLAGS += --tool=memcheck
VFLAGS += --leak-check=full
VFLAGS += --error-exitcode=1
VFLAGS += --show-reachable=yes
VFLAGS += --show-possibly-lost=yes
VFLAGS += --undef-value-errors=yes

memcheck: pinfo
	#@valgrind $(VFLAGS) ./pinfo 2 18 25 abc
	@valgrind $(VFLAGS) ./pinfo
	@echo "Memory check passed"

test: pinfo
	@./pinfo 2 18 25 abc

clean:
	rm -rf *.o *.out *.out.dSYM

pinfo: pinfo.c
	@gcc $(CFLAGS) pinfo.c -o pinfo
