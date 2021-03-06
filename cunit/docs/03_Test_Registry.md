# The Test Registry

## Synopsis

```c
#include <CUnit/TestDB.h> // included automatically by <CUnit/CUnit.h>

/* Declartions */
typedef struct CU_TestRegistry;
typedef CU_TestRegistry* CU_pTestRegistry;

CU_ErrorCode CU_initialize_registry(void);

void CU_cleanup_registry(void);

CU_pTestRegistry CU_get_registry(void);

CU_pTestRegistry CU_set_registry(CU_pTestRegistry pTestRegistry);

CU_pTestRegistry CU_create_new_registry(void);

void CU_destroy_existing_registry(CU_pTestRegistry* ppRegistry);
```

## Internal Structure

The test registry is the repository for suites and associated tests.
* CUnit maintains an active test registry
  * which is updated when the user adds a suite or test.
* The suites in this active registry are the ones run 
  * when the user chooses to run all tests.
* The CUnit test registry is a data structure
  * `CU_TestRegistry` declared in <CUnit/TestDB.h>.
  * It includes fields for the total numbers of suites and tests stored in the registry
  * As well as a pointer to the head of the linked list of registered suites.
  ```c
  typedef struct CU_TestRegistry
  {
    unsigned int uiNumberOfSuites;
    unsigned int uiNumberOfTests;
    CU_pSuite    pSuite;
  } CU_TestRegistry;

  typedef CU_TestRegistry* CU_pTestRegistry;
  ```
* The user normally only needs to initialize the registry
  * before use and clean up afterwards.
* However, other functions are provided to manipulate the registry when necessary.

## Initialization

The active CUnit test registry must be initialized before use. 
* The user should call `CU_initialize_registry()` before calling any other CUnit functions. 

### CU_initialize_registry()

* Failure to do so will likely result in a crash.
```c
CU_ErrorCode CU_initialize_registry(void);

/* An error status code is returned:

CUE_SUCCESS	   // initialization was successful.
CUE_NOMEMORY   // memory allocation failed.

*/
```

## Cleanup

When testing is complete, the user should call this function to clean up and release memory used by the framework. 

### CU_cleanup_registry()

This should be the last CUnit function called 
  * except for restoring the test registry using `CU_initialize_registry()` or `CU_set_registry()`.

```c
void CU_cleanup_registry(void);
```

* `Failure` to call `CU_cleanup_registry()` will result in memory leaks.
  * It may be called more than once without creating an error condition. 
  * Note that this function will destroy all suites (and associated tests) in the registry. 
  * Pointers to registered suites and tests should not be dereferenced after cleaning up the registry.

* Calling `CU_cleanup_registry()` will only affect the internal `CU_TestRegistry` maintained by the CUnit framework. 

Destruction of any other test registries owned by the user are the responsibility of the user. 
* This can be done explictly by calling `CU_destroy_existing_registry()`, or implicitly by making the registry active using `CU_set_registry()` and calling `CU_cleanup_registry()` again.

## Other Registry Functions

Other registry functions are provided primarily for internal and testing purposes. However, general users may find use for them and should be aware of them.

These include:

### CU_get_registry()
```c
CU_pTestRegistry CU_get_registry(void);
```

Returns a pointer to the active test registry. The registry is a variable of data type CU_TestRegistry. Direct manipulation of the internal test registry is not recommended - API functions should be used instead. The framework maintains ownership of the registry, so the returned pointer will be invalidated by a call to CU_cleanup_registry() or CU_initialize_registry().

### CU_set_registry()
```c
CU_pTestRegistry CU_set_registry(CU_pTestRegistry pTestRegistry)
```

Replaces the active registry with the specified one. A pointer to the previous registry is returned. It is the caller's responsibility to destroy the old registry. This can be done explictly by calling CU_destroy_existing_registry() for the returned pointer. Alternatively, the registry can be made active using CU_set_registry() and destroyed implicitly when CU_cleanup_registry() is called. Care should be taken not to explicitly destroy a registry that is set as the active one. This can result in multiple frees of the same memory and a likely crash.

### CU_create_new_registry()
```c
CU_pTestRegistry CU_create_new_registry(void)
```

Creates a new registry and returns a pointer to it. The new registry will not contain any suites or tests. It is the caller's responsibility to destroy the new registry by one of the mechanisms described previously.

### CU_destroy_existing_registry()
```c
void CU_destroy_existing_registry(CU_pTestRegistry* ppRegistry)
```

Destroys and frees all memory for the specified test registry, including any registered suites and tests. This function should not be called for a registry which is set as the active test registry (e.g. a CU_pTestRegistry pointer retrieved using CU_get_registry()). This will result in a multiple free of the same memory when CU_cleanup_registry() is called. Calling this function with NULL has no effect.

## Deprecated v1 Data Types & Functions

The following data types and functions are deprecated as of version 2. To use these deprecated names, user code must be compiled with USE_DEPRECATED_CUNIT_NAMES defined.
```c
#include <CUnit/TestDB.h> (included automatically by CUnit/CUnit.h>).
```

|Deprecated Name|Equivalent New Name|
|---|---|
|_TestRegistry|CU_TestRegistry|
|_TestRegistry.uiNumberOfGroups|CU_TestRegistry.uiNumberOfSuites|
|PTestRegistry->uiNumberOfGroups|CU_pTestRegistry->uiNumberOfSuites|
|_TestRegistry.pGroup|CU_TestRegistry.pSuite|
|PTestRegistry->pGroup|CU_pTestRegistry->pSuite|
|PTestRegistry|CU_pTestRegistry|
|initialize_registry()|CU_initialize_registry()|
|cleanup_registry()|CU_cleanup_registry()|
|get_registry()|CU_get_registry()|
|set_registry()|CU_set_registry()|