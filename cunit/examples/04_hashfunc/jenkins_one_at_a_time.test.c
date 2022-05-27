#include "CUnit/CUnit.h"
#include "hash_functions.h"

// Defined functions:
/*

uint32_t 
jenkins_one_at_a_time_hash(const uint8_t* key, size_t length);

*/

void test_jenkins_one_at_a_time(void) 
{
  tc_t tc[] = {
    {(uint8_t*)"a", 1, 0xca2e9442},
    {(uint8_t*)"The quick brown fox jumps over the lazy dog", 43, 0x519e91f5},
  };
  size_t num_tc = 2;

  for (size_t i = 0; i < num_tc; i++) {
    CU_ASSERT_EQUAL(jenkins_one_at_a_time_hash(tc[i].args, tc[i].len), tc[i].expect);
  }

  return;
}