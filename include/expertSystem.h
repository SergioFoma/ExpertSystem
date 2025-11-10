#ifndef H_EXPERTSYSTEM
#define H_EXPERTSYSTEM

#include "tree.h"

enum expertSystemErrors {
    CORRECT_WORK            = 0,
    CAN_NOT_DO_ALLOCATION   = 1,
    ERROR_WITH_GETLINE      = 2,
    NOT_CORRECT_WORK        = 3,
    ERROR_OF_CLEAN          = 4,
    TREE_NULL_PTR           = 5,
    TREE_ERRORS             = 6,
    NULL_PTR_IN_FUNC        = 7
};

enum informationAboutFind {
    FIND_PRINT_NO         = 0,
    FIND_PRINT_YES        = 1,
    NOT_FIND              = 3
};

expertSystemErrors startExpertSystem( tree_t* tree );

expertSystemErrors guessElement( tree_t* tree );

expertSystemErrors goToSheetOfTree( node_t** nodePtr, node_t** previousNodePtr, char** answer );

expertSystemErrors makeNewObject( node_t** previousNodePtr, char** answer );

expertSystemErrors changeElement( node_t* node );

expertSystemErrors takeAnAnswer( char** answer );

expertSystemErrors takeNameOfObject( char** answer );

expertSystemErrors writeInformationInFile( tree_t* tree );

expertSystemErrors giveDefinition( tree_t* tree );

informationAboutFind printDefinition( node_t* node, char* answer );

void cleanBuffer();

#endif


