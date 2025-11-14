#ifndef H_EXPERT_SYSTEM
#define H_EXPERT_SYSTEM

#include "tree.h"

enum expertSystemErrors {
    CORRECT_WORK            = 0,
    CAN_NOT_DO_ALLOCATION   = 1,
    ERROR_WITH_GETLINE      = 2,
    NOT_CORRECT_WORK        = 3,
    ERROR_OF_CLEAN          = 4,
    TREE_NULL_PTR           = 5,
    TREE_ERRORS             = 6,
    NULL_PTR_IN_FUNC        = 7,
    ERROR_WITH_FILE         = 8,
    ROOT_NULL_PTR           = 9
};

enum informationAboutFind {
    FIND_PRINT_NO         = 0,
    FIND_PRINT_YES        = 1,
    NOT_FIND              = 3,
    DETECTED              = 4,
    FINISH_FIND           = 5,
    ERROR_OF_FIND         = 6,
    FIND_FIRST_OBJECT     = 7,
    FIND_SECOND_OBJECT    = 8
};

enum typeOfOperation{
    REED_DATA_BASE      = 'r',
    GUESSES             = 'g',
    WRITE_IN_FILE       = 'w',
    GIVE_DEFINITION     = 'd',
    GIVE_DIFFERENCES    = 'f',
    STOP                = 's'
};

#define voiceTheLine( lineThatNeedVoiced ) system( "echo " lineThatNeedVoiced " | festival --tts")

expertSystemErrors startExpertSystem( tree_t* tree );

expertSystemErrors guessElement( tree_t* tree );

expertSystemErrors goToSheetOfTree( node_t** nodePtr, node_t** previousNodePtr, char** answer, size_t* sizeOfLine );

expertSystemErrors insertNewElement( node_t** previousNodePtr, char** answer, size_t* sizeOfLine );

expertSystemErrors takeAnAnswer( char** answer, size_t* sizeOfLine );

expertSystemErrors takeNameOfObject( char** answer, size_t* sizeOfLine );

expertSystemErrors giveDefinition( tree_t* tree );

informationAboutFind printDefinition( node_t* node, char* answer );

expertSystemErrors giveDifferences( tree_t* tree );

informationAboutFind printDifferences( node_t* node, char* firstObject, char* secondObject );

void checkingTheStatusOfTheExpertSystem( expertSystemErrors statusOfExpertSystem );

#endif


