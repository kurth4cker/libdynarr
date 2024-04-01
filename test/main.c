#include <dynarr.h>

#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

static MunitResult
test_new(const MunitParameter *params, void *fixture)
{
	(void)params;
	(void)fixture;
	struct dynarr *arr = dynarr_new(sizeof(int));
	assert_not_null(arr);
	assert_size(arr->size, ==, sizeof(int));
	assert_size(arr->len, ==, 0);
	assert_not_null(arr->data);
	assert_size(arr->capacity, >, 0);
	free(arr->data);
	free(arr);

	arr = dynarr_new(1);
	assert_not_null(arr);
	assert_size(arr->size, ==, 1);
	assert_size(arr->len, ==, 0);
	assert_size(arr->capacity, >, 0);
	assert_not_null(arr->data);
	free(arr->data);
	free(arr);

	arr = dynarr_new(sizeof(size_t));
	assert_not_null(arr);
	assert_size(arr->size, ==, sizeof(size_t));
	assert_size(arr->len, ==, 0);
	assert_size(arr->capacity, >, 0);
	assert_not_null(arr->data);
	free(arr->data);
	free(arr);

	return MUNIT_OK;
}

static MunitResult
test_push(const MunitParameter *params, void *fixture)
{
	(void)params;
	(void)fixture;
	struct dynarr *arr = dynarr_new(sizeof(int));
	if (!arr)
		return MUNIT_ERROR;

	int i = 42;
	dynarr_push(arr, &i);
	assert_size(arr->len, ==, 1);
	assert_int(*(int *)arr->data, ==, 42);

	i = 43;
	dynarr_push(arr, &i);
	assert_size(arr->len, ==, 2);
	assert_int(*(int *)arr->data, ==, 42);
	assert_int(*(int *)(arr->data + arr->size), ==, 43);

	i = 44;
	dynarr_push(arr, &i);
	assert_size(arr->len, ==, 3);
	assert_int(*(int *)arr->data, ==, 42);
	assert_int(*(int *)(arr->data + arr->size), ==, 43);
	assert_int(*(int *)(arr->data + 2 * arr->size), ==, 44);

	free(arr->data);
	free(arr);

	return MUNIT_OK;
}

static MunitTest tests[] = {
	{ "/new", test_new, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
	{ "/push", test_push, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL },
	{ NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL }
};

static const MunitSuite suite = {
	"/dynarr",
	tests,
	NULL,
	1,
	MUNIT_SUITE_OPTION_NONE
};

int
main(int argc, char **argv)
{
	return munit_suite_main(&suite, NULL, argc, argv);
}
