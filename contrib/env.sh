#!/bin/sh

if [ -d ../libdynarr-tests ]; then
	export TESTDIR=../libdynarr-tests
fi

export CFLAGS="-g -Wall -Werror -Wextra"
