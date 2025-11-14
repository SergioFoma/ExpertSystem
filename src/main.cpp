#include <stdio.h>
#include <string.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"
#include "paint.h"

int main(){

    tree_t tree = {};

    expertSystemErrors statusOfExpertSystem = startExpertSystem( &tree );

    checkingTheStatusOfTheExpertSystem( statusOfExpertSystem );

    dumpTree( &tree );

    destroyTree( &tree );

    return 0;
}
