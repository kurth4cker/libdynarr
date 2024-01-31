/* Copyright (c) 2024 Kurth4cker <kurth4cker@gmail.com>
 * Licensed under the terms of GPL-3.0-or-later. See file COPYING for details.
 */

#include <stdlib.h>
#include <string.h>

#include "vector.h"

#define NTH(idx) ((char *)vec->data + vec->size * (idx))

static void extend(struct vector *);

static const size_t capacity = 1 << 5;

static void
extend(struct vector *vec)
{
	vec->capacity <<= 1;
	vec->data = realloc(vec->data, vec->size * vec->capacity);
}

int
vector_init(struct vector *vec, size_t size)
{
	vec->data = calloc(capacity, size);
	if (!vec->data)
		return -1;

	vec->size = size;
	vec->capacity = capacity;
	vec->len = 0;

	return 0;
}

struct vector *
vector_new(size_t size)
{
	struct vector *vec = malloc(sizeof(struct vector));
	if (!vec)
		return NULL;

	if (vector_init(vec, size) == -1) {
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

	memcpy(NTH(vec->len), item, vec->size);
	vec->len++;
}

/* NEEDS FIX */
void
vector_rem(struct vector *vec, const void *item)
{
	for (size_t i = 0; i < vec->len; i++) {
		if (memcmp(item, vector_get(vec, i), vec->size) != 0)
			continue;
		memmove(NTH(i), NTH(i + 1), (vec->len - i - 1) * vec->size);
		vec->len--;
	}
}

void *
vector_get(const struct vector *vec, size_t idx)
{
	if (idx >= vec->len)
		return NULL;

	return NTH(idx);
}
