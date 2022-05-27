/*
 * hash functions declaration
 */

#include "jenkins_one_at_a_time.h"

struct tc_t{
  const uint8_t *args;
  size_t        len;
  uint32_t      expect;
};

typedef struct tc_t tc_t;

void test_jenkins_one_at_a_time(void);