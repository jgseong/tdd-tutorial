# Writing CUnit Test Cases

## Test Functions

A CUnit 'test' is C function having the signature:
```c
void test_func(void)
```
There are no restrictions on the content of a test function, except that it should not modify the CUnit framework 
* `e.g.` add suites or tests, modify the test registry, or initiate a test run.
* A test function may call other functions 
  * which also may not modify the framework. 
* Registering a test will cause it's function to be run when the test is run.
* An example test function for a routine that returns the maximum of 2 integers might look like:
```c
int maxi(int i1, int i2)
{
  return (i1 > i2) ? i1 : i2;
}

void test_maxi(void)
{
  CU_ASSERT(maxi(0,2) == 2);
  CU_ASSERT(maxi(0,-2) == 0);
  CU_ASSERT(maxi(2,2) == 2);
}
```

## CUnit Assertions

CUnit provides **a set of assertions for testing logical conditions**. 
* The success or failure of these assertions is tracked by the framework, and can be viewed when a test run is complete.
* Each assertion tests 
  * a single logical condition, and fails if the condition evaluates to `FALSE`.
    * Upon failure, the test function continues unless the user chooses the `xxx_FATAL` version of an assertion. 
    * In that case, the test function is aborted and returns immediately.
  * `FATAL versions of assertions should be used with caution!` 
    * There is no opportunity for the test function to clean up after itself once a `FATAL` assertion fails. 
* The normal `suite cleanup function` is not affected, however.
* There are also special `"assertions"` for registering a `pass` or `fail` with the framework without performing a logical test. 
* These are useful for testing flow of control or other conditions not requiring a logical test:
```c
void test_longjmp(void)
{
  jmp_buf buf;
  int i;

  i = setjmp(buf);
  if (i == 0) {
    run_other_func();
    CU_PASS("run_other_func() succeeded.");
  }
  else
    CU_FAIL("run_other_func() issued longjmp.");
}
```
Other functions called by a registered test function may use the CUnit assertions freely.
* These assertions will be counted for the calling function. They may also use `FATAL` versions of assertions 
* failure will abort the original test function and its entire call chain.

### The assertions defined by CUnit are:
```c
#include <CUnit/CUnit.h>
```
#### Assert that `expression` is `TRUE` (non-zero)
```c
/* To assert when expression is true */
CU_ASSERT(int expression)
CU_ASSERT_FATAL(int expression)
CU_TEST(int expression)
CU_TEST_FATAL(int expression)
```
#### Assert that value is `TRUE` or `FALSE`
```c
/* expect to TRUE */
CU_ASSERT_TRUE(value)
CU_ASSERT_TRUE_FATAL(value)

/* expect to FALSE */
CU_ASSERT_FALSE(value)
CU_ASSERT_FALSE_FATAL(value)
```
#### Assert that equal to expected
```c
/* Assert that actual == expected */
CU_ASSERT_EQUAL(actual, expected)
CU_ASSERT_EQUAL_FATAL(actual, expected)

/* Assert that actual != expected */
CU_ASSERT_NOT_EQUAL(actual, expected))
CU_ASSERT_NOT_EQUAL_FATAL(actual, expected)
```
#### Assert that for pointers
```c
/* Assert that pointers actual == expected */
CU_ASSERT_PTR_EQUAL(actual, expected)
CU_ASSERT_PTR_EQUAL_FATAL(actual, expected)

/* Assert that pointers actual != expected */
CU_ASSERT_PTR_NOT_EQUAL(actual, expected)
CU_ASSERT_PTR_NOT_EQUAL_FATAL(actual, expected)

/* 	Assert that pointer value == NULL */
CU_ASSERT_PTR_NULL(value)
CU_ASSERT_PTR_NULL_FATAL(value)

/* Assert that pointer value != NULL */
CU_ASSERT_PTR_NOT_NULL(value)
CU_ASSERT_PTR_NOT_NULL_FATAL(value)
```
#### Assert that strings
```c
/* Assert that strings actual and expected are equivalent */
CU_ASSERT_STRING_EQUAL(actual, expected)
CU_ASSERT_STRING_EQUAL_FATAL(actual, expected)

/* Assert that strings actual and expected differ */
CU_ASSERT_STRING_NOT_EQUAL(actual, expected)
CU_ASSERT_STRING_NOT_EQUAL_FATAL(actual, expected)

/* Assert that 1st count chars of actual and expected are the same */
CU_ASSERT_NSTRING_EQUAL(actual, expected, count)
CU_ASSERT_NSTRING_EQUAL_FATAL(actual, expected, count)

/* Assert that 1st count chars of actual and expected differ */
CU_ASSERT_NSTRING_NOT_EQUAL(actual, expected, count)
CU_ASSERT_NSTRING_NOT_EQUAL_FATAL(actual, expected, count)
```
#### Assert that double type
* `Math library` must be linked in for this assertion. 
  * To compile with `-lm` (math)
```c
/* Assert that |actual - expected| <= |granularity| */
CU_ASSERT_DOUBLE_EQUAL(actual, expected, granularity)
CU_ASSERT_DOUBLE_EQUAL_FATAL(actual, expected, granularity)

/* Assert that |actual - expected| > |granularity| */
CU_ASSERT_DOUBLE_NOT_EQUAL(actual, expected, granularity)
CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL(actual, expected, granularity)
```
#### CU_PASS, CU_FAIL, CU_FAIL_FATAL
* Register a passing assertion or failed with the specified message. 
* No logical test is performed.
```c
/* Pass Test*/
CU_PASS(message)

/* Failure Test*/
CU_FAIL(message)
CU_FAIL_FATAL(message) /* FATAL */
```

## Depecated v1 Assertions
The following assertions are deprecated as of version 2. To use these assertions, user code must be compiled with `USE_DEPRECATED_CUNIT_NAMES` defined. Note that they behave the same as in version 1 (issue a `'return'` statement upon failure).
```c
#include <CUnit/CUnit.h>
```
|Deprecated MACRO|Equivalent MACRO|
|---|---|
|ASSERT|CU_ASSERT_FATAL|
|ASSERT_TRUE|CU_ASSERT_TRUE_FATAL|
|ASSERT_FALSE|CU_ASSERT_FALSE_FATAL|
|ASSERT_EQUAL|CU_ASSERT_EQUAL_FATAL|
|ASSERT_NOT_EQUAL|CU_ASSERT_NOT_EQUAL_FATAL|
|ASSERT_PTR_EQUAL|CU_ASSERT_PTR_EQUAL_FATAL|
|ASSERT_PTR_NOT_EQUAL|CU_ASSERT_PTR_NOT_EQUAL_FATAL|
|ASSERT_PTR_NULL|CU_ASSERT_PTR_NULL_FATAL|
|ASSERT_PTR_NOT_NULL|CU_ASSERT_PTR_NOT_NULL_FATAL|
|ASSERT_STRING_EQUAL|CU_ASSERT_STRING_EQUAL_FATAL|
|ASSERT_STRING_NOT_EQUAL|CU_ASSERT_STRING_NOT_EQUAL_FATAL|
|ASSERT_NSTRING_EQUAL|CU_ASSERT_NSTRING_EQUAL_FATAL|
|ASSERT_NSTRING_NOT_EQUAL|CU_ASSERT_NSTRING_NOT_EQUAL_FATAL|
|ASSERT_DOUBLE_EQUAL|CU_ASSERT_DOUBLE_EQUAL_FATAL|
|ASSERT_DOUBLE_NOT_EQUAL|CU_ASSERT_DOUBLE_NOT_EQUAL_FATAL|