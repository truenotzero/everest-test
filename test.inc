#ifdef TEST_H_
#error "Double inclusion of testing framework"
#else
#define TEST_H_
#endif // FRAMEWORK_H_

#include <stdio.h>

typedef int (*p_test_f)();

struct test {
  char const *name;
  p_test_f func;
};

#define TEST_ADD(t)                                                            \
  { .name = #t, .func = t }
#define TEST_DONE()                                                            \
  { .name = 0, .func = 0 }

struct test *register_tests();
void init();
void cleanup();

int main() {
  struct test *tests = register_tests();
  init();
  cleanup();

  // count tests
  unsigned num_tests;
  for (num_tests = 0; tests[num_tests].name; ++num_tests)
    ;

  for (unsigned i = 0; i < num_tests; ++i) {
    char const *name = tests[i].name;
    p_test_f f = tests[i].func;
    printf("[%d/%d] %s => ", i + 1, num_tests, name);
    int result = f();
    if (result == 0) {
      printf("Pass\n");
    } else {
      printf("Fail (%d)\n", result);
      return result;
    }
  }
}
