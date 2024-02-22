#pragma once

#include <stddef.h>

struct dynarr {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

int dynarr_init(struct dynarr *, size_t);
void dynarr_term(struct dynarr *);

/* TODO: implement */
int dynarr_push(struct dynarr *, const void *);
