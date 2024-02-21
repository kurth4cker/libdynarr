#include <stdlib.h>

#include "dynarr.h"

void
dynarr_term(struct dynarr *vec)
{
	free(vec->data);
	vec->data = NULL;
	vec->capacity = 0;
	vec->size = 0;
	vec->len = 0;
}
