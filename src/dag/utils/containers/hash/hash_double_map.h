/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_CONTAINERS_HASH_HASHdouble_MAP_H__
#define __UTILS_CONTAINERS_HASH_HASHdouble_MAP_H__

#include "uthash.h"

#include "common/errors.h"
#include "common/trinary/flex_trit.h"
#include "utils/containers/hash/hash243_set.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hash_to_double_map_entry_s {
    flex_trit_t hash[FLEX_TRIT_SIZE_243];
    double value;
    UT_hash_handle hh;
} hash_to_double_map_entry_t;

typedef hash_to_double_map_entry_t *hash_to_double_map_t;

retcode_t hash_to_double_map_add(hash_to_double_map_t *const map,
        flex_trit_t const *const hash,
double const value);
bool hash_to_double_map_contains(hash_to_double_map_t const *const map,
        flex_trit_t const *const hash);
bool hash_to_double_map_find(hash_to_double_map_t const *const map,
        flex_trit_t const *const hash,
hash_to_double_map_entry_t ** const res);
void hash_to_double_map_free(hash_to_double_map_t *const map);
void hash_to_double_map_keys(hash_to_double_map_t *const map,
                             hash243_set_t * const keys);

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_CONTAINERS_HASH_HASHdouble_MAP_H__
