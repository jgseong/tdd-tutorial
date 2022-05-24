# CUnit

## Description

The simple framework for unit test in C
* Static library
* Build the test structures
* A rich set assertions for common data types
* Provide the several different interface for running test and reporting results.
  * Includes automated interfaces for code-controlled testing and reporting.
  * Provide the interactive interfaces allowing the user to run tests and view results dynamically.
* Header files for data tyeps and useful functions:
```c
#include <CUnit/CUnit.h>
/* ASSERT macros for use in test cases, and includes other framework headers. */

#include <CUnit/CUError.h>
/* Error handling functions and data types. Includes automatically by CUnit.h */

#include <CUnit/TestDB.h>
/* Data type definitions and manipulation functions for the test registry, suites, and tests. Included automatically by CUnit.h */

#include <CUnit/TestRun.h>
/* Data type definitions and functions for running tests and retrieving results. Included automatically by CUnit.h. */
#include <CUnit/Automated.h>
/* Automated interface with xml output. */

#include <CUnit/Basic.h>
/* Basic interface with non-interactive output to stdout. */

#include <CUnit/Console.h>
/* Interactive console interface. */

#include <CUnit/CUCurses.h>
/* Interactive console interface (*nix). */

#include <CUnit/Win.h>
/* Windows interface (not yet implemented). */
```

## Structure

* combination of a platform-independent frameworks
  * with various user interfaces.
* Provide the basic support for managing
  * A test registry
    * Suites
      * Test cases
* The user interfaces facilitate interaction with the framework to run tests and view results.
* CUnit is organized like a conventional unit testing framework:
```

                      Test Registry
                            |
             ------------------------------
             |                            |
          Suite '1'      . . . .       Suite 'N'
             |                            |
       ---------------             ---------------
       |             |             |             |
    Test '11' ... Test '1M'     Test 'N1' ... Test 'NM'
```
* Individual test cases are packaged into suites, 
  * which are registered with the active test registry. 
* Suites can have setup and teardown functions 
  * which are automatically called before and after running the suite's tests. 
* All suites/tests in the registry may be run using a single function call, or selected suites or tests can be run.

## General Usage

A typical sequence of steps for using the CUnit framework is:
1. Write functions for tests (and suite init/cleanup if necessary).
1. Initialize the test registry - `CU_initialize_registry()`
1. Add suites to the test registry - `CU_add_suite()`
1. Add tests to the suites - `CU_add_test()`
1. Run tests using an appropriate interface, e.g. `CU_console_run_tests`
1. Cleanup the test registry - `CU_cleanup_registry`

## Changes to the CUnit API in Version 2

* All public names in `CUnit` are now prefixed with `CU_`. 
  * This helps minimize clashes with names in user code. 
  * Note that earlier versions of CUnit used different names without this prefix. 
  * The older API names are deprecated but still supported. 
  * To use the older names, user code must now be compiled with `USE_DEPRECATED_CUNIT_NAMES` defined.
  * The deprecated API functions are described in the appropriate sections of the documentation.

