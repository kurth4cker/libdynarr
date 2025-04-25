// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2024 kurth4cker <kurth4cker@gmail.com>

#include <sys/types.h>

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "dynarr.h"

#define CAPACITY_OK(arr, idx) ((idx) < (arr)->capacity)
#define LENGTH_OK(arr, idx) ((idx) < (arr)->len)

static const Dynarr initial_array = {
	.data = NULL,
	.size = 0,
	.len = 0,
	.capacity = 64,
};

static bool expand(Dynarr *);
static void move(Dynarr *, size_t, ssize_t);
static void set(const Dynarr *arr, size_t idx, const void *obj);

static bool
expand(Dynarr *arr)
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
move(Dynarr *arr, size_t idx, ssize_t direction)
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

static void
set(const Dynarr *arr, size_t idx, const void *obj)
{
	assert(CAPACITY_OK(arr, idx));
	void *dest = dynarr_get(arr, idx);
	memcpy(dest, obj, arr->size);
}

bool
dynarr_capacity_ok(const Dynarr *arr, size_t idx)
{
	return CAPACITY_OK(arr, idx);
}

void
dynarr_free(Dynarr *arr)
{
	free(arr->data);
	free(arr);
}

void *
dynarr_get(const Dynarr *arr, size_t idx)
{
	assert(CAPACITY_OK(arr, idx));
	return (char *)arr->data + idx * arr->size;
}

bool
dynarr_insert(Dynarr *arr, size_t idx, const void *obj)
{
	static const ssize_t direction = 1;

	if (!LENGTH_OK(arr, idx))
		return dynarr_push(arr, obj);

	if (!CAPACITY_OK(arr, arr->len + direction) && !expand(arr))
		return false;

	move(arr, idx, direction);
	set(arr, idx, obj);
	return true;
}

bool
dynarr_length_ok(const Dynarr *arr, size_t idx)
{
	return LENGTH_OK(arr, idx);
}

Dynarr *
dynarr_new(size_t size)
{
	Dynarr *arr = malloc(sizeof(Dynarr));
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

bool
dynarr_pop(Dynarr *arr)
{
	if (arr->len == 0)
		return false;

	arr->len--;

	void *obj = dynarr_get(arr, arr->len);
	memset(obj, 0, arr->size);

	return true;
}

bool
dynarr_push(Dynarr *arr, const void *obj)
{
	const size_t idx = arr->len;

	if (!CAPACITY_OK(arr, idx) && !expand(arr))
		return false;

	set(arr, idx, obj);
	arr->len++;
	return true;
}

void
dynarr_remove(Dynarr *arr, size_t idx)
{
	static const ssize_t direction = -1;

	assert(LENGTH_OK(arr, idx));
	assert(CAPACITY_OK(arr, idx));

	move(arr, idx + 1, direction);

	void *obj = dynarr_get(arr, arr->len);
	memset(obj, 0, arr->size);
}
