#include <stdlib.h>
#include <string.h>

#include "dynarr.h"

static dynarr initial_array = {
	.data = NULL,
	.size = 0,
	.len = 0,
	.capacity = 64,
};

void
dynarr_free(dynarr *arr)
{
	free(arr->data);
	free(arr);
}

void *
dynarr_get(const dynarr *arr, size_t idx)
{
	return (char *)arr->data + idx * arr->size;
}

dynarr *
dynarr_new(size_t size)
{
	dynarr *arr = malloc(sizeof(dynarr));
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

void
dynarr_set(dynarr *arr, size_t idx, const void *obj)
{
	void *dest = dynarr_get(arr, idx);
	memcpy(dest, obj, arr->size);
}
