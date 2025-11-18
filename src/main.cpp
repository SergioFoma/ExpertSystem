#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "tree.h"
#include "treeDump.h"
#include "expertSystem.h"
#include "paint.h"
#include "animationInConsole.h"

int main(){

    infoAboutGraphicAnimation videoInfo = { "design/fileForVideo.txt", NULL, 354, 84, 300, 256 };
    printVideo( &videoInfo );

    return 0;

    tree_t tree = {};

    expertSystemErrors statusOfExpertSystem = startExpertSystem( &tree );

    checkingTheStatusOfTheExpertSystem( statusOfExpertSystem );

    dumpTree( &tree );

    destroyTree( &tree );

    return 0;
}
