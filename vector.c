/* Copyright (c) 2024 Kurth4cker <kurth4cker@gmail.com>
 * Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
 */

#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define IDX2PTR(vec,idx) ((char *)((vec)->data) + (vec)->size * (idx))

static void
extend(struct vector *vec)
{
	vec->capacity *= 1.8 + 1;
	vec->data = realloc(vec->data, vec->size * vec->capacity);
}

struct vector *
vector_new(size_t sz)
{
	struct vector *vec = malloc(sizeof(struct vector));
	if (!vec)
		return NULL;

	vec->size = sz;
	vec->len = 0;
	vec->capacity = 1024;

	vec->data = calloc(vec->capacity, vec->size);
	if (!vec->data) {
		free(vec);
		return NULL;
	}

	return vec;
}

void
vector_free(struct vector *vec)
{
	free(vec->data);
	free(vec);
}

void
vector_add(struct vector *vec, const void *item)
{
	if (vec->len > vec->capacity)
		extend(vec);

	memcpy(IDX2PTR(vec, vec->len), item, vec->size);
	vec->len++;
}

void *
vector_get(struct vector *vec, size_t idx)
{
	if (idx >= vec->len)
		return NULL;

	return IDX2PTR(vec, idx);
}
