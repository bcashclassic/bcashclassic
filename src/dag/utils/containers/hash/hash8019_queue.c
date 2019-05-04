/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdlib.h>

#include "utils/containers/hash/hash8019_queue.h"

bool hash8019_queue_empty(hash8019_queue_t const queue) { return (queue == NULL); }

retcode_t hash8019_queue_push(hash8019_queue_t *const queue,
                          flex_trit_t const *const hash) {
  hash8019_queue_entry_t *entry = NULL;

  if ((entry = (hash8019_queue_entry_t *)malloc(sizeof(hash8019_queue_entry_t))) == NULL) {
    return RC_UTILS_OOM;
  }
  memcpy(entry->hash, hash, FLEX_TRIT_SIZE_8019);
  CDL_APPEND(*queue, entry);
  return RC_OK;
}

void hash8019_queue_pop(hash8019_queue_t *const queue) {
  hash8019_queue_entry_t *tmp = NULL;

  tmp = *queue;
  if (tmp != NULL) {
    CDL_DELETE(*queue, *queue);
    free(tmp);
  }
}

flex_trit_t *hash8019_queue_peek(hash8019_queue_t const queue) {
  if (queue == NULL) {
    return NULL;
  }
  return (flex_trit_t *)(queue->hash);
}

void hash8019_queue_free(hash8019_queue_t *const queue) {
  hash8019_queue_entry_t *iter = NULL, *tmp1 = NULL, *tmp2 = NULL;

  CDL_FOREACH_SAFE(*queue, iter, tmp1, tmp2) {
    CDL_DELETE(*queue, iter);
    free(iter);
  }
}

size_t hash8019_queue_count(hash8019_queue_t const queue) {
  hash8019_queue_entry_t *iter = NULL;
  size_t count = 0;
  CDL_COUNT(queue, iter, count);
  return count;
}

flex_trit_t *hash8019_queue_at(hash8019_queue_t *const queue, size_t index) {
  hash8019_queue_entry_t *iter = NULL;
  size_t count = 0;
  CDL_FOREACH(*queue, iter) {
    if (count == index) {
      return (flex_trit_t *)(iter->hash);
    }
    count++;
  }
  return NULL;
}
