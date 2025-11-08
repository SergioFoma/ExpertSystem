#ifndef H_TREEDUMP
#define H_TREEDUMP

#include "tree.h"

void dumpNode( node_t* node, int rank, FILE* treeFile );

treeErrors dumpTree( tree_t* node );

#endif
