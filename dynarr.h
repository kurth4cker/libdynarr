#pragma once

#include <stddef.h>

struct dynarr {
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
	void *data;
};

struct dynarr *dynarr_new(size_t);
void dynarr_free(struct dynarr *);

void *dynarr_get(const struct dynarr *, size_t);
void dynarr_set(struct dynarr *, size_t, const void *);

bool dynarr_push(struct dynarr *, const void *);
bool dynarr_pop(struct dynarr *);

bool dynarr_insert(struct dynarr *, size_t, const void *);
void dynarr_remove(struct dynarr *, size_t);

bool dynarr_capacity_ok(const struct dynarr *, size_t);
bool dynarr_length_ok(const struct dynarr *, size_t);
