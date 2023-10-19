#include <SDL.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Background(SDL_Renderer* renderer, SDL_Color gris){
    setWindowColor(renderer, gris);
    SDL_RenderPresent(renderer);
}



void Menu_init(SDL_Renderer *renderer, SDL_Color gris){
    Background(renderer,gris);
    SDL_Texture* temp=loadImage("Menu/Concept_Menu2.png",renderer);
    SDL_Rect dest_rect = {262,0};
    charge_image(temp,renderer,dest_rect);
}

void Sous_menu_solo(SDL_Renderer* renderer,SDL_Color gris){
    Background(renderer,gris);
    SDL_Texture* temp=loadImage("Menu/SousMenusolo.png",renderer);
    SDL_Rect dest_rect = {262,0};
    charge_image(temp,renderer,dest_rect);
}

void Sous_menu_2j(SDL_Renderer* renderer,SDL_Color gris){
    Background(renderer,gris);
    SDL_Texture* temp=loadImage("Menu/SousMenu2J.png",renderer);
    SDL_Rect dest_rect = {262,0};
    charge_image(temp,renderer,dest_rect);
}

void Sous_menu_ajout(SDL_Renderer* renderer,SDL_Color gris){
    Background(renderer,gris);
    SDL_Texture* temp=loadImage("Menu/SousMenuaJout.png",renderer);
    SDL_Rect dest_rect = {262,0};
    charge_image(temp,renderer,dest_rect);
}

void Jeusol_2j(SDL_Renderer* renderer,SDL_Color gris){
    Background(renderer,gris);
    SDL_Texture* temp=loadImage("Menu/jeusol-.png",renderer);
    SDL_Rect dest_rect = {262,0};
    charge_image(temp,renderer,dest_rect);
}
