#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>	
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



Noeud *newWord(Noeud *node, char mot_FR[],char mot_ENG[],char mot_trad1[],char mot_trad2[],char IMG_path[]){
    node=insert(node, mot_FR,mot_ENG,mot_trad1,mot_trad2,IMG_path);
    return node;
}