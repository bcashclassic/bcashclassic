/*
 * Copyright (c) 2018 IOTA Stiftung
 * https://github.com/iotaledger/entangled
 *
 * Refer to the LICENSE file for licensing information
 */

#include <stdlib.h>

#include "utils/containers/hash/hash243_stack.h"

bool hash243_stack_empty(hash243_stack_t const stack) { return (stack == NULL); }

retcode_t hash243_stack_push(hash243_stack_t *const stack,
                          flex_trit_t const *const hash) {
  hash243_stack_entry_t *entry = NULL;

  if ((entry = (hash243_stack_entry_t *)malloc(sizeof(hash243_stack_entry_t))) == NULL) {
    return RC_UTILS_OOM;
  }
  memcpy(entry->hash, hash, FLEX_TRIT_SIZE_243);
  LL_PREPEND(*stack, entry);
  return RC_OK;
}

void hash243_stack_pop(hash243_stack_t *const stack) {
  hash243_stack_entry_t *tmp = NULL;

  tmp = *stack;
  LL_DELETE(*stack, *stack);
  free(tmp);
}

flex_trit_t *hash243_stack_peek(hash243_stack_t const stack) {
  return (flex_trit_t *)(stack->hash);
}

void hash243_stack_free(hash243_stack_t *const stack) {
  hash243_stack_entry_t *iter = NULL, *tmp = NULL;

  LL_FOREACH_SAFE(*stack, iter, tmp) {
    LL_DELETE(*stack, iter);
    free(iter);
  }
}

size_t hash243_stack_count(hash243_stack_t const stack) {
  hash243_stack_t curr = stack;
  size_t count = 0;
  while (curr != NULL) {
    ++count;
    curr = curr->next;
  }
  return count;
}

flex_trit_t *hash243_stack_at(hash243_stack_t const stack, size_t index) {
  hash243_stack_entry_t *iter = NULL;
  size_t count = 0;
  LL_FOREACH(stack, iter) {
    if (count == index) {
      return (flex_trit_t *)(iter->hash);
    }
    count++;
  }
  return NULL;
}
