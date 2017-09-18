target := shell
src_dir := ./src
tests_dir ?= ./tests

sources := $(shell find $(src_dir) -name *.c)
tests_dir := $(shell find $(tests_dir) -name *.c)
objects := $(addsuffix .o,$(basename $(sources))) 
test_objects := $(addsuffix .o,$(basename $(tests_dir))) \
	$(filter-out $(src_dir)/main.o,$(objects))
deps := $(objects:.o)

include := $(shell find $(src_dir) -type d)
include_flags := $(addprefix -I,$(include))

CFLAGS := $(include_flags) -g

$(target): $(objects)
	$(CC) $(LDFLAGS) $(objects) -o $@

test: $(test_objects) 
	$(CC) $(LDFLAGS) $(test_objects) -o $@

.PHONY: clean
clean:
	$(RM) $(target) test $(objects) $(test_objects) $(deps)
