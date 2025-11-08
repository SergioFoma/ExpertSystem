#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "expertSystem.h"
#include "myStringFunction.h"
#include "paint.h"

expertSystemErrors guessElement( tree_t* tree ){
    assert( tree );

    colorPrintf( NOMODE, YELLOW, "Expert system loading...\nI'm a expert system - choose an object and i'm guess it\n\n" );

    node_t** nodePtr = &( (tree->rootTree)->left );

    char* answer = (char*)calloc( maxLenForAnswer, sizeof( char ) );
    if( answer == NULL ){
        return CAN_NOT_DO_ALLOCATION;
    }

    expertSystemErrors systemErr = CORRECT_WORK;

    do{
        cleanLine( answer );

        colorPrintf( NOMODE, BLUE, treeValueFormat "?\n", (*nodePtr)->data );
        systemErr = takeAnAnswer( answer );
        colorPrintf( NOMODE, PURPLE, " answer = %s, LINE = %d\n", answer, __LINE__ );
        while( systemErr != CORRECT_WORK ){
            cleanLine( answer );
            colorPrintf( NOMODE, PURPLE, "answer after clean = %s, LINE = %d\n", answer, __LINE__ );
            systemErr = takeAnAnswer( answer );
            colorPrintf( NOMODE, PURPLE, " answer = %s, LINE = %d\n", answer, __LINE__ );
        }

        if( strcmp( answer, "YES") == 0 ){
            nodePtr = &( (*nodePtr)->left );
        }
        else{
            nodePtr = &( (*nodePtr)->right );
        }


    }while( *(nodePtr) != NULL );

    if( strcmp( answer, "YES" ) == 0 ){
        colorPrintf( NOMODE, GREEN, "\n\nThe expert system guessed the hidden object!\n\n" );
        nodePtr = &(tree->rootTree );
        free( answer );
        return CORRECT_WORK;

    }
    else{
        colorPrintf( NOMODE, RED, "\n\nSystem does not  guess object...\n\n" );
        free( answer );
        return CORRECT_WORK;
    }

    free( answer );
    return CORRECT_WORK;
}

expertSystemErrors takeAnAnswer( char* answer ){
    assert( answer );

    char* lineForRecording = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = myGetline( &lineForRecording, &sizeOfAllocationMemory, stdin );
    colorPrintf( NOMODE, PURPLE, "line for recording = %s, LINE = %d\n", lineForRecording, __LINE__ );

    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    size_t lineIndex = 0;
    int statusOfClean = 0;

    while( lineForRecording[ lineIndex ] != '\0' && lineForRecording[ lineIndex ] != ' '  && lineIndex < maxLenForAnswer ){
        answer[ lineIndex ] = lineForRecording[ lineIndex ];
        ++lineIndex;
    }

    answer[ lineIndex ] = '\0';

    if( strlen( answer ) != strlen( lineForRecording ) ){
        colorPrintf( NOMODE, RED, "\n\nYour answer in too long\n\n" );
        statusOfClean = cleanLine( answer );
        if( statusOfClean != 0 ){
            free( lineForRecording );
            return ERROR_OF_CLEAN;
        }
        free( lineForRecording );
        return NOT_CORRECT_WORK;
    }
    else if( strcmp( answer, "NO" ) != 0 && strcmp( answer, "YES" ) != 0 ){
        colorPrintf( NOMODE, RED, "\n\nYour answer should be \"YES\" or \"NO\"\n\n" );
        statusOfClean = cleanLine( answer );
        if( statusOfClean != 0 ){
            free( lineForRecording );
            return ERROR_OF_CLEAN;
        }
        free( lineForRecording );
        return NOT_CORRECT_WORK;
    }

    free( lineForRecording );
    return CORRECT_WORK;

}
