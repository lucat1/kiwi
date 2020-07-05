CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wno-unused-parameter -g
LDFLAGS += -lX11 
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CC     ?= gcc

SRC=kiwi.c

all:
	$(CC) $(CFLAGS) -o kiwi $(SRC) $(LDFLAGS)

test: all
	DISPLAY=:1 ./kiwi

install: all
	@echo installing to $(DESTDIR)$(BINDIR)
	@mkdir -p $(DESTDIR)$(BINDIR)
	@cp -f kiwi $(DESTDIR)$(BINDIR)
	@chmod 755 $(DESTDIR)$(BINDIR)/kiwi

uninstall:
	@echo uninstalling from $(DESTDIR)$(BINDIR) 
	@rm -f $(DESTDIR)$(BINDIR)/kiwi
