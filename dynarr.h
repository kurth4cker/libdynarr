#pragma once

#include <stddef.h>

typedef struct {
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
	void *data;
} Dynarr;

Dynarr *dynarr_new(size_t);
void dynarr_free(Dynarr *);

void *dynarr_get(const Dynarr *, size_t);

bool dynarr_push(Dynarr *, const void *);
bool dynarr_pop(Dynarr *);

bool dynarr_insert(Dynarr *, size_t, const void *);
void dynarr_remove(Dynarr *, size_t);

bool dynarr_capacity_ok(const Dynarr *, size_t);
bool dynarr_length_ok(const Dynarr *, size_t);
