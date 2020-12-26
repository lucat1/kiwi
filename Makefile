CC     ?= gcc
CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration -Wno-missing-braces

LDFLAGS += -lxcb -lxcb-keysyms
PREFIX ?= /usr
BIN = kiwi

SRC = $(wildcard *.c)
OBJ := $(SRC:.c=.o)

kiwi: $(OBJ) 
	@echo "LD\t$(BIN)"
	@$(CC) $(LDFLAGS) -o $(BIN) $(OBJ) 

debug: CFLAGS += -DDEBUG -ggdb
debug: clean kiwi

profile: CFLAGS += -DDEBUG -pg
profile: clean kiwi

$(OBJ): config.h
$(OBJ): %.o: %.c
	@echo "CC\t$<"
	@$(CC) $(CFLAGS) -c -o $@ $(@:%.o=%.c)

.PHONY: clean install uninstall
clean:
	rm *.o kiwi

install: kiwi
	@echo installing to $(DESTDIR)$(BINDIR)
	@mkdir -p $(DESTDIR)$(BINDIR)
	@cp -f kiwi $(DESTDIR)$(BINDIR)
	@chmod 755 $(DESTDIR)$(BINDIR)/kiwi

uninstall:
	@echo uninstalling from $(DESTDIR)$(BINDIR) 
	@rm -f $(DESTDIR)$(BINDIR)/kiwi
