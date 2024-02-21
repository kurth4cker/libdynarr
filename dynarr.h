#ifndef VECTOR_H
#define VECTOR_H
#include <stddef.h>

struct vector {
	void *data;
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
};

int vector_init(struct vector *, size_t);

#endif /* VECTOR_H */
