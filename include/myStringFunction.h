#ifndef H_MYSTRINGFUNCTION
#define H_MYSTRINGFUNCTION

#include <stdio.h>
#include <unistd.h>

ssize_t myGetline( char** line, size_t* n, FILE* stream );

int cleanLine( char* lineForClean );

void cleanBuffer();

#endif
