#include <sys/types.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "dynarr.h"

#define CAPACITY_OK(arr, idx) ((idx) < (arr)->capacity)
#define LENGTH_OK(arr, idx) ((idx) < (arr)->len)

static dynarr initial_array = {
	.data = NULL,
	.size = 0,
	.len = 0,
	.capacity = 64,
};

static int expand(dynarr *);
static void move(dynarr *, size_t, ssize_t);

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

static void
move(dynarr *arr, size_t idx, ssize_t direction)
{
	const void *src = dynarr_get(arr, idx);
	void *dest = dynarr_get(arr, idx + direction);
	size_t size = (arr->len - idx) * arr->size;

	assert(CAPACITY_OK(arr, idx + direction));
	assert(CAPACITY_OK(arr, idx));
	assert(LENGTH_OK(arr, idx));

	memmove(dest, src, size);
	arr->len += direction;
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

int
dynarr_insert(dynarr *arr, size_t idx, const void *obj)
{
	static const ssize_t direction = 1;

	if (!LENGTH_OK(arr, idx))
		return dynarr_push(arr, obj);

	if (!CAPACITY_OK(arr, arr->len + direction) && !expand(arr))
		return 0;

	move(arr, idx, direction);
	dynarr_set(arr, idx, obj);
	return 1;
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
	dynarr_reset(arr, arr->len);
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
dynarr_remove(dynarr *arr, size_t idx)
{
	static const ssize_t direction = -1;

	assert(LENGTH_OK(arr, idx));
	assert(CAPACITY_OK(arr, idx));

	move(arr, idx + 1, direction);
	dynarr_reset(arr, arr->len);
}

void
dynarr_reset(dynarr *arr, size_t idx)
{
	void *dest = dynarr_get(arr, idx);
	memset(dest, 0, arr->size);
}

void
dynarr_set(dynarr *arr, size_t idx, const void *obj)
{
	void *dest = dynarr_get(arr, idx);
	memcpy(dest, obj, arr->size);
}
