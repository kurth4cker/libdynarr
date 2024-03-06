#include <stdlib.h>

#include "dynarr.h"

void
dynarr_free(struct dynarr *arr)
{
	free(arr->data);
	free(arr);
}

/* TODO: implement */
struct dynarr *
dynarr_new(size_t size)
{
	(void)size;
	return NULL;
}
