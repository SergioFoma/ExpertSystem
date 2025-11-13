#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#include "parseFileDataBase.h"
#include "treeDump.h"
#include "myStringFunction.h"
#include "paint.h"

expertSystemErrors writeInformationInFile( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "\nEnter the name of file were do you want save data base: " );

    char* fileNameForWrite = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = myGetline( &fileNameForWrite, &sizeOfAllocationMemory, stdin );
    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    FILE* fileForTree = fopen( fileNameForWrite, "w" );
    if( fileForTree == NULL ){
        colorPrintf( NOMODE, RED, "\nError with write data base in file\n" );
        return ERROR_WITH_FILE;
    }

    dumpTreeInFile( tree, fileForTree );

    free( fileNameForWrite );

    fclose( fileForTree );
    return CORRECT_WORK;
}

errorCode initBufferInformation( bufferInformation *bufferFromFile, FILE* myFile, const char* nameOfFile ){
    assert( bufferFromFile );
    assert( nameOfFile );

    if( myFile == NULL ){
        return fileOpenErr;
    }

    getFileSize( bufferFromFile, nameOfFile );
    bufferFromFile->buffer = (char*)calloc( bufferFromFile->fileSize + 1, sizeof( char ) );
    if( bufferFromFile->buffer == NULL ){
        return memoryErr;
    }
    bufferFromFile->bufferSize = fread( bufferFromFile->buffer, sizeof( char ), bufferFromFile->fileSize, myFile );
    if( bufferFromFile->bufferSize == 0 ){
        return fileOpenErr;
    }

    (bufferFromFile->buffer)[ bufferFromFile->fileSize ]= '\0';
    (bufferFromFile->buffer)[ bufferFromFile->bufferSize ] = '\0';

    return correct;
}

void getFileSize( bufferInformation* bufferFromFile, const char* nameOfFile ){
    assert( bufferFromFile != NULL );
    assert( nameOfFile != NULL );

    struct stat fileText;
    int status = stat( nameOfFile, &fileText );

    colorPrintf(NOMODE, YELLOW, "Size of file: %d\n", fileText.st_size );
    bufferFromFile->fileSize = fileText.st_size;
}

expertSystemErrors createTreeFromFile( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "Enter the name of file, where i will find information for my data base: " );
    char* nameOfFileForDataBase = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = myGetline( &nameOfFileForDataBase, &sizeOfAllocationMemory, stdin );
    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    FILE* fileForDataBase = fopen( nameOfFileForDataBase, "r" );
    if( fileForDataBase == NULL ){
        colorPrintf( NOMODE, RED, "\n can not open file:%s %s %d\n", __FILE__, __func__, __LINE__ );
        free( nameOfFileForDataBase );
        return ERROR_WITH_FILE;
    }

    bufferInformation dataBaseFromFile = {};
    errorCode statusOfReadFromFile = initBufferInformation( &dataBaseFromFile, fileForDataBase, nameOfFileForDataBase);
    if( statusOfReadFromFile != correct ){
        return ERROR_WITH_FILE;
    }

    char* ptrOnBuffer = dataBaseFromFile.buffer;
    tree->rootTree = createNodeFromFile( &ptrOnBuffer );

    free( nameOfFileForDataBase );
    colorPrintf( NOMODE, RED, " line after delete = %d\nPtr on buffer", __LINE__);
    destroyBufferInformation( &dataBaseFromFile );
    fclose( fileForDataBase );
    return CORRECT_WORK;
}


node_t* createNodeFromFile( char** ptrOnSymbolInPosition ){
    if( ptrOnSymbolInPosition == NULL || *( ptrOnSymbolInPosition) == NULL ){
        return NULL;
    }

    printf( "in function\n" );
    if( *(*ptrOnSymbolInPosition) == '(' ){
        ++(*ptrOnSymbolInPosition);
        char* nodeName = readNodeNameFromFile( ptrOnSymbolInPosition );
        node_t* newNode = NULL;
        initNode( &newNode, nodeName );
        newNode->left = createNodeFromFile( ptrOnSymbolInPosition );
        newNode->right = createNodeFromFile( ptrOnSymbolInPosition );
        ++(*ptrOnSymbolInPosition);
        printf( " pos = '%c', line = %d\n", **ptrOnSymbolInPosition, __LINE__ );
        return newNode;
    }
    else if( **ptrOnSymbolInPosition == 'n' ){
        *ptrOnSymbolInPosition += strlen( "nil" );
        printf( " pos = '%c', line = %d\n", **ptrOnSymbolInPosition, __LINE__ );
        return NULL;
    }

    return NULL;
}

char* readNodeNameFromFile( char** ptrOnSymbolInPosition ){
    if( ptrOnSymbolInPosition == NULL || *(ptrOnSymbolInPosition) == NULL ){
        return NULL;
    }

    char* startOfLineWithNodeName = strchr( *ptrOnSymbolInPosition, '\"' ) + 1;
    char* endOfLineWithNodeName = strchr( startOfLineWithNodeName, '\"' );

    char* nodeName = (char*)calloc( (size_t)(endOfLineWithNodeName - startOfLineWithNodeName) + 1, sizeof( char ) );
    if( nodeName == NULL ){
        return NULL;
    }
    printf( "startOfLineWithName = %c\nendOfLineWithNodeName = %c\nlen name = %lu\n",
            *startOfLineWithNodeName, *endOfLineWithNodeName, (size_t)(endOfLineWithNodeName - startOfLineWithNodeName));
    sscanf( startOfLineWithNodeName, "%[^\"]", nodeName );
    printf( "name = '%s'\n", nodeName );
    *ptrOnSymbolInPosition = endOfLineWithNodeName + 1;

    return nodeName;
}

void destroyBufferInformation( bufferInformation *bufferFromFile ){
    if( bufferFromFile == NULL ){
        return ;
    }

    free( bufferFromFile->buffer );
    bufferFromFile->bufferSize = 0;
    bufferFromFile->fileSize = 0;
    bufferFromFile = NULL;
}
