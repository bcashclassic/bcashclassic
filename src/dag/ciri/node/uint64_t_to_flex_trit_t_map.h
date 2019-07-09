/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#ifndef __UTILS_CONTAINERS_uint64_t_flex_trit_t_MAP_H__
#define __UTILS_CONTAINERS_uint64_t_flex_trit_t_MAP_H__

#include <stdbool.h>

#include "uthash.h"
#include "common/errors.h"
#include "common/trinary/trits.h"
#include "common/trinary/flex_trit.h"

/*
 * This Generic map allows mapping any key type to any value type
 * assuming that key can be trivially copied, to allow for
 * user-defined types, user should add dependency in "map_generator.bzl"
 * and include the required files in this header file
 */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct uint64_t_to_flex_trit_t_map_entry_s {
  uint64_t *key;
  flex_trit_t *value;
  UT_hash_handle hh;
} uint64_t_to_flex_trit_t_map_entry_t;

typedef struct uint64_t_to_flex_trit_t_map_s {
  size_t key_size;
  size_t value_size;
  uint64_t_to_flex_trit_t_map_entry_t* map;
} uint64_t_to_flex_trit_t_map_t;

retcode_t uint64_t_to_flex_trit_t_map_init(uint64_t_to_flex_trit_t_map_t *const map,
                                              size_t const key_size, size_t const value_size);

size_t uint64_t_to_flex_trit_t_map_size(uint64_t_to_flex_trit_t_map_t const *const map);

retcode_t uint64_t_to_flex_trit_t_map_add(uint64_t_to_flex_trit_t_map_t *const map,
                                             uint64_t const *const key,
                                             flex_trit_t const *const value);

bool uint64_t_to_flex_trit_t_map_contains(uint64_t_to_flex_trit_t_map_t const *const map,
                                             uint64_t const *const key);

bool uint64_t_to_flex_trit_t_map_find(uint64_t_to_flex_trit_t_map_t const *const map,
                                         uint64_t const *const key,
                                         uint64_t_to_flex_trit_t_map_entry_t **const res);

retcode_t uint64_t_to_flex_trit_t_map_free(uint64_t_to_flex_trit_t_map_t *const map);

bool uint64_t_to_flex_trit_t_map_cmp(uint64_t_to_flex_trit_t_map_t const *const lhs,
                                        uint64_t_to_flex_trit_t_map_t const *const rhs);

bool uint64_t_to_flex_trit_t_map_remove(uint64_t_to_flex_trit_t_map_t *const map,
uint64_t const *const key);

retcode_t uint64_t_to_flex_trit_t_map_remove_entry(uint64_t_to_flex_trit_t_map_t *const map,
                                      uint64_t_to_flex_trit_t_map_entry_t *const entry);

#ifdef __cplusplus
}
#endif

#endif  // __UTILS_CONTAINERS_uint64_t_flex_trit_t_MAP_H__
