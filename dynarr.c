#include <stdlib.h>

#include "dynarr.h"

static struct dynarr initial_array = {
	.data = NULL,
	.size = 0,
	.len = 0,
	.capacity = 64,
};

void
dynarr_free(struct dynarr *arr)
{
	free(arr->data);
	free(arr);
}

struct dynarr *
dynarr_new(size_t size)
{
	struct dynarr *arr = malloc(sizeof(struct dynarr));
	if (!arr)
		return NULL;

	arr->data = calloc(initial_array.capacity, size);
	if (!arr->data) {
		free(arr);
		return NULL;
	}

	arr->capacity = initial_array.capacity;
	arr->len = initial_array.len;
	arr->size = size;

	return arr;
}
