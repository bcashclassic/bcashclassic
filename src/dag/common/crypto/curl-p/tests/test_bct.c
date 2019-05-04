/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <unity/unity.h>

#include "common/crypto/curl-p/bct.h"
#include "common/trinary/bct.h"

//{0b101101, 0b010110}
// 0b10011011, 0b0110 < backwards
//
// 0b101101,
// 0b010110
#define TRITS_IN 0b01111001, 0b0110

#define CURL_P_27_EXP                                                                                                  \
  1, 1, -1, 0, 1, 1, -1, 1, 0, -1, 0, 1, -1, 1, 0, 1, 0, 1, -1, -1, 0, -1, 1, -1, 1, -1, 1, 1, -1, 1, -1, -1, -1, 0,   \
      0, -1, -1, -1, 1, 1, 1, -1, 1, -1, 0, 1, 0, -1, 0, 0, 1, 1, -1, 1, -1, 1, 1, 1, 1, -1, -1, 1, 0, -1, 0, 1, 1, 1, \
      1, 0, 1, 0, 0, 0, -1, 1, -1, -1, -1, 0, 0, 1, -1, 0, 0, 0, 0, -1, 1, 1, -1, 1, -1, -1, 0, 1, -1, 1, 0, 1, -1, 0, \
      0, 1, -1, 0, -1, 0, 1, 1, 1, 0, -1, 1, 0, 1, 0, -1, 0, 0, -1, 0, -1, 1, 0, 1, -1, 1, 0, -1, -1, 0, -1, 1, -1, 1, \
      -1, -1, 0, -1, 1, -1, 0, -1, 1, 1, -1, 1, 1, 0, 1, 1, 1, -1, -1, 0, 0, 0, -1, -1, -1, -1, 1, 1, 0, 0, 1, -1, -1, \
      0, -1, -1, -1, 0, -1, 0, -1, 1, 1, 0, 1, 0, 0, 0, -1, -1, 0, -1, 1, -1, -1, 1, -1, 1, -1, 1, -1, 0, -1, 0, 1, 0, \
      -1, -1, -1, 1, -1, 1, 0, 0, -1, 0, 1, 1, 1, 0, 0, -1, -1, 1, 0, 1, 0, -1, -1, -1, 1, 0, 0, -1, 0, 1, 0, 0, -1,   \
      0, 0, 1, -1, 0, 0, -1, -1
#define CURL_P_81_EXP                                                                                                  \
  1, 1, 0, 0, 0, 0, -1, 0, 0, -1, 0, 0, 1, 1, -1, 0, 1, 1, 0, 0, 1, 1, 0, 1, -1, 0, -1, 0, -1, 0, -1, 0, -1, 0, 0, 1,  \
      -1, 1, -1, 1, 1, -1, -1, -1, 1, 0, -1, -1, 0, 0, 1, -1, 1, -1, -1, -1, 1, 1, -1, 0, 1, -1, 0, 1, 0, 1, 1, 1, -1, \
      -1, 0, -1, -1, 0, 1, -1, 0, 1, 1, -1, -1, 1, 0, 1, -1, -1, 1, 0, 1, 0, 1, 1, -1, 0, -1, 1, -1, -1, -1, 0, 0, 0,  \
      -1, -1, -1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, -1, -1, 1, 0, 0, 1, 1, 1, -1, 0, -1, 0, 1, 0, 0, 1, -1, -1, -1,  \
      0, 0, 1, -1, -1, 1, 0, -1, 0, 1, -1, -1, -1, 0, -1, 1, 0, 0, -1, 0, 0, -1, 0, -1, 0, -1, 1, 1, 1, -1, 1, -1, 0,  \
      1, 1, 1, 1, -1, 0, 0, 1, -1, 0, 0, 1, 0, 1, -1, 1, 1, -1, 1, 1, 0, -1, 1, 1, -1, 0, 1, 1, -1, -1, 0, 1, 1, 0,    \
      -1, 0, -1, 1, -1, -1, -1, 0, -1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, -1, -1, 1, -1, 1, -1, 1, 1, 0, 0, 1, 0, 0, 1, -1, \
      0, -1, 0, -1, 0, 0
