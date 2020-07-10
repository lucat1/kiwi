CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration
CFLAGS += -Wno-unused-parameter -g
LDFLAGS += -lX11 
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
CC     ?= gcc

all:
	$(CC) $(CFLAGS) -o kiwi  kiwi.c  $(LDFLAGS)
	$(CC) $(CFLAGS) -o kiwic kiwic.c $(LDFLAGS)

test: all
	PATH=$$PATH:$CWD DISPLAY=:1 ./kiwi

install: all
	@echo installing to $(DESTDIR)$(BINDIR)
	@mkdir -p $(DESTDIR)$(BINDIR)
	@cp -f kiwi $(DESTDIR)$(BINDIR)
	@chmod 755 $(DESTDIR)$(BINDIR)/kiwi

uninstall:
	@echo uninstalling from $(DESTDIR)$(BINDIR) 
	@rm -f $(DESTDIR)$(BINDIR)/kiwi
