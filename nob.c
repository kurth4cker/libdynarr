// SPDX-License-Identifier: GPL-3.0-or-later
// SPDX-FileCopyrightText: 2025 kurth4cker <kurth4cker@gmail.com>

#include <stdlib.h>

#define NOB_EXPERIMENTAL_DELETE_OLD
#define NOB_IMPLEMENTATION
#include "nob.h"

static void
cc(Nob_Cmd *cmd)
{
	char *cc = getenv("CC");
	if (cc != NULL) {
		nob_cmd_append(cmd, cc);
	} else {
#if defined(__clang__)
		nob_cmd_append(cmd, "clang");
#elif defined(__GNUC__)
		nob_cmd_append(cmd, "gcc");
#else
		nob_cmd_append(cmd, "cc");
#endif
	}
}

static void
cc_and_cflags(Nob_Cmd *cmd)
{
	cc(cmd);
	nob_cmd_append(cmd, "-pedantic");
	nob_cmd_append(cmd, "-Wall", "-Wextra", "-Werror");
	nob_cmd_append(cmd, "-g");
}

int
main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	Nob_Cmd cmd = { 0 };

	cc_and_cflags(&cmd);
	nob_cc_inputs(&cmd, "-c", "dynarr.c");
	nob_cc_output(&cmd, "dynarr.o");
	if (!nob_cmd_run_sync_and_reset(&cmd)) {
		exit(EXIT_FAILURE);
	}

	nob_cmd_append(&cmd, "ar", "-rc");
	nob_cmd_append(&cmd, "libdynarr.a", "dynarr.o");
	if (!nob_cmd_run_sync_and_reset(&cmd)) {
		exit(EXIT_FAILURE);
	}

	nob_cmd_append(&cmd, "ranlib", "libdynarr.a");
	nob_cmd_run_sync_and_reset(&cmd);

	cc_and_cflags(&cmd);
	nob_cc_inputs(&cmd, "example.c", "libdynarr.a");
	nob_cc_output(&cmd, "example");
	if (!nob_cmd_run_sync_and_reset(&cmd)) {
		exit(EXIT_FAILURE);
	}
}
