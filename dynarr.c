#include <stdlib.h>

#include "dynarr.h"

static size_t initial_capacity = 64;

int
dynarr_init(struct dynarr *vec, size_t size)
{
	vec->data = calloc(initial_capacity, size);
	if (!vec->data)
		return -1;

	vec->size = size;
	vec->len = 0;
	vec->capacity = initial_capacity;

	return 0;
}

void
dynarr_term(struct dynarr *vec)
{
	free(vec->data);
	vec->data = NULL;
}
