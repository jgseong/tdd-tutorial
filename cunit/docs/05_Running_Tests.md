# Running Tests

## Synopsis

```c
#include <CUnit/Automated.h>
void         CU_automated_run_tests(void);
CU_ErrorCode CU_list_tests_to_file(void);
void         CU_set_output_filename(const char* szFilenameRoot);

#include <CUnit/Basic.h>
typedef enum    CU_BasicRunMode;
CU_ErrorCode    CU_basic_run_tests(void);
CU_ErrorCode    CU_basic_run_suite(CU_pSuite pSuite);
CU_ErrorCode    CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest);
void            CU_basic_set_mode(CU_BasicRunMode mode);
CU_BasicRunMode CU_basic_get_mode(void);
void            CU_basic_show_failures(CU_pFailureRecord pFailure);

#include <CUnit/Console.h>
void CU_console_run_tests(void);

#include <CUnit/CUCurses.h>
void CU_curses_run_tests(void);

#include <CUnit/TestRun.h> // (included automatically by <CUnit/CUnit.h>)
unsigned int CU_get_number_of_suites_run(void);
unsigned int CU_get_number_of_suites_failed(void);
unsigned int CU_get_number_of_tests_run(void);
unsigned int CU_get_number_of_tests_failed(void);
unsigned int CU_get_number_of_asserts(void);
unsigned int CU_get_number_of_successes(void);
unsigned int CU_get_number_of_failures(void);

typedef struct CU_RunSummary;
typedef CU_Runsummary* CU_pRunSummary;
const CU_pRunSummary CU_get_run_summary(void);

typedef struct CU_FailureRecord;
typedef CU_FailureRecord*  CU_pFailureRecord;
const CU_pFailureRecord CU_get_failure_list(void);
unsigned int CU_get_number_of_failure_records(void);
```

## Running Tests in CUnit

CUnit supports running all tests in all registered suites, but individual tests or suites can also be run.
* During each run, the framework keeps track of the number of suites, tests, and assertions run, passed, and failed.
* Note that the results are cleared each time a test run is initiated (even if it fails).
* While CUnit provides primitive functions for running suites and tests, most users will want to use one of the simplified user interfaces.

These interfaces handle the details of interaction with the framework and provide output of test details and results for the user.

The following interfaces are included in the CUnit library:
|Interface|Platform|Description|
|---|:---:|---|
|Automated|all|non-interactive with output to xml files|
|Basic|all|non-interactive with optional output to stdout|
|Console|all|interactive console mode under user control|
|Curses|Linux/Unix|interactive curses mode under user control|

If these interfaces are not sufficient, clients can also use the primitive framework API defined in <CUnit/TestRun.h>.
* See the source code for the various interfaces for examples of how to interact with the primitive API directly.

## Automated Mode

* The automated interface is `non-interactive`. 
* Clients initiate a test run, and the results are output to an XML file.
* A listing of the registered tests and suites can also be reported to an XML file.

The following functions comprise the automated interface API:

```c
void CU_automated_run_tests(void);
```
Runs all tests in all registered suites.
* Test results are output to a file named `ROOT-Results.xml`.
* The filename ROOT can be set using `CU_set_output_filename()`, or else the default `CUnitAutomated-Results.xml` is used. 
* Note that if a distict filename ROOT is not set before each run, the results file will be overwritten.
* The results file is supported by both a document type definition file (CUnit-Run.dtd) and XSL stylesheet (CUnit-Run.xsl).
* These are provided in the Share subdirectory of the source and installation trees.

```c
CU_ErrorCode CU_list_tests_to_file(void)
```
Lists the registered suites and associated tests to file. 
* The listing file is named `ROOT-Listing.xml`.
* The filename ROOT can be set using `CU_set_output_filename()`, or else the default CUnitAutomated is used.
* Note that if a distict filename ROOT is not set before each run, the listing file will be overwritten.
* The listing file is supported by both a document type definition file (CUnit-List.dtd) and XSL stylesheet (CUnit-List.xsl).
* These are provided in the Share subdirectory of the source and installation trees.
* Note also that a listing file is not generated automatically by `CU_automated_run_tests()`. 
* Client code must explicitly request a listing when one is desired.

```c
void CU_set_output_filename(const char* szFilenameRoot)
```
Sets the output filenames for the results and listing files. 
* `szFilenameRoot` is used to construct the filenames by appending `-Results.xml` and `-Listing.xml`, respectively.

## Basic Mode

* The basic interface is also non-interactive, with results output to stdout.
* This interface supports running individual suites or tests, and allows client code to control the type of output displayed during each run.
* This interface provides the most flexibility to clients desiring simplified access to the CUnit API.

The following public functions are provided:

```c
CU_ErrorCode CU_basic_run_tests(void);
```
* Runs all tests in all registered suites.
* Returns the 1st error code occurring during the test run.
* The type of output is controlled by the current run mode, which can be set using `CU_basic_set_mode()`.

```c
CU_ErrorCode CU_basic_run_suite(CU_pSuite pSuite);
```
* Runs all tests in single specified suite.
* Returns the 1st error code occurring during the test run.
* The type of output is controlled by the current run mode, which can be set using `CU_basic_set_mode()`.

