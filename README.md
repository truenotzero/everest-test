# test
A testing helper

## Usage
An example test file should look like this:
```c
#include <test.inc>

void init() { /* Code that runs before all tests */ }
void cleanup() { /* Code that runs after all tests */ }

int successful_test() {
    // do some testing
    return 0;// zero means pass
}

int failed_test() {
    // do some testing
    return 1; // non-zero means fail
}

struct test* register_tests() {
    // tests are run in order of registraion
    static struct test tests[] = {
        TEST_ADD(successful_test),
        TEST_ADD(failed_test),
        TEST_DONE(), // this is necessary
    };

    return tests;
}
```

Compile & run

## Including testing as part of the automated build process
Note that doing this will require you to define a test file for every source you have, even if it's a dummy file
Create a makefile like so:
```Makefile
# you must define: 
CC=
CFLAGS=
LDFLAGS=

SRC_DIR=path/to/sources
TEST_SRC_DIR=path/to/tests
TEST_BIN_DIR=path/to/tests/binaries


# The implicit rule for compiling C files is
# removed in test.makefile, therefore, you must
# re-implement it. Take note that `$(TEST_BIN_DIR)/%.test
# is required as a dependency
%.o: %.c $(TEST_BIN_DIR)/%.test
	$(CC) $(CFLAGS) -c $< -o $@

include test.makefile
```