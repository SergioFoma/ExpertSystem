#ifndef H_TREEDUMP
#define H_TREEDUMP

#include "tree.h"

void dumpNode( node_t* node, int rank, FILE* treeFile );

treeErrors dumpTree( tree_t* node );

void dumpNodeInFile( const node_t* node, FILE* fileForWrite );

void dumpTreeInFile( const tree_t* tree, FILE* fileForWrite );

#endif
