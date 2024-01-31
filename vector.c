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
