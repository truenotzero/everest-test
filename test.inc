#ifdef TEST_H_
#error "Double inclusion of testing framework"
#else
#define TEST_H_
#endif // FRAMEWORK_H_

#include <stdio.h>

#define TEST_UNUSED_INIT()                                                     \
  void init() {}
#define TEST_UNUSED_CLEANUP()                                                  \
  void cleanup() {}
#define TEST_UNUSED_FILE()                                                     \
  TEST_UNUSED_INIT()                                                           \
  TEST_UNUSED_CLEANUP()                                                        \
  struct test *register_tests() {                                              \
    return 0;                                                                  \
  }

#define TEST_EQ(a, b) (a) - (b)
#define TEST_NEQ(a, b) (a) == (b)
#define OR *
#define AND +

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

#define print(s, ...) printf("[everest/test] " s, __VA_ARGS__)

int main(int argc, char *argv[]) {
  struct test *tests = register_tests();
  if (!tests)
    return 0;
  init();
  cleanup();

  if (argc < 1)
    return 0;
  print("Running suite: %s\n", argv[0]);

  // count tests
  unsigned num_tests;
  for (num_tests = 0; tests[num_tests].name; ++num_tests)
    ;

  for (unsigned i = 0; i < num_tests; ++i) {
    char const *name = tests[i].name;
    p_test_f f = tests[i].func;
    int result = f();
    print("[%02d/%02d] %s <== %s\n", i + 1, num_tests, result ? "Fail" : "Pass",
          name);
    if (result) {
      return result;
    }
  }
}
