#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"
#include "paint.h"

int main(){

    tree_t tree = {};
    initTree( &tree );

    node_t* node_1 = {};
    char* line_1 = strdup( "Animals" );
    initNode( &node_1, line_1 );

    node_t* node_2 = {};
    char* line_2 = strdup( "Poltarashka" );
    initNode( &node_2, line_2 );

    node_t* node_3 = {};
    char* line_3 = strdup( "Matan teaches" );
    initNode( &node_3, line_3 );

    node_t* node_4 = {};
    char* line_4 = strdup( "Baraban" );
    initNode( &node_4, line_4 );

    node_t* node_5 = {};
    char* line_5 = strdup( "Nikita" );
    initNode( &node_5, line_5 );

    ( tree.rootTree )->right = node_1;
    node_1->left = node_2;
    node_1->right = node_3;
    node_3->left = node_4;
    node_3->right = node_5;

    expertSystemErrors statusOfExpertSystem = startExpertSystem( &tree );
    if( statusOfExpertSystem != CORRECT_WORK ){
        colorPrintf( NOMODE, RED, "\n\nError of system\n\n" );
        return 0;
    }

    dumpTree( &tree );

    destroyTree( &tree );

    return 0;
}
