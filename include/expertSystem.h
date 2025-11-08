#ifndef H_EXPERTSYSTEM
#define H_EXPERTSYSTEM

#include "tree.h"

const size_t maxLenForAnswer = 10;

enum expertSystemErrors {
    CORRECT_WORK            = 0,
    CAN_NOT_DO_ALLOCATION   = 1,
    ERROR_WITH_GETLINE      = 2,
    NOT_CORRECT_WORK        = 3,
    ERROR_OF_CLEAN          = 4
};

expertSystemErrors guessElement( tree_t* tree );

expertSystemErrors takeAnAnswer( char* answer );

#endif


