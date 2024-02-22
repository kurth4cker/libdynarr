#include <stdlib.h>

#include "dynarr.h"

void *
dynarr_get(const struct dynarr *vec, size_t idx)
{
	if (idx >= vec->len)
		return NULL;

	return (char *)vec->data + idx * vec->size;
}

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

/* TODO: implement */
int
dynarr_push(struct dynarr *vec, const void *obj)
{
	(void)vec;
	(void)obj;
	return 0;
}

/* TODO: implement */
int
dynarr_set(struct dynarr *vec, size_t idx, const void *obj)
{
	(void)vec;
	(void)idx;
	(void)obj;
	return -2;
}

void
dynarr_term(struct dynarr *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->capacity = 0;
	vec->size = 0;
	vec->len = 0;
}
