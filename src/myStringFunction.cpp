#include "myStringFunction.h"

#include <malloc.h>
#include <assert.h>
#include <ctype.h>

ssize_t myGetline( char** line, size_t* n, FILE* stream ) {

    const size_t startSize = 32;

    if( line == NULL ) {
        return -1;
    }

    if ( *line == NULL ) {
        char* tryLine =( char* )calloc( startSize, sizeof( char ) );

        if ( tryLine == NULL ) {
            return -1;
        }
        *n = startSize;
        *line = tryLine;
    }

    int getChar = 0;
    ssize_t indexCopyLine = 0;

    while( ( getChar = fgetc( stream) ) != '\n' && getChar != EOF ) {

        if ( indexCopyLine == ( *n - 1 ) ) {
            char* tryLine = ( char* )realloc( *line, 2 * (*n) );

            if ( tryLine == NULL ) {
                return -1;
            }
            *line = tryLine;

            ( *n ) *= 2;
        }

        (*line)[ indexCopyLine++  ] = getChar;
    }

    (*line)[ indexCopyLine ] = '\0';

    return indexCopyLine;

}

int cleanLine( char* lineForClean ){
    if( lineForClean == NULL ){
        return -1;
    }

    size_t cleanLineIndex = 0;

    while( lineForClean[ cleanLineIndex ] != '\0' ){
        lineForClean[ cleanLineIndex ] = '\0';
        ++cleanLineIndex;
    }

    lineForClean[ cleanLineIndex ] = '\0';

    return 0;
}

void cleanBuffer(){
    int symbol = '\0';
    while( ( symbol = getchar() ) != '\n' );
}