/*
#define CURL_P_27_EXP 0, 0, 1, -1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0,
-1, -1, -1, 1, 0, 1, 1, 1, 0, 1, -1, -1, 0, 1, 1, 0, 1, 1, -1, -1,  1, 0, 0, 1,
-1, 0, 0, -1, 1, 1, 1, 0, 0, 1, 1, -1, -1, -1, 0, 1, 1, 0, 0, -1, 0, 0, 0, 1, 1,
-1, 0, 0, 0, 1, 0, 1, -1, 1, 1, 1 , 0, 1, 1, 0, -1, 0, 0, -1, -1, -1, 1, -1, 1,
1, 1, 0, 1, -1, 1, 1, 1, 0, 0, 1, 0, 0, 1, -1, 1, 0, 1, 0, 1, -1, 0, 0, 1, 1,
-1,  0, -1, 0, 1, 1, -1, -1, 1, 1, -1, -1, 1, 0, 0, 1, 1, -1, 1, 0, 1, 0, 0, 0,
-1, 0, -1, -1, 0, 0, 1, 1, 0, 1, -1, 1, 0, -1, -1, 1, 1, -1, -1, 0, -1, 1, -1,
-1, -1, 0, -1, 0, 0, 1, 0, -1, -1, -1, -1, 1, 1, 1, 1, -1, 1, -1, -1, -1, 0, -1,
1, -1, 1, -1, 0, 0 , -1, 1, 1, 0, 1, 0, 1, 1, -1, 0, -1, 1, -1, 1, 0, -1, 1, -1,
-1, -1, -1, -1, 1, 1, 1, -1, 0, -1, -1, 1, 0, 1, 0, 1, 1, 0, 0, 1 , 0, 1, 0, -1,
1, -1, 1, 0, 0, 1, 1, 0 #define CURL_P_81_EXP 0, 0, -1, 0, 1, 1, -1, 1, 0, 0, 0,
1, 1, 0, 1, -1, -1, -1, -1, 1, 1, 0, 1, -1, 0, 1, -1 , 1, -1, 1, 0, 0, 1, 1, 0,
0, 1, 1, -1, -1, 0, 0, 1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 1, -1, 1, 0, 1, 1, 0, 0,
1, 1, 1, 0, 0, -1, 1 , 1, -1, 0, 1, 0, 1, -1, 0, 1, 0, 0, 0, 1, 0, 1, 1, -1, -1,
1, 0, -1, -1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, -1, -1, 1, 0, 0, 0, 0, 1, -1, 1, 0,
-1, 0, 0, -1, 0, -1, -1, -1, 0, 1, 1, 0, 1, -1, -1, 1, -1, 0, 1, 0, -1, -1, -1,
1, 1, -1, -1, 0, 1, 0, -1, -1, 1, 1, 1, 0, -1, -1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1,
0, -1, 1, 0, -1, 0, 1, 0, 0, -1, -1, -1, 1, -1, 0, 0, -1, 1, -1, 1, -1, 1, 1, 1,
-1, 0, 1, -1, 0, 1, 1, -1, 0, 0, -1, -1, 0, -1, 0, -1, 0, 0, -1, -1, 1, 1, -1,
-1, 0, 1, 0, -1, -1, -1, 0, 0, 1, 0, 0, -1, 0, 0, -1, 1, 1, -1, 1, 0, -1, 1, -1,
0, 0, 0, 1, 0, 1, -1, -1, -1, 1, 0, 0, -1, 1
*/

void run_curl_p_s_test(BCurl *curl, trit_t *exp) {
  bct_t trits[] = {TRITS_IN};
  bct_t hash[61];
  trit_t trit_hash[HASH_LENGTH_TRIT];

  s_curl_absorb(curl, trits, 0, 6);
  s_curl_squeeze(curl, hash, 0, HASH_LENGTH_TRIT);
  s_curl_reset(curl);

  copy_bct_to_trits(trit_hash, hash, 0, HASH_LENGTH_TRIT);
  TEST_ASSERT_EQUAL_INT8_ARRAY(exp, trit_hash, HASH_LENGTH_TRIT);
}

void test_curl_p_27_works(void) {
  BCurl curl;
  init_s_curl(&curl);
  curl.type = CURL_P_27;
  trit_t trits_exp[] = {CURL_P_27_EXP};
  run_curl_p_s_test(&curl, trits_exp);
  // Reset should work
  // run_curl_p_s_test(&curl, trits_exp);
}

void test_curl_p_81_works(void) {
  BCurl curl;
  init_s_curl(&curl);
  curl.type = CURL_P_81;
  trit_t trits_exp[] = {CURL_P_81_EXP};
  run_curl_p_s_test(&curl, trits_exp);
  // Reset should work
  // run_curl_p_s_test(&curl, trits_exp);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(test_curl_p_27_works);
  RUN_TEST(test_curl_p_81_works);
  // RUN_TEST(test_other);

  return UNITY_END();
}
