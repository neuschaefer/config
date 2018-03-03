/*
 * SPDX-License-Identifier: GPL-2.0
 * Copyright (C) 2018 Jonathan Neuschäfer
 *
 * This program sets the "No new privileges" flag in the current process, and
 * then executes a different program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/prctl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int res;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s PROGRAM [ARGS]\n", argv[0]);
		exit(1);
	}

	res = prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0);
	if (res < 0) {
		perror("prctl failed");
		exit(1);
	}

	execvp(argv[1], argv+1);
	perror("exec failed");
	exit(1);
}
