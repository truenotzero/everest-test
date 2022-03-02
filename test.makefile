# in the project's main makefile define:
# TEST_SRC_DIR=path/to/test/srcs
# TEST_BIN_DIR=path/to/test/execs
# OBJS=all object files here
# the tests inside the directory will mirror src's hierarchy

%.o: %.c



.PRECIOUS: $(TEST_BIN_DIR)/%.test
$(TEST_BIN_DIR)/%.test: $(TEST_SRC_DIR)/%.c %.c
	mkdir -p $(TEST_BIN_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)
	$@
