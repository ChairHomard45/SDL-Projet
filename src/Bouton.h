#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>	
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void genere_bout(SDL_Renderer* renderer,SDL_Rect buttonRect){
    SDL_Texture *playButton = loadImage("Bouton/Test_Bouton.png", renderer);
    charge_image(playButton,renderer,buttonRect);
}

int first_bouton(SDL_Renderer *renderer, SDL_Rect buttonRect){
SDL_Texture *playButton = loadImage("Bouton/Test_Bouton.png", renderer);
    charge_image(playButton,renderer,buttonRect);
    return 0;}

int solo_bouton(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Solo.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

int deuxjoueurbouton(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/2_joueur.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

int ajoutmotbouton(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Ajoutmot.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

int BoutonPasser(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Bouton_pass.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

int BoutonValide(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Bouton_Valide.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}

int BoutonFin(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Bouton_Fin.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}
    
int Bouton_Retour(SDL_Renderer* renderer, SDL_Rect buttonRect){
    SDL_Texture *playButton2 = loadImage("Bouton/Bouton_Retour.png", renderer);
    charge_image(playButton2,renderer,buttonRect);
    return 1;}
    