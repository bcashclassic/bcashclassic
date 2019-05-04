/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include "utils/containers/hash/hash243_set.h"
#include "utils/handles/rand.h"

uint32_t hash243_set_size(hash243_set_t const *const set) {
  return HASH_COUNT(*set);
}

retcode_t hash243_set_add(hash243_set_t *const set,
                            flex_trit_t const *const hash) {
  hash243_set_entry_t *entry = NULL;

  if (!hash243_set_contains(set, hash)) {
    if ((entry = (hash243_set_entry_t *)malloc(sizeof(hash243_set_entry_t))) == NULL) {
      return RC_UTILS_OOM;
    }
    memcpy(entry->hash, hash, FLEX_TRIT_SIZE_243);
    HASH_ADD(hh, *set, hash, FLEX_TRIT_SIZE_243, entry);
  }
  return RC_OK;
}

retcode_t hash243_set_remove(hash243_set_t *const set,
                                flex_trit_t const *const hash) {
  hash243_set_entry_t *entry = NULL;

  if (set != NULL && * set != NULL && hash != NULL) {
    HASH_FIND(hh, *set, hash, FLEX_TRIT_SIZE_243, entry);
    return hash243_set_remove_entry(set, entry);
  }
  return RC_OK;
}

retcode_t hash243_set_remove_entry(hash243_set_t *const set,
                                      hash243_set_entry_t * const entry) {
  if (set != NULL && * set != NULL && entry != NULL) {
    HASH_DEL(*set, entry);
    free(entry);
  }
  return RC_OK;
}

retcode_t hash243_set_append(hash243_set_t const *const set1,
                               hash243_set_t *const set2) {
  retcode_t ret = RC_OK;
  hash243_set_entry_t *iter = NULL, *tmp = NULL;

  HASH_ITER(hh, *set1, iter, tmp) {
    if ((ret = hash243_set_add(set2, iter->hash)) != RC_OK) {
      return ret;
    }
  }
  return ret;
}

bool hash243_set_contains(hash243_set_t const *const set,
                            flex_trit_t const *const hash) {
  hash243_set_entry_t *entry = NULL;

  if (*set == NULL) {
    return false;
  }

  HASH_FIND(hh, *set, hash, FLEX_TRIT_SIZE_243, entry);
  return entry != NULL;
}

bool hash243_set_find(hash243_set_t const *const set,
        flex_trit_t const *const hash, hash243_set_entry_t const ** entry){
if (*set == NULL) {
return false;
}

if (entry == NULL){
  return RC_NULL_PARAM;
}

HASH_FIND(hh, *set, hash, FLEX_TRIT_SIZE_243, *entry);
return *entry != NULL;

}

void hash243_set_free(hash243_set_t *const set) {
  hash243_set_entry_t *iter = NULL, *tmp = NULL;

  HASH_ITER(hh, *set, iter, tmp) {
    HASH_DEL(*set, iter);
    free(iter);
  }
  *set = NULL;
}

retcode_t hash243_set_for_each(hash243_set_t const *const set,
                                 hash243_on_container_func func,
                                 void *const container) {
  retcode_t ret = RC_OK;
  hash243_set_entry_t *curr_entry = NULL;
  hash243_set_entry_t *tmp_entry = NULL;

  HASH_ITER(hh, *set, curr_entry, tmp_entry) {
    if ((ret = func(container, curr_entry->hash)) != RC_OK) {
      return ret;
    }
  }
  return ret;
}

retcode_t hash243_set_random_hash(hash243_set_t const *const set,
                                     flex_trit_t *const hash) {
  hash243_set_entry_t* iter = NULL;
  hash243_set_entry_t* tmp = NULL;

  if (set == NULL || hash == NULL) {
   return RC_NULL_PARAM;
  }

  int index = rand_handle_rand_interval(0, hash243_set_size(set));
  HASH_ITER(hh, *set, iter, tmp) {
    if (index-- == 0) {
      memcpy(hash, iter->hash, FLEX_TRIT_SIZE_243);
      break;
    }
  }

  return RC_OK;
}
