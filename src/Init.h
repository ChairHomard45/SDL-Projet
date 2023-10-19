#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*=======================initialise la fenêtre et le render==========================*/
int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if(0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

/*==============================Fonction pour charger l'image===================================*/
SDL_Texture *loadImage(const char path[], SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL; 
    SDL_Texture *texture = NULL;
    tmp = IMG_Load(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP tmp : %s\n", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s \n", SDL_GetError());
        return NULL;
    }
    return texture;
}




void charge_image(SDL_Texture *imag,SDL_Renderer *render,SDL_Rect dest_rect){
if (SDL_QueryTexture(imag,NULL,NULL,&dest_rect.w,&dest_rect.h) != 0){
            fprintf(stderr, "Erreur SDL_QueryTexture : %s", SDL_GetError());
            SDL_QUIT;
        }
        
        if(SDL_RenderCopy(render,imag,NULL,&dest_rect) != 0){
            fprintf(stderr, "Erreur SDL_RenderCopy : %s", SDL_GetError());
            SDL_QUIT;
        }
     
        SDL_RenderPresent(render);
        }


int Regle(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/REGLE.jpg", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

/*==================================Charge la couleur de la fenêtre========================*/
int setWindowColor(SDL_Renderer *renderer, SDL_Color color){
    if(SDL_SetRenderDrawColor(renderer, color.r, color.g,color.b, color.a) < 0)
        return -1;
    if(SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}


/*==================================Fonction pour la musique===============================*/
int setMusique(){
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)
        {
 	        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
 	        return -1;
        }
    return 1;
}

/*================================Tous fermer================================================*/
int Clean_up(SDL_Window *window,SDL_Renderer *renderer,SDL_Texture *texture,SDL_Texture *image, Mix_Music* music){
       Mix_FreeMusic(music);/* La musique est terminée, on la libère */
            Mix_CloseAudio();
        if(NULL != image)
        SDL_DestroyTexture(image);
        if(NULL != texture)
            SDL_DestroyTexture(texture);
        if(NULL != renderer)
            SDL_DestroyRenderer(renderer);
        if(NULL != window)
            SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
        }