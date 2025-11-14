#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"
#include "paint.h"

int main(){

    tree_t tree = {};
    
    expertSystemErrors statusOfExpertSystem = startExpertSystem( &tree );
    if( statusOfExpertSystem != CORRECT_WORK ){
        colorPrintf( NOMODE, RED, "\n\nError of system\n\n" );
        destroyTree( &tree );
        return 0;
    }

    dumpTree( &tree );

    destroyTree( &tree );

    return 0;
}
