/*
 * CIS 343 project 1 - implementation of file_utils.h
 * Gaelen McIntee
 * 2/2/17
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "file_utils.h"

int read_file( char* filename, char **buffer )
{
	FILE *f;
	struct stat info;

	f = fopen(filename, "r");
	if (f == NULL) {
		perror("read_file error opening file");
		return -1;
	}

	stat(filename, &info);  // store statistics on the file we're opening in the info struct
	char append[info.st_size]; // place to store fgets output

	*buffer = malloc(info.st_size * sizeof(char));
	if (*buffer == NULL) {
		perror("read_file error with malloc()");
		return -1;
	}

	while ( fgets(append, info.st_size, f) ) // loop while we can read something from fgets.
	{
		strcat(*buffer, append);
	}

	return 0;
}

int write_file( char* filename, char *buffer, int size )
{
	FILE *f = fopen(filename, "w");
	if (f == NULL) {
		perror("write_file error opening file");
		return -1;
	}

	// fprintf(f, "%s", buffer);
	fputs(buffer, f);

	return 0;
}

//pay no attention to this main() used for debugging
// int main (void)
// {
// 	char *buf;
//
// 	int i = read_file("lol", &buf);
// 	if (i < 0) return;
// 	fprintf(stderr, "%s\nReturn code: %i", buf, i);
//
// 	int x = write_file("out", buf, strlen(buf));
// 	if (x < 0) return;
// 	fprintf(stderr, "Return code: %i", x);
// }
