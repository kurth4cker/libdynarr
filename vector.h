#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

struct vector {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

struct vector *vector_new(size_t);
void vector_free(struct vector *);

void vector_add(struct vector *, const void *);
void vector_rem(struct vector *, const void *);

void *vector_get(struct vector *, size_t);

#endif /* VECTOR_H */
