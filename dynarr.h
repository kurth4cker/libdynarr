#ifndef DYNARR_H_
#define DYNARR_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct {
	size_t size; /* sizeof each element */
	size_t len; /* number of elements */
	size_t capacity; /* element capacity */
	void *data;
} Dynarr;

// Allocates and initializes new Dynarr with given item size.
// Item size is typically sizeof(Typaname).
Dynarr *dynarr_new(size_t itemsize);

// Deallocate Dynarr
void dynarr_free(Dynarr *arr);

// Get given index.
// .
// RETURN:
//   On success return adress of item. If you change it it will affect array too.
//   On failure, return NULL.
void *dynarr_get(const Dynarr *arr, size_t idx);

// Push given object to the array. Copies contents of object.
// This function fail only if reallocation of array fails.
bool dynarr_push(Dynarr *arr, const void *obj);

// Remove last object from array. Fails if array is empty.
bool dynarr_pop(Dynarr *arr);

// Insert item into given index. Moves items to right if necessary.
// Like push, fails if allocation fails.
bool dynarr_insert(Dynarr *arr, size_t idx, const void *obj);

// Remove item from given index. If index is out of range, do nothing.
void dynarr_remove(Dynarr *arr, size_t idx);

// Check index is in capacity.
bool dynarr_capacity_ok(const Dynarr *arr, size_t idx);

// Check index is in length.
bool dynarr_length_ok(const Dynarr *arr, size_t idx);

#endif // DYNARR_H_
