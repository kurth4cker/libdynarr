// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "dynarr.h"

typedef enum {
	UNKNOWN = 0,
	C,
	CXX,
	PYTHON,
	GO,
} Language;

typedef struct {
	const char *name;
	Language language;
} Project;

static const char *LANGUAGE_STRINGS[] = {
	[UNKNOWN] = "unknown",
	[C] = "C",
	[CXX] = "C++",
	[PYTHON] = "Python",
	[GO] = "Go",
};

static void
fill_projects(Dynarr *arr)
{
	const Project projects[] = {
		{"wang-tiles", C},
		{"generate-names", C},
		{"go-sample", GO},
	};

	for (size_t i = 0; i < sizeof(projects)/sizeof(*projects); i++) {
		const bool ok = dynarr_push(arr, &projects[i]);
		assert(ok);
	}
}

static void
print_projects(const Dynarr *arr)
{
	for (size_t i = 0; i < arr->len; i++) {
		assert(dynarr_length_ok(arr, i));

		const Project *project = dynarr_get(arr, i);
		assert(project != NULL);
		assert(project->name != NULL);
		printf("name = %s, type = %s\n", project->name, LANGUAGE_STRINGS[project->language]);
	}
}

int
main(void)
{
	Dynarr *arr = dynarr_new(sizeof(Project));
	if (arr == NULL) {
		fprintf(stderr, "Dynarr alloc failed\n");
		exit(EXIT_FAILURE);
	}

	fill_projects(arr);
	print_projects(arr);
	dynarr_free(arr);
}
