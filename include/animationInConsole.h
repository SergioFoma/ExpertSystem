#ifndef H_ANIMATION_IN_CONSOLE
#define H_ANIMATION_IN_CONSOLE

struct infoAboutGraphicAnimation {
    char* nameOfFileForVideo;
    FILE* fileForAnimation;
    size_t width;
    size_t height;
    size_t countOfShot;
    size_t countOfColors;
};

void printPicture( infoAboutGraphicAnimation* animationInfo );

void printVideo( infoAboutGraphicAnimation* animationInfo );

#endif
