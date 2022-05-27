#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "hash_functions.h"

int main()
{
  tc_t tc[] = {
    {(uint8_t*)"a", 1, 0xca2e9442},
    {(uint8_t*)"The quick brown fox jumps over the lazy dog", 43, 0x519e91f5},
  };
  printf("0x%x\n", jenkins_one_at_a_time_hash(tc[0].args, tc[0].len));
  printf("0x%x\n", jenkins_one_at_a_time_hash(tc[1].args, tc[1].len));
}
