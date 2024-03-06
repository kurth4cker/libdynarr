#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynarr.h"

#define CAPACITY_OK(arr, idx) (idx < arr->capacity)

static dynarr initial_array = {
	.data = NULL,
	.size = 0,
	.len = 0,
	.capacity = 64,
};

static int
expand(dynarr *arr)
{
	const size_t capacity = arr->capacity * 2;
	void *data = realloc(arr->data, capacity);

	if (!data)
		return 0;

	arr->data = data;
	arr->capacity = capacity;
	return 1;
}

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

int
dynarr_pop(dynarr *arr)
{
	if (arr->len == 0)
		return 0;

	arr->len--;
	void *dest = dynarr_get(arr, arr->len);
	assert(dest != NULL);
	memset(dest, 0, arr->size);
	return 1;
}

int
dynarr_push(dynarr *arr, const void *obj)
{
	const size_t idx = arr->len;

	if (!CAPACITY_OK(arr, idx) && !expand(arr))
		return 0;

	dynarr_set(arr, idx, obj);
	arr->len++;
	return 1;
}

void
dynarr_set(dynarr *arr, size_t idx, const void *obj)
{
	void *dest = dynarr_get(arr, idx);
	memcpy(dest, obj, arr->size);
}
