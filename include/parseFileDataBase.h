#ifndef H_PARSEFILEDATABASE
#define H_PARSEFILEDATABASE

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "expertSystem.h"

struct bufferInformation{
    char* buffer;
    size_t fileSize;
    size_t bufferSize;
};

enum errorCode {
    correct        = 0,
    fileOpenErr    = 1,
    memoryErr      = 2
};

expertSystemErrors writeInformationInFile( tree_t* tree );

void getFileSize( bufferInformation* bufferFromFile, const char* nameOfFile );

errorCode initBufferInformation( bufferInformation *bufferFromFile, FILE* myFile, const char* nameOfFile );

void destroyBufferInformation( bufferInformation *bufferFromFile );

expertSystemErrors createTreeFromFile( tree_t* tree );

node_t* createNodeFromFile( char** ptrOnSymbolInPosition );

char* readNodeNameFromFile( char** ptrOnSymbolInPosition );

#endif

