#pragma once

#include <stddef.h>

struct dynarr {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

void *dynarr_get(const struct dynarr *, size_t);
int dynarr_init(struct dynarr *, size_t);
int dynarr_insert(struct dynarr *, size_t, const void *);
int dynarr_push(struct dynarr *, const void *);
void dynarr_term(struct dynarr *);
