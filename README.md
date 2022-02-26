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