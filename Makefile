CC     ?= pcc
CFLAGS += -std=c99 -Wall -Wextra -pedantic -Wold-style-declaration -Wno-missing-braces -O3

LDFLAGS += -lxcb -lxcb-keysyms -lxcb-randr
PREFIX ?= /usr
PROG = kiwi

$(PROG): $(PROG).c config.h
	$(CC) $(LDFLAGS) -o $(PROG) $(PROG).c

dev: CFLAGS += -DDEBUG
dev: kiwi

debug: CFLAGS += -DDEBUG -DVERBOSE -ggdb
debug: clean kiwi

profile: CFLAGS += -DDEBUG -pg
profile: clean kiwi

.PHONY: clean install uninstall
clean:
	rm $(PROG)

install: kiwi
	@echo installing to $(DESTDIR)$(BINDIR)
	@mkdir -p $(DESTDIR)$(BINDIR)
	@cp -f kiwi $(DESTDIR)$(BINDIR)
	@chmod 755 $(DESTDIR)$(BINDIR)/kiwi

uninstall:
	@echo uninstalling from $(DESTDIR)$(BINDIR) 
	@rm -f $(DESTDIR)$(BINDIR)/kiwi
