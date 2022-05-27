/*
 * one_at_a_time
 * Jenkins's one_at_a_time hash is adapted here from a WWW page by Bob Jenkins,
 * which is an expanded version of his Dr. Dobb's article.
 *
 * It was originally created to fulfill certain requirements described by Colin Plumb, 
 * a cryptographer, but was ultimately not put to use.
 * The avalanche behavior of this hash is shown on the right.
 *
 * Each of the 24 rows corresponds to a single bit in the 3-byte input key, and each of 
 * the 32 columns corresponds to a bit in the output hash. Colors are chosen by how well 
 * the input key bit affects the given output hash bit: a green square indicates good 
 * mixing behavior, a yellow square weak mixing behavior, and red would indicate no mixing. 
 * 
 * Only a few bits in the last byte of the input key are weakly mixed to a minority of bits
 * in the output hash.
 *
 * Standard implementations of the Perl programming language prior to version 5.28 included Jenkins's 
 * one-at-a-time hash or a hardened variant of it, which was used by default.
 */

#include "jenkins_one_at_a_time.h"

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
  size_t i = 0;
  uint32_t hash = 0;
  while (i != length) {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}