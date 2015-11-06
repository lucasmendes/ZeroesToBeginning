/**
 * @Name        ZeroesToBeginning.cc
 * @Author      Lucas Martin Giacomini Mendes <lucasmendes@gmail.com>
 * @Version     1.0.0
 * @Copyright   GNU
 * @Description Move all zero values in a random array to its beginning
 *              This code follows Google C++ Style Guide:
 *              https://google.github.io/styleguide/cppguide.html
 */

#include <iostream>
#include <cstring>
using namespace std;

/**
 * Local prototypes
 */
int ZeroesToBeginningRuntimeOptimized(int array[], const int array_size);
int ZeroesToBeginningSpaceOptimized  (int array[], const int array_size);
int UnitTestPassScenario(
    int (*function_under_test)(int array[], const int array_size),
    const char *function_description);
int UnitTestFailScenario(
    int (*function_under_test)(int array[], const int array_size),
    const char *function_description);

/**
 * Main function is also the test fixture
 */
int main() {
  cout << endl << "Move all zero values in a random array to its beginning" << endl << endl;
  UnitTestPassScenario(ZeroesToBeginningRuntimeOptimized, "RuntimeOptimized");
  UnitTestFailScenario(ZeroesToBeginningRuntimeOptimized, "RuntimeOptimized");
  UnitTestPassScenario(ZeroesToBeginningSpaceOptimized,   "SpaceOptimized  ");
  UnitTestFailScenario(ZeroesToBeginningSpaceOptimized,   "SpaceOptimized  ");
  cout << endl << "Execution finished" << endl << endl;
  return 0;
}

/**
 * ZeroesToBeginningRuntimeOptimized
 * @brief 1st solution: Runtime optimized
 *
 * @note Average complexity    O(n)
 * @note Worst-case complexity O(n)
 * @note Because there are 2 independent loops that run anyway:
 * @note Main loop executes "array_size" times
 * @note memcpy internal loop executes "array_size" times
 * @note Which gives a linear complexity of O(n) for all cases
 */
int ZeroesToBeginningRuntimeOptimized(int array[], const int array_size) {
  // Sanity check
  if (array == NULL) {
    return -1;
  }
  if (array_size == 0) {
    return -1;
  }
  // To optimize runtime performance, do everything in a single pass with 2 arrays
  int *output_array = new int[array_size]();  // value-initialize with 0
  int next_output_array = array_size - 1;
  for (int i = array_size - 1; i >= 0; --i) {  // Main loop executes "array_size" times
    if (array[i] != 0) {
      // Move non-zeroes to end of output_array
      output_array[next_output_array] = array[i];
      --next_output_array;
    }
  }
  memcpy(array, output_array, array_size * sizeof(int));  // memcpy internal loop executes "array_size" times
  delete output_array;
  return 0;
}

/**
 * ZeroesToBeginningSpaceOptimized
 * @brief 2nd solution: space optimized
 *
 * @note Average complexity    O(n)
 * @note Worst-case complexity O(n)
 * @note Because there are 2 mutually-exclusive loops, with a total of "array_size" times:
 * @note Outer loop executes "number of non-zeroes" times
 * @note Inner loop executes "number of zeroes" times
 * @note Total = "array_size" times
 * @note Which gives a linear complexity of O(n) for all cases
 */
int ZeroesToBeginningSpaceOptimized(int array[], const int array_size) {
  // Sanity check
  if (array == NULL) {
    return -1;
  }
  if (array_size == 0) {
    return -1;
  }
  // To optimize space, use the same array as input and output
  int next_zero = 0;
  for (int i = array_size - 1; i > next_zero; --i) {        // Outer loop executes "number of non-zeroes" times
    if (array[i] == 0) {
      while ((array[next_zero] == 0) && (i > next_zero)) {  // Inner loop executes "number of zeroes" times
        ++next_zero;
      }
      // Swap positions
      array[i] = array[next_zero];
      array[next_zero] = 0;
    }
  }
  return 0;
}

/**
 * UnitTestPassScenario
 * 1st Unit Test: Pass Scenario
 */
int UnitTestPassScenario(
    int (*function_under_test)(int array[], const int array_size),
    const char *function_description) {
  bool pass = true;
  int test_array[10] = {1,2,3,4,5,6,7,8,0,0};
  // Many solutions can be correct. Only 2 are being tested here.
  const int expected_output_array_1[10] = {0,0,1,2,3,4,5,6,7,8};  // 1st solution
  const int expected_output_array_2[10] = {0,0,3,4,5,6,7,8,2,1};  // 2nd solution
  cout << "UnitTestPassScenario (" << function_description << ")... ";
  // Invoke function under test
  if (function_under_test(test_array, sizeof(test_array)/sizeof(int)) != 0) {
    pass = false;
  }
  // Validate function result
  if ((memcmp(test_array, expected_output_array_1, sizeof(test_array)) != 0) &&
      (memcmp(test_array, expected_output_array_2, sizeof(test_array)) != 0)) {
    pass = false;
  }
  // Evaluate test result
  if (pass == true) {
    cout << "Ok" << endl;
    return 0;
  } else {
    cout << "FAIL" << endl;
    return -1;
  }
}

/**
 * UnitTestFailScenario
 * 2nd Unit Test: Fail Scenario
 */
int UnitTestFailScenario(
    int (*function_under_test)(int array[], const int array_size),
    const char *function_description) {
  bool pass = true;
  cout << "UnitTestFailScenario (" << function_description << ")... ";
  // Invoke function under test
  if (function_under_test(NULL, 0) == 0) {  // Null arguments
    pass = false;
  }
  if (function_under_test(NULL, 1) == 0) {  // Null array
    pass = false;
  }
  if (function_under_test((int *) 1, 0) == 0) {  // Null array_size
    pass = false;
  }
  // Evaluate test result
  if (pass == true) {
    cout << "Ok" << endl;
    return 0;
  } else {
    cout << "FAIL" << endl;
    return -1;
  }
}
