.PHONY: all run
all: bin/$(MODULE) $(J)
run: bin/$(MODULE) $(J)
	$^
