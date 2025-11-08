#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"

void printNode( const node_t* node ){
    assert( node );

    printf( "(\"" treeValueFormat "\" ", node->data );

    if( node->left ){
        printNode( node->left );
    }
    if( node->right ){
        printNode( node->right );
    }

    printf( ")" );
}

void printTree( const tree_t* tree ){
    assert( tree );

    printNode( tree->rootTree );
}

void printTheSortedNode( const node_t* node ){
    assert( node );

    if( node->left ){
        printTheSortedNode( node->left );
    }

    printf( treeValueFormat " ", node->data );

    if( node->right ){
        printTheSortedNode( node->right );
    }
}

void printTheSortedTree( const tree_t* tree ){
    assert( tree );

    printTheSortedNode( tree->rootTree );
}

treeErrors initNode( node_t** node, treeElem_t element ){
    assert( node );

    *node = ( node_t* )calloc( oneStruct, sizeof( node_t ) );
    if( *node == NULL ){
        return NOT_ENOUGH_MEMORY;
    }

    (*node)->data = element;

    (*node)->left = NULL;
    (*node)->right = NULL;

    return CORRECT_TREE;
}

treeErrors initTree( tree_t* tree ){
    assert( tree );

    treeErrors errorWithInitialization = initNode( &(tree->rootTree), maxTreeValue );

    if( errorWithInitialization != CORRECT_TREE ){
        return errorWithInitialization;
    }

    return CORRECT_TREE;
}

treeErrors insertNode( tree_t* tree, treeElem_t element ){
    if( tree == NULL ){
        return NODE_NULL_PTR;
    }

    node_t** nodePtr = &(tree->rootTree);
    while( *(nodePtr) ){
        if( element <= (*nodePtr)->data ){
            nodePtr = &( (*nodePtr)->left );
        }
        else{
            nodePtr = &( (*nodePtr)->right );
        }
    }

    initNode( nodePtr, element );

    return CORRECT_TREE;
}

void destroyNode( node_t* node ){
    if( node == NULL ){
        return ;
    }

    //printf( "\n\nnode = %p\nData = "  treeValueFormat "\nleft prt = %p\nright ptr = %p\n", node, node->data, node->left, node->right );

    node->data = {};

    if( node->left  ){
        destroyNode( node->left );
    }

    if( node->right ){
        destroyNode( node->right );
    }

    //printf( "\nnode %p befor delete\n", node );
    free( node );
}

void destroyTree( tree_t* tree ){
    if( tree == NULL ){
        return ;
    }

    destroyNode( tree->rootTree );

    *tree = {};
}
