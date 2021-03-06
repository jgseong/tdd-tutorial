# Error Handling

## Synopsis

```c
#include <CUnit/CUError.h> // (included automatically by <CUnit/CUnit.h>)

typedef enum CU_ErrorCode;
CU_ErrorCode   CU_get_error(void);
const char*    CU_get_error_msg(void);

typedef enum CU_ErrorAction;
void           CU_set_error_action(CU_ErrorAction action);
CU_ErrorAction CU_get_error_action(void);
```

## CUnit Error Handling
Most CUnit functions set an error code indicating the framework error status.
* Some functions return the code, while others just set the code and return some other value.
* Two functions are provided for examining the framework error status:
```c
CU_ErrorCode CU_get_error(void);
const char* CU_get_error_msg(void);
```

The first returns the error code itself, while the second returns a message describing the error status.

The error code is an enum of type `CU_ErrorCode` defined in `<CUnit/CUError.h>`. 

The following error code values are defined:

|Error Value|Description|
|---|---|
|CUE_SUCCESS|No error condition.|
|CUE_NOMEMORY|Memory allocation failed.|
|CUE_NOREGISTRY|Test registry not initialized.|
|CUE_REGISTRY_EXISTS|Attempt to CU_set_registry() without CU_cleanup_registry().|
|CUE_NOSUITE|A required CU_pSuite pointer was NULL.|
|CUE_NO_SUITENAME|Required CU_Suite name not provided.|
|CUE_SINIT_FAILED|Suite initialization failed.|
|CUE_SCLEAN_FAILED|Suite cleanup failed.|
|CUE_DUP_SUITE|Duplicate suite name not allowed.|
|CUE_NOTEST|A required CU_pTest pointer was NULL.|
|CUE_NO_TESTNAME|Required CU_Test name not provided.|
|CUE_DUP_TEST|Duplicate test case name not allowed.|
|CUE_TEST_NOT_IN_SUITE|Test is not registered in the specified suite.|
|CUE_FOPEN_FAILED|An error occurred opening a file.|
|CUE_FCLOSE_FAILED|An error occurred closing a file.|
|CUE_BAD_FILENAME|A bad filename was requested (NULL, empty, nonexistent, etc.).|
|CUE_WRITE_ERROR|An error occurred during a write to a file.|

## Behavior Upon Framework Errors

The default behavior when an error condition is encountered is for the error code to be set and execution continued.
There may be times when clients prefer for a test run to stop on a framework error, or even for the test application to exit.

This behavior can be set by the user, for which the following functions are provided:
```c
void CU_set_error_action(CU_ErrorAction action);
CU_ErrorAction CU_get_error_action(void);
```

The error action code is an enum of type `CU_ErrorAction` defined in `<CUnit/CUError.h>`. The following error action codes are defined:
|Error Value|Description|
|CUEA_IGNORE|Runs should be continued when an error condition occurs (default)|
|CUEA_FAIL|Runs should be stopped when an error condition occurs|
|CUEA_ABORT|The application should exit() when an error conditions occurs|

## Deprecated v1 Variables & Functions

The following variables and functions are deprecated as of version 2. To use these deprecated names, user code must be compiled with `USE_DEPRECATED_CUNIT_NAMES` defined.

|Deprecated Name|Equivalent New Name|
|---|---|
|get_error()|CU_get_error_msg()|
|error_code|None. Use CU_get_error()|
