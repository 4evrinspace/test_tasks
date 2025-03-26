DIRS = 1 2 4 5 6 7 8 9

.PHONY: all $(DIRS)

all: $(DIRS)

$(DIRS):
	$(MAKE) -C $@

clean:
	@for dir in $(DIRS); do \
		$(MAKE) -C $$dir clean; \
	done