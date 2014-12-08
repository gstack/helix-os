include $(MKROOT)/$(MKCONFIG)

INCLUDE		= $(shell pwd)/../include
CFLAGS		= -nostartfiles -nodefaultlibs -nostdlib -fno-builtin -Wall -DARCH=$(ARCH) -I$(INCLUDE)
ASFLAGS		= -f elf
LDFLAGS		= -fPIC -shared

OBJS		= $(patsubst %.c, %.o, $(wildcard *c))
OBJS		+=$(patsubst %.s, %.o, $(wildcard *s))

all: debugger_mod

%.o : %.c
	@echo "   [debugger] CC $<"
	@$(CC) $(CFLAGS) -c $<

%.o : %.s
	@echo "   [debugger] AS $<"
	@$(AS) $(ASFLAGS) $<

debugger_mod: $(OBJS)
	@echo "   [debugger] LD $(LDFLAGS) -o ../../modobjs/debugger_mod.o *.o"
	@$(LD) $(LDFLAGS) -o ../../modobjs/debugger_mod.o *.o

clean:
	@rm -f *.o

.PHONY: all
