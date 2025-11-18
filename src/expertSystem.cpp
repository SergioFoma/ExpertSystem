#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "expertSystem.h"
#include "myStringFunction.h"
#include "paint.h"
#include "parseFileDataBase.h"
#include "animationInConsole.h"

const size_t maxLenForAnswer = 40;      // start size for answer from user
size_t startPosition = 0;               // start position for read from file
const size_t countOfColorsInRGB = 256;  // for color animation
const size_t sizeOfPicture = 50;        // width ang hight of picture
const size_t sizeOfVideo = 150;         // width and hight of video
const size_t countOfPicture = 951;      // count of pictures

expertSystemErrors startExpertSystem( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }

    expertSystemErrors statusOfSystem = CORRECT_WORK;
    char userChoice = '\0';
    colorPrintf( NOMODE, YELLOW, "Expert system loading...\nI'm a expert system - choose an object and i'm guess it\n\n" );
    voiceTheLine( "Expert system loading. I'm a expert system - choose an object and i'm guess it" );

    while( true ){
        colorPrintf( NOMODE, BLUE, "What do you want?\n"
                                   "[r] - read data base from your file\n"
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
            voiceTheLine( "Expert system finish her work" );
            return CORRECT_WORK;
        }

        switch( userChoice ){
            case REED_DATA_BASE:
                statusOfSystem = createTreeFromFile( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            case GUESSES:
                statusOfSystem = guessElement( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            case WRITE_IN_FILE:
                statusOfSystem = writeInformationInFile( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                colorPrintf( NOMODE, GREEN, "Information about database write in file!\n" );
                voiceTheLine( "Information about database write in file" );
                break;
            case GIVE_DEFINITION:
                statusOfSystem = giveDefinition( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            case GIVE_DIFFERENCES:
                statusOfSystem = giveDifferences( tree );
                if( statusOfSystem != CORRECT_WORK ){
                    return statusOfSystem;
                }
                break;
            default:
                colorPrintf( NOMODE, RED, "You have entered an unknown command, try again.\n" );
                voiceTheLine( "You have entered an unknown command, try again." );
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
    else if( tree->rootTree == NULL ){
        initTree( tree );
    }

    node_t* nodePtr = tree->rootTree;
    node_t* previousNodePtr = nodePtr;

    size_t sizeOfAnswer = maxLenForAnswer;
    char* answer = (char*)calloc( sizeOfAnswer, sizeof( char ) );
    if( answer == NULL ){
        return CAN_NOT_DO_ALLOCATION;
    }

    expertSystemErrors systemErr = goToSheetOfTree( &nodePtr, &previousNodePtr, &answer, &sizeOfAnswer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    if( strcmp( answer, "YES" ) == 0 ){
        colorPrintf( NOMODE, GREEN, "\n\nThe expert system guessed the hidden object!\n\n" );
        voiceTheLine( "The expert system guessed the hidden object!" );
        free( answer );
        return CORRECT_WORK;

    }

    systemErr = insertNewElement( &previousNodePtr, &answer, &sizeOfAnswer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    return CORRECT_WORK;
}

expertSystemErrors goToSheetOfTree( node_t** nodePtr, node_t** previousNodePtr, char** answer, size_t* sizeOfAnswer ){
    if( nodePtr == NULL || previousNodePtr == NULL || answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    expertSystemErrors systemErr = CORRECT_WORK;

    infoAboutGraphicAnimation pictureInfo = {
        "design/fileForOutput.txt",
        NULL,
        sizeOfPicture,
        sizeOfPicture,
        countOfPicture,
        countOfColorsInRGB
    };

    do{
        cleanLine( *answer );

        //printPicture( &pictureInfo );
        colorPrintf( NOMODE, BLUE, treeValueFormat "?\n", (*nodePtr)->data );
        voiceTheLine( (*nodePtr)->data );
        systemErr = takeAnAnswer( answer, sizeOfAnswer );
        while( systemErr != CORRECT_WORK ){
            cleanLine( *answer );
            systemErr = takeAnAnswer( answer, sizeOfAnswer );
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

expertSystemErrors insertNewElement( node_t** previousNodePtr, char** answer, size_t* sizeOfAnswer ){
    if( previousNodePtr == NULL || answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    colorPrintf( NOMODE, YELLOW, "\n\nWhat name of this object?\n\n" );
    voiceTheLine( "What name of this object?" );
    cleanLine( *answer );
    expertSystemErrors systemErr = takeNameOfObject( answer, sizeOfAnswer );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    initNode( &( (*previousNodePtr)->left ), *answer  ) ;

    colorPrintf( NOMODE, YELLOW, "\n\nHow is different from %s?\n\n", (*previousNodePtr)->data );
    voiceTheLine( "How do they differ?" );

    size_t sizeOfDifferences = maxLenForAnswer;
    char* differences = (char*)calloc( sizeOfDifferences, sizeof( char ) );

    systemErr = takeNameOfObject( &differences, &sizeOfDifferences );
    if( systemErr != CORRECT_WORK ){
        return systemErr;
    }

    initNode( &( (*previousNodePtr)->right), (*previousNodePtr)->data );

    (*previousNodePtr)->data = differences;

    colorPrintf( NOMODE, GREEN, "\nI am remember this object and added to my data base\n" );
    voiceTheLine( "I am remember this object and added to my data base" );

    return CORRECT_WORK;
}

expertSystemErrors takeAnAnswer( char** answer, size_t* sizeOfLine ){
    if( answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    char* lineForRecording = NULL;
    size_t sizeOfAllocationMemory = 0;
    ssize_t statusOfGetline = getlineWrapper( &lineForRecording, &sizeOfAllocationMemory, stdin );
    if( statusOfGetline == -1 ){
        return ERROR_WITH_GETLINE;
    }

    size_t lineIndex = 0;
    int statusOfClean = 0;

    while( lineForRecording[ lineIndex ] != '\0' && lineForRecording[ lineIndex ] != ' ' ){
        if( lineIndex == *sizeOfLine - 1 ){
            (*sizeOfLine) *= 2;
            (*answer) = (char*)realloc( *answer, sizeof( char ) * (*sizeOfLine) );
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
        voiceTheLine( "Your answer in too long" );
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
        voiceTheLine( "Your answer should be \"YES\" or \"NO\" ");
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

expertSystemErrors takeNameOfObject( char** answer, size_t* sizeOfLine ){
    if( answer == NULL ){
        return NULL_PTR_IN_FUNC;
    }

    ssize_t statusOfGetline = getlineWrapper( answer, sizeOfLine, stdin );
    if( statusOfGetline == -1 ){
        return ERROR_WITH_GETLINE;
    }

    return CORRECT_WORK;
}

expertSystemErrors giveDefinition( tree_t* tree ){
    if( tree == NULL ){
        return TREE_NULL_PTR;
    }
    else if( tree->rootTree == NULL ){
        return ROOT_NULL_PTR;
    }

    colorPrintf( NOMODE, YELLOW, "Enter the name of object: " );
    voiceTheLine( "Enter the name of object: " );

    size_t sizeOfName = maxLenForAnswer;
    char* nameOfObject = (char*)calloc( sizeOfName, sizeof( char ) );
    if( nameOfObject == NULL ){
        return CAN_NOT_DO_ALLOCATION;
    }

    takeNameOfObject( &nameOfObject, &sizeOfName );

    informationAboutFind statusOfFind = printDefinition( tree->rootTree, nameOfObject );
    if( statusOfFind == NOT_FIND ){
        colorPrintf( NOMODE, RED, "You enter the name of unknown object. Try again\n" );
        voiceTheLine( "You enter the name of unknown object. Try again" );
    }

    free( nameOfObject );
    return CORRECT_WORK;
}

informationAboutFind printDefinition( node_t* node, char* answer ){
    if( node == NULL || answer == NULL ){
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
    else if( tree->rootTree == NULL ){
        return ROOT_NULL_PTR;
    }

    size_t sizeOfFirstObject = maxLenForAnswer;
    char* firstObject = (char*)calloc( sizeOfFirstObject, sizeof( char ) );
    size_t sizeOfSecondObject = maxLenForAnswer;
    char* secondObject = (char*)calloc( sizeOfSecondObject, sizeof( char ) );

    colorPrintf( NOMODE, YELLOW, "You have selected the option to compare two objects\n"
                                 "Enter the name of the first one: " );
    voiceTheLine(  "You have selected the option to compare two objects. Enter the name of the first one: " );

    expertSystemErrors statusOfProgramWork = takeNameOfObject( &firstObject, &sizeOfFirstObject );
    if( statusOfProgramWork != CORRECT_WORK ){
        return statusOfProgramWork;
    }

    colorPrintf( NOMODE, YELLOW, "\nEnter the name of second one: " );
    voiceTheLine( "Enter the name of second one: " );
    statusOfProgramWork = takeNameOfObject( &secondObject, &sizeOfSecondObject);
    if( statusOfProgramWork != CORRECT_WORK ){
        return statusOfProgramWork;
    }

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
        colorPrintf( NOMODE, PURPLE, ",but " );
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

void checkingTheStatusOfTheExpertSystem( expertSystemErrors statusOfExpertSystem ){
    switch( statusOfExpertSystem ){
        case CORRECT_WORK:
            return ;
        case CAN_NOT_DO_ALLOCATION:
            colorPrintf( NOMODE, RED, "\nError of allocation memory\n" );
            voiceTheLine( "Error of allocation memory" );
            break;
        case ERROR_WITH_GETLINE:
            colorPrintf( NOMODE, RED, "\nSystem get error from getline\n" );
            voiceTheLine( "System get error from getline" );
            break;
        case NOT_CORRECT_WORK:
            colorPrintf( NOMODE, RED, "\nExpert system have error with get an answer\n" );
            voiceTheLine( "Expert system have error with get an answer" );
            break;
        case ERROR_OF_CLEAN:
            colorPrintf( NOMODE, RED, "\nSystem can not clean line after your answer\n" );
            voiceTheLine( "System can not clean line after your answer" );
            break;
        case TREE_NULL_PTR:
            colorPrintf( NOMODE, RED, "\nSystem get a null ptr on your tree\n" );
            voiceTheLine( "System get a null ptr on your tree" );
            break;
        case TREE_ERRORS:
            colorPrintf( NOMODE, RED, "\nSystem get errors from tree functions\n" );
            voiceTheLine( "System get errors from tree functions" );
            break;
        case NULL_PTR_IN_FUNC:
            colorPrintf( NOMODE, RED, "\nSystem get null ptr\n" );
            voiceTheLine( "System get null ptr" );
            break;
        case ERROR_WITH_FILE:
            colorPrintf( NOMODE, RED, "\nSystem have error with files\n" );
            voiceTheLine( "System have error with files" );
            break;
        case ROOT_NULL_PTR:
            colorPrintf( NOMODE, RED, "\nSystem get null ptr on root of tree\n" );
            voiceTheLine( "System get null ptr on root of tree" );
            break;
        default:
            return ;
    }
}

void voiceTheLine( const char* lineThatNeedVoiced ){

    size_t sizeOfLine = ( strlen( lineThatNeedVoiced ) + strlen( "echo \"" ) + strlen( "\" | festival --tts" ) + 1 )* sizeof( char );

    char* lineForSystem = (char*)calloc( sizeOfLine , sizeof( char ) );

    snprintf( lineForSystem, sizeOfLine, "echo \"%s\" | festival --tts", lineThatNeedVoiced );

    system( lineForSystem);

    free( lineForSystem );
}

