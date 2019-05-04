/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_CONTAINERS_HASH_HASH243_SET_H__
#define __UTILS_CONTAINERS_HASH_HASH243_SET_H__

#include "uthash.h"

#include "common/errors.h"
#include "common/trinary/flex_trit.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hash243_set_entry_s {
  flex_trit_t hash[FLEX_TRIT_SIZE_243];
  UT_hash_handle hh;
} hash243_set_entry_t;

typedef hash243_set_entry_t *hash243_set_t;

typedef retcode_t (*hash243_on_container_func)(void *container,
                                                 flex_trit_t *hash);

uint32_t hash243_set_size(hash243_set_t const *const set);
retcode_t hash243_set_add(hash243_set_t *const set,
                            flex_trit_t const *const hash);
retcode_t hash243_set_remove(hash243_set_t *const set,
                                flex_trit_t const *const hash);
retcode_t hash243_set_remove_entry(hash243_set_t *const set,
                                      hash243_set_entry_t *const entry);
retcode_t hash243_set_append(hash243_set_t const *const set1,
                               hash243_set_t *const set2);
bool hash243_set_contains(hash243_set_t const *const set,
                            flex_trit_t const *const hash);
bool hash243_set_find(hash243_set_t const *const set,
        flex_trit_t const *const hash, hash243_set_entry_t const ** entry);
void hash243_set_free(hash243_set_t *const set);
retcode_t hash243_set_for_each(hash243_set_t const *const set,
                                 hash243_on_container_func func,
                                 void *const container);
retcode_t hash243_set_random_hash(hash243_set_t const *const set,
                                     flex_trit_t *const hash);

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_CONTAINERS_HASH_HASH243_SET_H__
