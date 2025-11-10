#ifndef H_TREE
#define H_TREE

#include <limits.h>

typedef char* treeElem_t;
#define treeValueFormat "%s"
#define maxTreeValue strdup("It is unknown who")

const size_t oneStruct = 1;

enum treeErrors {
    CORRECT_TREE        = 0,
    NODE_NULL_PTR       = 1,
    NOT_ENOUGH_MEMORY   = 2,
    ERROR_OF_OPEN_FILE  = 3
};

struct node_t {
    treeElem_t data;
    node_t* left;
    node_t* right;
};

struct tree_t{
    node_t* rootTree;
};

void printNode( const node_t* tree );

void printTree( const tree_t* tree );

void printTheSortedNode( const node_t* tree );

void printTheSortedTree( const tree_t* tree );

treeErrors initTree( tree_t* tree );

treeErrors initNode( node_t** node, treeElem_t element );

treeErrors insertNode( tree_t* root, treeElem_t element );

void destroyNode( node_t* node );

void destroyTree( tree_t* node );

#endif
