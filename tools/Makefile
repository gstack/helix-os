all: ddbg

ddbg:
	@cd kernel_dbg; $(MAKE)
	@cp kernel_dbg/ddbg .

clean:
	@-rm ddbg
	@-cd kernel_dbg; $(MAKE) clean

.PHONY: all
