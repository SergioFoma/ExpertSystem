#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "animationInConsole.h"
#include "paint.h"
#include "expertSystem.h"
#include "myStringFunction.h"

const char* dataBaseWithQuestionAndAnswer[] = {
    "Is the rule \"There are always two of them. No more, no less\" the main law of the Sith during the Galactic Empire?",
    "YES",
    "Was Count Dooku (Darth Tyranus) Yoda's student before turning to the dark side?",
    "NO",
    "Did Darth Vader try to overthrow Emperor Palpatine in order to rule the Galaxy himself?",
    "YES",
    "Do the Sith use lightsabers only in red?",
    "NO",
    "Is the Sith doctrine based on the principle of \"Peace through might\"?",
    "YES"
};
const size_t sizeOfDataBaseWithQuestionAndAnswer = sizeof( dataBaseWithQuestionAndAnswer ) / sizeof( dataBaseWithQuestionAndAnswer[0] );

void printPicture( infoAboutGraphicAnimation *animationInfo ){
    if( animationInfo == NULL ){
        return ;
    }
    if( animationInfo->fileForAnimation == NULL ){
        colorPrintf( NOMODE, RED, "\nError of open file for animation\n" );
        return ;
    }

    /*bufferInformation bufferFromFileForAnimation = {};
    errorCode statusOfInit = initBufferInformation( &bufferFromFile, animationInfo->fileForAnimation, animationInfo->nameOfFileForVideo );
    */
    size_t numberWithColors = 0, redColor = 0, greenColor = 0, blueColor = 0, numberAfterColors = 0;

    for( size_t x = 0; x < animationInfo->height; x++ ){
        for( size_t y = 0; y < animationInfo->width; y++ ){
            fscanf( animationInfo->fileForAnimation, "%lu", &numberWithColors );
            numberAfterColors = numberWithColors % animationInfo->countOfColors;
            numberWithColors /= animationInfo->countOfColors;

            blueColor = numberWithColors % animationInfo->countOfColors;
            numberWithColors /= animationInfo->countOfColors;

            greenColor = numberWithColors % animationInfo->countOfColors;
            numberWithColors /= animationInfo->countOfColors;

            redColor = numberWithColors % animationInfo->countOfColors;

            printf( "\033[48;2;%lu;%lu;%lum%c\033[0m", redColor, greenColor, blueColor, (char)numberAfterColors );
        }
        printf( "\n" );
    }

}

void printVideo( infoAboutGraphicAnimation* animationInfo ){
    if( animationInfo == NULL ){
        return ;
    }

    animationInfo->fileForAnimation = fopen( animationInfo->nameOfFileForVideo, "r" );
    if( animationInfo->fileForAnimation == NULL ){
        return ;
    }

    system( "tput civis" );
    for( size_t indexOfPicture = 0; indexOfPicture < animationInfo->countOfShot; indexOfPicture++ ){
        printPicture( animationInfo );
        printf( "\033[1:1H" );
    }
    system( "tput cnorm" );
    system( "clear" );


    fclose( animationInfo->fileForAnimation );
}

void startMovieSurvey( infoAboutGraphicAnimation* animationInfo ){
    if( animationInfo == NULL ){
        return ;
    }

    srand( time( NULL ) );

    int indexOfQuestion = ( rand() % ( sizeOfDataBaseWithQuestionAndAnswer / 2 ) ) * 2;

    colorPrintf( NOMODE, YELLOW, "%s\n", dataBaseWithQuestionAndAnswer[ indexOfQuestion ] );
    voiceTheLine( dataBaseWithQuestionAndAnswer[ indexOfQuestion ] );

    size_t sizeOfAnswer = 30;
    char* answer = (char*)calloc( sizeOfAnswer, sizeof( char ) );

    expertSystemErrors statusOfTakeAnAnswer = NOT_CORRECT_WORK;
    while( ( statusOfTakeAnAnswer = takeAnAnswer( &answer, &sizeOfAnswer ) ) != CORRECT_WORK ){
        cleanLine( answer );
    }

    if( strcmp( dataBaseWithQuestionAndAnswer[ indexOfQuestion + 1 ], answer ) != 0 ){
        printVideo( animationInfo );
    }

    free( answer );
}
