#include <stdio.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"

int main(){

    /*tree_t tree = {};

    initTree( &tree );

    insertNode( &tree , 10 );
    insertNode( &tree , 20 );
    insertNode( &tree , 5 );
    insertNode( &tree , 3 );
    insertNode( &tree , 7 );
    insertNode( &tree , 15 );

    printTree( &tree );
    printf( "\n" );

    printf( "\nThe sorted tree:\n\n" );
    printTheSortedTree( &tree );
    printf( "\n" );*/

    tree_t tree = {};
    initTree( &tree );

    node_t* node_1 = {};
    initNode( &node_1, "Animals" );

    node_t* node_2 = {};
    initNode( &node_2, "Poltarashka" );

    node_t* node_3 = {};
    initNode( &node_3, "Matan teaches" );

    node_t* node_4 = {};
    initNode( &node_4, "Baraban" );

    node_t* node_5 = {};
    initNode( &node_5, "Nikita" );

    ( tree.rootTree )->left = node_1;
    node_1->left = node_2;
    node_1->right = node_3;
    node_3->left = node_4;
    node_3->right = node_5;

    dumpTree( &tree );

    guessElement( &tree );

    destroyTree( &tree );

    return 0;
}
