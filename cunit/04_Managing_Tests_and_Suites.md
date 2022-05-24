# Managing Test & Suites

In order for a test fo be run by CUnit, it must be added to a test collection (suite) which is registered with the test registry

## Synopsis

```c
#include <CUnit/TestDB.h> // (included automatically by <CUnit/CUnit.h>)

typedef struct CU_Suite;
typedef CU_Suite*  CU_pSuite;

typedef struct CU_Test;
typedef CU_Test*  CU_pTest;

typedef void (*CU_TestFunc)(void);
typedef int  (*CU_InitializeFunc)(void);
typedef int  (*CU_CleanupFunc)(void);

CU_pSuite CU_add_suite(const char* strName,
                        CU_InitializeFunc pInit,
                        CU_CleanupFunc pClean);

CU_pTest  CU_add_test(CU_pSuite pSuite,
                      const char* strName,
                      CU_TestFunc pTestFunc);

typedef struct CU_TestInfo;
typedef struct CU_SuiteInfo;

CU_ErrorCode CU_register_suites(CU_SuiteInfo suite_info[]);
CU_ErrorCode CU_register_nsuites(int suite_count, ...);
```

##  Adding Suites to the Registry

```c
CU_pSuite CU_add_suite(const char* strName, CU_InitializeFunc pInit, CU_CleanupFunc pClean);
```

Creates a new test collection (suite): 
* `strName` = having the specified name, 
* `pInit` = initialization function, 
* `pClean` = and cleanup function. 

The new suite is registered with (and owned by) the test registry, 
* so the registry must be initialized before adding any suites.
> The current implementation does not support the creation of suites independent of the test registry.
* The suite's name must be unique among all suites in the registry.
* The initialization and cleanup functions are **optional**, 
  * and are passed as pointers to functions to be called before and after running the tests contained in the suite. 
  * This allows the suite to set up and tear down temporary fixtures to support running the tests. 
  * These functions take **no arguments** and should return **zero** if they are completed successfully (non-zero otherwise).
  * If a suite does not require one or both of these functions, pass `NULL` to `CU_add_suite()`.

A pointer to the new suite is returned, 
* which is needed for adding tests to the suite. 
* If an error occurs, `NULL` is returned and the framework error code is set to one of the following:
| error code | description |
|---|---|
| CUE_SUCCESS	| suite creation was successful. |
| CUE_NOREGISTRY | the registry has not been initialized. |
| CUE_NO_SUITENAME | strName was NULL. |
| CUE_DUP_SUITE	| the suite's name was not unique. |
| CUE_NOMEMORY | memory allocation failed. |

## Adding Tests to Suites

```c
CU_pTest CU_add_test(CU_pSuite pSuite, const char* strName, CU_TestFunc pTestFunc);
```

Creates a new test having the specified name and test function, and registers it with the specified suite.
* The suite must already have been created using `CU_add_suite()`.
> The current implementation does not support the creation of tests independent of a registered suite.
* The test's name must be unique among all tests added to a single suite.
* The **test function cannot be NULL**, 
  * and points to a function to be called when the test is run. 
  * Test functions have neither arguments nor return values. `void`

A pointer to the new test is returned.
If an error occurs during creation of the test, `NULL` is returned and the framework error code is set to one of the following:

| error code | description |
|---|---|
| CUE_SUCCESS | suite creation was successful. |
| CUE_NOSUITE | the specified suite was NULL or invalid. |
| CUE_NO_TESTNAME | strName was NULL. |
| CUE_NO_TEST | pTestFunc was NULL or invalid. |
| CUE_DUP_TEST | the test's name was not unique. |
| CUE_NOMEMORY | memory allocation failed. |

## Shortcut Methods for Managing Tests

```c
#define CU_ADD_TEST(suite, test) (CU_add_test(suite, #test, (CU_TestFunc)test))
```

This macro automatically generates a unique test name based on the test function name, and adds it to the specified suite.
The return value should be checked by the user to verify success.

```c
CU_ErrorCode CU_register_suites(CU_SuiteInfo suite_info[]);
CU_ErrorCode CU_register_nsuites(int suite_count, ...); // arg. is CU_SuiteInfo
```

For large test structures with many tests and suites, managing test/suite associations and registration is tedious and error-prone. 

CUnit provides a special registration system to help manage suites and tests.
It's primary benefit is to centralize the registration of suites and associated tests, and to minimize the amount of error checking code the user needs to write.

Test cases are first grouped into arrays of `CU_TestInfo` instances (defined in <CUnit/TestDB.h>):
```c
CU_TestInfo test_array1[] = {
  { "testname1", test_func1 },
  { "testname2", test_func2 },
  { "testname3", test_func3 },
  CU_TEST_INFO_NULL,
};
```

Each array element contains the (unique) name and test function for a single test case.
The array must end with an element holding NULL values,
* which the macro CU_TEST_INFO_NULL conveniently defines.
* The test cases included in a single `CU_TestInfo` array form the set of tests that will be registered with a single test suite.

Suite information is then defined in one or more arrays of CU_SuiteInfo instances (defined in <CUnit/TestDB.h>):
```c
CU_SuiteInfo suites[] = {
  { "suitename1", suite1_init-func, suite1_cleanup_func, test_array1 },
  { "suitename2", suite2_init-func, suite2_cleanup_func, test_array2 },
  CU_SUITE_INFO_NULL,
};
```
Each of these array elements contain the (unique) name, suite initialization function, suite cleanup function, and `CU_TestInfo` array for a single suite.
As usual, NULL may be used for the initialization or cleanup function if the given suite does not need it.
The array must end with an all-NULL element, for which the macro `CU_SUITE_INFO_NULL` may be used.

All suites defined in a `CU_SuiteInfo` array can then be registered in a single statement:
```c
CU_ErrorCode error = CU_register_suites(suites);
```

If an error occurs during the registration of any suite or test, an error code is returned. The error codes are the same as those returned by normal suite registration and test addition operations.
The function `CU_register_nsuites()` is provided for situations in which the user wishes to register multiple `CU_SuiteInfo` arrays in a single statement:
```c
CU_ErrorCode error = CU_register_nsuites(2, suites1, suites2);
```

This function accepts a variable number of `CU_SuiteInfo` arrays. The first argument indicates the actual number ot arrays being passed.

## Deprecated v1 Data Types & Functions
The following data types and functions are deprecated as of version 2. To use these deprecated names, user code must be compiled with USE_DEPRECATED_CUNIT_NAMES defined.
#include <CUnit/TestDB.h> (included automatically by CUnit/CUnit.h>).

| Deprecated Name	| Equivalent New Name |
|---|---|
| TestFunc | CU_TestFunc |
| InitializeFunc|CU_InitializeFunc|
|CleanupFunc|CU_CleanupFunc|
|_TestCase|CU_Test|
|PTestCase|CU_pTest|
|_TestGroup|CU_Suite|
|PTestGroup|CU_pSuite|
|add_test_group()|CU_add_suite()|
|add_test_case()|CU_add_test()|
|ADD_TEST_TO_GROUP()|CU_ADD_TEST()|
|test_case_t|CU_TestInfo|
|test_group_t|CU_SuiteInfo|
|test_suite_t|no equivalent - use CU_SuiteInfo|
|TEST_CASE_NULL|CU_TEST_INFO_NULL|
|TEST_GROUP_NULL|CU_SUITE_INFO_NULL|
|test_group_register|CU_register_suites()|
|test_suite_register|no equivalent - use CU_register_suites()|
