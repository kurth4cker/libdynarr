#ifndef DYNARR_H_
#define DYNARR_H_

#include <stddef.h>
#include <stdbool.h>

// TODO(#5): Maybe a new type called Array

// TODO(#6): Add comment documentation of Dynarr
typedef struct {
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
	void *data;
} Dynarr;

Dynarr *dynarr_new(size_t itemsize);
void dynarr_free(Dynarr *arr);

void *dynarr_get(const Dynarr *arr, size_t idx);

bool dynarr_push(Dynarr *arr, const void *obj);
bool dynarr_pop(Dynarr *arr);

bool dynarr_insert(Dynarr *arr, size_t idx, const void *obj);
void dynarr_remove(Dynarr *arr, size_t idx);

bool dynarr_capacity_ok(const Dynarr *arr, size_t idx);
bool dynarr_length_ok(const Dynarr *arr, size_t idx);

#endif // DYNARR_H_
