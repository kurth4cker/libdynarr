#pragma once

#include <stddef.h>

struct dynarr {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

struct dynarr *dynarr_new(size_t);
void dynarr_free(struct dynarr *);

void *dynarr_get(const struct dynarr *, size_t);
void dynarr_set(struct dynarr *, size_t, const void *);

int dynarr_push(struct dynarr *, const void *);
int dynarr_pop(struct dynarr *);

int dynarr_insert(struct dynarr *, size_t, const void *);
void dynarr_remove(struct dynarr *, size_t);

int dynarr_capacity_ok(const struct dynarr *, size_t);
int dynarr_length_ok(const struct dynarr *, size_t);
