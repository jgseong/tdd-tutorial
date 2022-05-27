#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_functions.h"

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"

int main()
{
   CU_TestInfo ts_basic[] = {
      {"test jenkins_one_at_a_time", test_jenkins_one_at_a_time},
      CU_TEST_INFO_NULL,
   };

   CU_SuiteInfo suites[] = {
      {"basic test set", NULL, NULL, NULL, NULL, ts_basic},
      CU_SUITE_INFO_NULL,
   };

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   CU_ErrorCode error = CU_register_suites(suites);
   if (error != CUE_SUCCESS) {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}