```c
CU_ErrorCode CU_basic_run_test(CU_pSuite pSuite, CU_pTest pTest);
```
* Runs a single test in a specified suite.
* Returns the 1st error code occurring during the test run.
* The type of output is controlled by the current run mode, which can be set using `CU_basic_set_mode()`.

```c
void CU_basic_set_mode(CU_BasicRunMode mode);
```
* Sets the basic run mode, which controls the output during test runs.
* Choices are:
|mode|description|
|---|---|
|CU_BRM_NORMAL|Failures and run summary are printed.|
|CU_BRM_SILENT|No output is printed except error messages.|
|CU_BRM_VERBOSE|Maximum output of run details.|

```c
CU_BasicRunMode CU_basic_get_mode(void);
```
* Retrieves the current basic run mode code.

```c
void CU_basic_show_failures(CU_pFailureRecord pFailure);
```
* Prints a summary of all failures to stdout. Does not depend on the run mode.

## Interactive Console Mode

```c
void CU_console_run_tests(void);
```
* The console interface is interactive.
* All the client needs to do is initiate the console session, and the user controls the test run interactively.
* This include selection & running of registered suites and tests, and viewing test results. To start a console session, use `CU_console_run_tests()`

## Interactive Curses Mode

```c
void CU_curses_run_tests(void);
```
* The curses interface is interactive.
* All the client needs to do is initiate the curses session, and the user controls the test run interactively.
* This include selection & running of registered suites and tests, and viewing test results.
* Use of this interface requires linking the ncurses library into the application. To start a curses session, use `CU_curses_run_tests()`;

##  Getting Test Results

* The interfaces present results of test runs, 
  * but client code may sometimes need to access the results directly. 
* These results include various run counts, as well as a linked list of failure records holding the failure details.
* Note that test results are overwritten each time a new test run is started, or when the registry is initialized or cleaned up.

Functions for accessing the test results are:
```c
unsigned int CU_get_number_of_suites_run(void);
unsigned int CU_get_number_of_suites_failed(void);
unsigned int CU_get_number_of_tests_run(void);
unsigned int CU_get_number_of_tests_failed(void);
unsigned int CU_get_number_of_asserts(void);
unsigned int CU_get_number_of_successes(void);
unsigned int CU_get_number_of_failures(void);
```

* These functions report the number of suites, tests, and assertions that ran or failed during the last run.
* A suite is considered failed if it's initialization or cleanup function returned `non-NULL`.
* A test fails if any of its assertions fail. The last 3 functions all refer to individual assertions.

To retrieve the total number of registered suites and tests, use `CU_get_registry()−>uiNumberOfSuites` and `CU_get_registry()−>uiNumberOfTests`, respectively.

```c
const CU_pRunSummary CU_get_run_summary(void);
```
* Retrieves all test result counts at once.
* The return value is a pointer to a saved structure containing the counts.
* This data type is defined in `<CUnit/TestRun.h>` (included automatically by `<CUnit/CUnit.h>`):

```c
typedef struct CU_RunSummary
{
  unsigned int nSuitesRun;
  unsigned int nSuitesFailed;
  unsigned int nTestsRun;
  unsigned int nTestsFailed;
  unsigned int nAsserts;
  unsigned int nAssertsFailed;
  unsigned int nFailureRecords;
} CU_RunSummary;

typedef CU_Runsummary* CU_pRunSummary;
```
* The structure variable associated with the returned pointer is owned by the framework, so the user should not free or otherwise change it.
* Note that the pointer may be invalidated once another test run is initiated.

```c
const CU_pFailureRecord CU_get_failure_list(void)
```
* Retrieves a linked list recording any failures occurring during the last test run (NULL for no failures).
* The data type of the return value is declared in `<CUnit/TestRun.h>` (included automatically by `<CUnit/CUnit.h>`).
* Each failure record contains information about the location and nature of the failure:
```c
typedef struct CU_FailureRecord
{
  unsigned int  uiLineNumber;
  char*         strFileName;
  char*         strCondition;
  CU_pTest      pTest;
  CU_pSuite     pSuite;

  struct CU_FailureRecord* pNext;
  struct CU_FailureRecord* pPrev;

} CU_FailureRecord;

typedef CU_FailureRecord*  CU_pFailureRecord;
```
* The structure variable associated with the returned pointer is owned by the framework, so the user should not free or otherwise change it.
* Note that the pointer may be invalidated once another test run is initiated.

```c
unsigned int CU_get_number_of_failure_records(void)
```
* Retrieves the number of `CU_FailureRecords` in the linked list of failures returned by `CU_get_failure_list()`.
* Note that this can be more than the number of failed assertions, since suite initialization and cleanup failures are included.

## Deprecated v1 Data Types & Functions

The following data types and functions are deprecated as of version 2. To use these deprecated names, user code must be compiled with `USE_DEPRECATED_CUNIT_NAMES` defined.

|Deprecated Name|Equivalent New Name|
|---|---|
|automated_run_tests()|CU_automated_run_tests() plus CU_list_tests_to_file()|
|set_output_filename()|CU_set_output_filename()|
|console_run_tests()|CU_console_run_tests()|
|curses_run_tests()|CU_curses_run_tests()|
