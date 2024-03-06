#pragma once

#include <stddef.h>

struct dynarr {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

typedef struct dynarr dynarr;

dynarr *dynarr_new(size_t);
void dynarr_free(dynarr *);

void *dynarr_get(const dynarr *, size_t);
void dynarr_set(dynarr *, size_t, const void *);

int dynarr_push(dynarr *, const void *);
int dynarr_pop(dynarr *);
