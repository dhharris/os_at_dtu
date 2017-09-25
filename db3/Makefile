executable=shell
src_dir := ./src
inc_dir := ./include
test_dir ?= ./tests

sources := $(wildcard $(src_dir)/*.c) 
headers := $(wildcard $(inc_dir)/*.h) 
test_sources := $(wildcard $(test_dir)/*.c) 
objects := $(addprefix obj/,$(notdir $(sources:.c=.o)))
test_objects := $(addprefix obj/,$(notdir $(test_sources:.c=.o))) $(objects)

CFLAGS := -g

$(executable): main.c $(objects)
	$(CC) $(LDFLAGS) -o $@ $^

test: $(test_objects) 
	$(CC) $(CFLAGS) -o $@ $^ 

obj/%.o: $(src_dir)/%.c 
	$(CC) $(CFLAGS) -c -o $@ $<

obj/%.o: $(test_dir)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	$(RM) $(executable) test $(objects) $(test_objects) $(deps)
