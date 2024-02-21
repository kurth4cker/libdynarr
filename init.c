#include <stdlib.h>

#include "dynarr.h"

int
dynarr_init(struct dynarr *vec, size_t size)
{
	static const size_t capacity = 64;

	vec->data = calloc(64, size);
	if (!vec->data)
		return -1;

	vec->size = size;
	vec->len = 0;
	vec->capacity = capacity;

	return 0;
}
