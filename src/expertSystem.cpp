#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "expertSystem.h"
#include "myStringFunction.h"
#include "paint.h"
#include "treeDump.h"

size_t maxLenForAnswer = 40;        // start size for answer from user

expertSystemErrors startExpertSystem( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    char userChoice = '\0';
    expertSystemErrors statusOfSystem = CORRECT_WORK;
    colorPrintf( NOMODE, YELLOW, "Expert system loading...\nI'm a expert system - choose an object and i'm guess it\n\n" );
    while( true ){
        colorPrintf( NOMODE, BLUE, "What do you want?\n"
                                "[g] - guesses\n"
                                "[w] - write in file\n"
                                "[d] - give a definition\n"
                                "[f] - give differences\n"
                                "[s] - stop\n"
                                "Your choice: " );

        scanf( "%1c", &userChoice );
        cleanBuffer();
        if( userChoice == 's' ){
            colorPrintf( NOMODE, GREEN, "\nExpert system finish her work\n" );
            return CORRECT_WORK;
        }

        switch( userChoice ){
            case 'g':
                statusOfSystem = guessElement( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            case 'w':
                statusOfSystem = writeInformationInFile( tree );
                if( statusOfSystem == CORRECT_WORK ){
                    colorPrintf( NOMODE, GREEN, "Information about database write in file!\n" );
                }
                break;
            case 'd':
                statusOfSystem = giveDefinition( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            case 'f':
                statusOfSystem = giveDifferences( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            default:
                colorPrintf( NOMODE, RED, "You have entered an unknown command, try again.\n" );
                break;
        }
        printf( "\n\n" );
    }

    return CORRECT_WORK;
}

expertSystemErrors guessElement( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    node_t* nodePtr = tree->rootTree;
    node_t* previousNodePtr = nodePtr;

    char* answer = (char*)calloc( maxLenForAnswer, sizeof( char ) );
    if( answer == NULL ){
        return CAN_NOT_DO_ALLOCATION;
    }

    expertSystemErrors systemErr = goToSheetOfTree( &nodePtr, &previousNodePtr, &answer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    if( strcmp( answer, "YES" ) == 0 ){
        colorPrintf( NOMODE, GREEN, "\n\nThe expert system guessed the hidden object!\n\n" );
        free( answer );
        return CORRECT_WORK;

    }

    systemErr = makeNewObject( &previousNodePtr, &answer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    return CORRECT_WORK;
}

expertSystemErrors goToSheetOfTree( node_t** nodePtr, node_t** previousNodePtr, char** answer ){
    if( nodePtr == NULL || previousNodePtr == NULL || answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    expertSystemErrors systemErr = CORRECT_WORK;
    do{
        cleanLine( *answer );

        colorPrintf( NOMODE, BLUE, treeValueFormat "?\n", (*nodePtr)->data );
        systemErr = takeAnAnswer( answer );
        while( systemErr != CORRECT_WORK ){
            cleanLine( *answer );
            systemErr = takeAnAnswer( answer );
        }

        *previousNodePtr = *nodePtr;
        if( strcmp( *answer, "YES") == 0 ){
            *nodePtr = (*nodePtr)->left ;
        }
        else{
            *nodePtr = (*nodePtr)->right;
        }


    }while( (*nodePtr) );

    return CORRECT_WORK;
}

expertSystemErrors makeNewObject( node_t** previousNodePtr, char** answer ){
    if( previousNodePtr == NULL || answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    colorPrintf( NOMODE, YELLOW, "\n\nWhat name of this object?\n\n" );
    cleanLine( *answer );
    expertSystemErrors systemErr = takeNameOfObject( answer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    initNode( &( (*previousNodePtr)->left ), *answer  ) ;

    colorPrintf( NOMODE, YELLOW, "\n\nHow is different from %s?\n\n", (*previousNodePtr)->data );

    char* differences = (char*)calloc( maxLenForAnswer, sizeof( char ) );

    systemErr = takeNameOfObject( &differences );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    initNode( &( (*previousNodePtr)->right), (*previousNodePtr)->data );

    (*previousNodePtr)->data = differences;

    colorPrintf( NOMODE, GREEN, "\nI am remember this object and added to my data base\n" );

    return CORRECT_WORK;
}

expertSystemErrors takeAnAnswer( char** answer ){
    if( answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    char* lineForRecording = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = myGetline( &lineForRecording, &sizeOfAllocationMemory, stdin );
    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    size_t lineIndex = 0;
    int statusOfClean = 0;

    while( lineForRecording[ lineIndex ] != '\0' && lineForRecording[ lineIndex ] != ' ' ){
        if( lineIndex == maxLenForAnswer - 1 ){
            maxLenForAnswer *= 2;
            (*answer) = (char*)realloc( *answer, sizeof( char ) * maxLenForAnswer );
            if( *answer == NULL ){
                return CAN_NOT_DO_ALLOCATION;
            }
        }

        (*answer)[ lineIndex ] = lineForRecording[ lineIndex ];
        ++lineIndex;
    }

    (*answer)[ lineIndex ] = '\0';

    if( strlen( (*answer) ) != strlen( lineForRecording ) ){
        colorPrintf( NOMODE, RED, "\n\nYour answer in too long\n\n" );
        statusOfClean = cleanLine( (*answer) );
        if( statusOfClean != 0 ){
            free( lineForRecording );
            return ERROR_OF_CLEAN;
        }
        free( lineForRecording );
        return NOT_CORRECT_WORK;
    }
    else if( strcmp( (*answer), "NO" ) != 0 && strcmp( (*answer), "YES" ) != 0 ){
        colorPrintf( NOMODE, RED, "\n\nYour answer should be \"YES\" or \"NO\"\n\n" );
        statusOfClean = cleanLine( (*answer) );
        if( statusOfClean != 0 ){
            free( lineForRecording );
            return ERROR_OF_CLEAN;
        }
        free( lineForRecording );
        return NOT_CORRECT_WORK;
    }

    free( lineForRecording );
    return CORRECT_WORK;

}

expertSystemErrors takeNameOfObject( char** answer ){
    if( answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    char* lineForRecording = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t sizeOfLine = myGetline( &lineForRecording, &sizeOfAllocationMemory, stdin );
    if( sizeOfLine == -1 ){
        return ERROR_WITH_GETLINE;
    }

    size_t lineIndex = 0;

    while( lineForRecording[ lineIndex ] != '\0' ){
        if( lineIndex == maxLenForAnswer - 1 ){
            maxLenForAnswer *= 2;
            (*answer) = (char*)realloc( *answer, sizeof( char ) * maxLenForAnswer );
            if( *answer == NULL ){
                return CAN_NOT_DO_ALLOCATION;
            }
        }

        (*answer)[ lineIndex ] = lineForRecording[ lineIndex ];
        ++lineIndex;
    }

    (*answer)[ lineIndex ] = '\0';

    free( lineForRecording );
    return CORRECT_WORK;
}

void cleanBuffer(){
    int symbol = '\0';
    while( ( symbol = getchar() ) != '\n' );
}

expertSystemErrors writeInformationInFile( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    FILE* fileForTree = fopen( "treeInformation.txt", "w" );

    dumpTreeInFile( tree, fileForTree );

    return CORRECT_WORK;
}

expertSystemErrors giveDefinition( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "Enter the name of object: " );
    char* nameOfObject = (char*)calloc( maxLenForAnswer, sizeof( char ) );
    if( nameOfObject == NULL ){
        return CAN_NOT_DO_ALLOCATION;
    }

    takeNameOfObject( &nameOfObject );

    informationAboutFind statusOfFind = printDefinition( tree->rootTree, nameOfObject );
    if( statusOfFind == NOT_FIND ){
        colorPrintf( NOMODE, RED, "You enter the name of unknown object. Try again\n" );
    }

    free( nameOfObject );
    return CORRECT_WORK;
}

informationAboutFind printDefinition( node_t* node, char* answer ){
    if( node == NULL ){
        return NOT_FIND;
    }

    if( node->left && strcmp( answer, (node->left)->data ) == 0 ){
        colorPrintf( NOMODE, PURPLE, "%s: %s ", answer, node->data );
        return FIND_PRINT_YES;
    }
    if( node->right && strcmp( answer, (node->right)->data ) == 0 ){
        colorPrintf( NOMODE, PURPLE, "%s: no %s ", answer, node->data );
        return FIND_PRINT_NO;
    }

    informationAboutFind statusOfFinding = NOT_FIND;
    if( node->left ){
        statusOfFinding= printDefinition( node->left, answer );
        if( statusOfFinding != NOT_FIND ){
            colorPrintf( NOMODE, PURPLE, ",%s ", node->data );
            return FIND_PRINT_YES;
        }
    }
    if( node->right ){
        statusOfFinding = printDefinition( node->right, answer );
        if( statusOfFinding != NOT_FIND ){
            colorPrintf( NOMODE, PURPLE, ",no %s ", node->data );
            return FIND_PRINT_NO;
        }
    }

    return NOT_FIND;
}

expertSystemErrors giveDifferences( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    char* firstObject = (char*)calloc( maxLenForAnswer, sizeof( char ) );
    char* secondObject = (char*)calloc( maxLenForAnswer, sizeof( char ) );

    colorPrintf( NOMODE, YELLOW, "You have selected the option to compare two objects\nEnter the name of the first one: " );
    expertSystemErrors statusOfProgramWork = takeNameOfObject( &firstObject );
    if( statusOfProgramWork != CORRECT_WORK ){
        return statusOfProgramWork;
    }
    colorPrintf( NOMODE, BLUE, "\n%s\n", firstObject );

    colorPrintf( NOMODE, YELLOW, "\nEnter the name of second one: " );
    statusOfProgramWork = takeNameOfObject( &secondObject );
    if( statusOfProgramWork != CORRECT_WORK ){
        return statusOfProgramWork;
    }
    colorPrintf( NOMODE, BLUE, "\n%s\n", secondObject );


    printDifferences( tree->rootTree, firstObject, secondObject );

    free( firstObject );
    free( secondObject );

    return CORRECT_WORK;
}

informationAboutFind printDifferences( node_t* node, char* firstObject, char* secondObject ){
    if( node == NULL || firstObject == NULL || secondObject == NULL ){
        return ERROR_OF_FIND;
    }

    if( strcmp( firstObject, node->data ) == 0 ){
        return FIND_FIRST_OBJECT;
    }
    else if( strcmp( secondObject, node->data ) == 0 ){
        return FIND_SECOND_OBJECT;
    }

    informationAboutFind statusOfDetectedFromLeft = FINISH_FIND;
    informationAboutFind statusOfDetectedFromRight = FINISH_FIND;

    if( node->left ){
        statusOfDetectedFromLeft = printDifferences( node->left, firstObject, secondObject );
    }
    if( node->right ){
        statusOfDetectedFromRight = printDifferences( node->right, firstObject, secondObject );
    }

    if( statusOfDetectedFromLeft == FIND_FIRST_OBJECT && statusOfDetectedFromRight == FIND_SECOND_OBJECT ){
        printDefinition( node, firstObject );
        colorPrintf( NOMODE, PURPLE, " ,but " );
        printDefinition( node, secondObject );
        return FINISH_FIND;
    }
    else if( statusOfDetectedFromLeft == FIND_SECOND_OBJECT && statusOfDetectedFromRight == FIND_FIRST_OBJECT ){
        printDefinition( node, firstObject );
        colorPrintf( NOMODE, PURPLE, " ,but " );
        printDefinition( node, secondObject );
        return FINISH_FIND;
    }

    if( statusOfDetectedFromLeft != FINISH_FIND ){
        return statusOfDetectedFromLeft;
    }
    else if( statusOfDetectedFromRight != FINISH_FIND ){
        return statusOfDetectedFromRight;
    }

    return FINISH_FIND;
}
