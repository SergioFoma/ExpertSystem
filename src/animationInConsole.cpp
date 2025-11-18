#include <stdio.h>
#include <stdlib.h>

#include "animationInConsole.h"
#include "paint.h"

void printPicture( infoAboutGraphicAnimation *animationInfo ){
    if( animationInfo->fileForAnimation == NULL ){
        colorPrintf( NOMODE, RED, "\nError of open file for animation\n" );
        return ;
    }

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
