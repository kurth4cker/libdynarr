#include <stdlib.h>
#include <string.h>

#include "dynarr.h"

static size_t initial_capacity = 64;

static int
expand(struct dynarr *vec)
{
	const size_t capacity = vec->capacity + vec->capacity / 2 + 1;
	void *data = realloc(vec->data, capacity);

	if (!data)
		return -1;

	vec->data = data;
	vec->capacity = capacity;
	return 0;
}

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

int
dynarr_insert(struct dynarr *vec, size_t idx, const void *obj)
{
	char *ptr = vec->data;

	if (vec->len >= vec->capacity && expand(vec) == -1)
		return -1;

	ptr += vec->size * idx;
	memmove(ptr + vec->size, ptr, vec->len - idx);
	memcpy(ptr, obj, vec->size);
	vec->len++;

	return 0;
}

/* TODO: implement */
int
dynarr_push(struct dynarr *vec, const void *obj)
{
	(void)vec;
	(void)obj;
	return -1;
}

void
dynarr_term(struct dynarr *vec)
{
	free(vec->data);
	vec->data = NULL;
}
