#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "story.h"
#include "utils.h"

void displayknight(){
    printf("##########################################\n");
    printf("#                                        #\n");
    printf("#                   cdx.                 #\n");
    printf("#                 .dWXNo                 #\n");
    printf("#                  'cWXXx                #\n");
    printf("#                 .lkKXX'                #\n");
    printf("#                ,XMMNKWO.               #\n");
    printf("#               .XXXNWNN0NN0d,           #\n");
    printf("#              .XKXNWWWMMNNMMo           #\n");
    printf("#             ;WMWNKNNNXXWWNN            #\n");
    printf("#           ;KMMMMWNKNWKNWMK.            #\n");
    printf("#        .oNMMMMMMWWWNXMMNd              #\n");
    printf("#       :WMMMMMMMMWNNWNXMMk              #\n");
    printf("#       o.'0MMMMMMMNWo  0NN.             #\n");
    printf("#         .ooOX0cOXMl   ON0              #\n");
    printf("#        .'      ,WX    cNX              #\n");
    printf("#                 Wd     kW'             #\n");
    printf("#                .x0d'   :kko;           #\n");
    printf("#                                        #\n");
    printf("##########################################\n");
}




void playstory(int chapter) {
    switch (chapter) {
        case 1:
            displayknight();
            printf("Chapter 1\n");
            sleep(1);
            printf("The journey begins in a small village...\n");

            break;
        case 2:
            printf("Chapter 2: The Dark Forest Awaits...\n");
            break;
        default:
            printf("Chapter %d: Story content coming soon...\n", chapter);
            break;
    }
    start_combat(chapter);
}