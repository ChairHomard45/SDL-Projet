#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>	
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Init.h"
#include "List.h"
#include "Arbre_AVL.h"
#include "Recherche_mot.h"
#include "Bouton.h"
#include "Menu.h"



#define NUM_STRING 230
#define bool unsigned int
#define true 1
#define false 0

/*==-------------------------Initialisation de l'arbre-------------------==*/
Noeud* B=NULL;

/*==--------------Initialisation du tableau de chaîne de caractère-------------==*/
char MotFr[219][31];

/*==--------------------Initialisation de la liste----------------------==*/
NodePointer t = NULL;

/*==----------Nombre aleatoire----------==*/
int NbRandom(int TAILLE_Tableau){
    srand(time(NULL));
    return rand() % TAILLE_Tableau + 0;
}

/*---------Recuperation et stockage dans le tableau de chaine de caractère----------------------*/
void Recup_stock_tabchar(){
    FILE* fic;
    char *ptr_chaine ;
    int num_ligne = 1 ;
    char ligne[200];
    int i=0;
    fic = fopen( "src/Image_sons.csv", "rt") ;
    if (fic==NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
    fgets( ligne, 100, fic);
    while ( fgets( ligne, 100, fic) != NULL  ){
        num_ligne++ ;
        ptr_chaine = strtok (ligne, ";");
        strcpy(MotFr[i],ptr_chaine); //transfer des mots dans le tableau de chaîne de caractère
        i++;
        }
    fclose(fic);
}

/*-----Insertion dans l'arbre--------*/

void retrieve_in_csv(){
    FILE* fic;
    char *ptr_chaine;
    int num_ligne = 1 ;
    char Mot_Fr[31];
    char Mot_ENG[31];
    char Mot_trad1[31];
    char Mot_trad2[31];
    char Mot_IMGpath[31];

    char ligne[200];
    int i=0;
    fic = fopen( "src/Image_sons.csv", "rt") ;
    if (fic==NULL)
    {
        printf("Ouverture fichier impossible !");
        exit(0);
    }
    
    fgets( ligne, 100, fic);
    while ( fgets( ligne, 100, fic) != NULL  ){
        num_ligne++ ;
        //Cellule 1//
        ptr_chaine = strtok (ligne, ";");
        strcpy(Mot_Fr,ptr_chaine);
       
        //Cellule 2//
        ptr_chaine = strtok (NULL, ";");
        strcpy(Mot_ENG,ptr_chaine);
        
        //Cellule 3//
        ptr_chaine = strtok (NULL, ";");
        strcpy(Mot_IMGpath,ptr_chaine);
        
        if ((ptr_chaine = strtok(NULL,";"))!=NULL){
            //Cellule 4//
            if (strcmp(ptr_chaine," ")!=0){strcpy(Mot_trad1,ptr_chaine);}
        }
        i++;
        B=insert(B,Mot_Fr,Mot_ENG,Mot_trad1,Mot_trad2,Mot_IMGpath);
        
        }
        //preOrderPrint(B);
    fclose(fic);
}


/*------Recuperation dans la liste-------*/
void recupinsert(int Recup_numb){
            Noeud *test=searchOnTree(B,MotFr[Recup_numb]);
            char Mot_Eng[31];
            char IMG[31];
            char mot_trad1[31];
            strcpy(Mot_Eng,test->motENG);
            strcpy(IMG,test->IMGpath);
            insertIntoLinkedList(mot_trad1,Mot_Eng,IMG,MotFr[Recup_numb],&t);
}

/*------Load image-------*/
SDL_Texture* Loading_image(SDL_Texture* image, NodePointer t,SDL_Renderer* renderer,SDL_Rect dest_rect){
        char Image_Path[50]={"images_sons/"};
        strcat(Image_Path,t->IMG_path);
        strcat(Image_Path,".jpg");
        image = loadImage(Image_Path, renderer);  
        return image;
} 
/*-------Pour le bouton Passer-------*/
SDL_Texture* passagesuivant(SDL_Texture *image,int a,NodePointer t,SDL_Renderer *renderer,SDL_Rect dest_rect){
    NodePointer current = t; 
    for (int i=0;i<a;i++){
        current = current->next;
    }
    image=Loading_image( image, current, renderer,dest_rect);
    return image;
}

/*------Delay pour le random-------*/
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;
 
    // Storing start time
    clock_t start_time = clock();
 
    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}
/*-----insertion image diff------*/
void boucleinsert(int nbrimg){
    
        for (int i = 0; i<nbrimg;i++){
            
            int Recup_numb=NbRandom(NUM_STRING);
            recupinsert(Recup_numb);
            delay(1);
        }
}

int main(int argc, char *argv[])
{ 
        /*=======================Initialisation des variables====================*/
        SDL_Window *window = NULL;
        SDL_Renderer *renderer = NULL;
        SDL_Texture *texture = NULL;
        SDL_Surface *surface = NULL;
        SDL_Texture *image = NULL;
        SDL_Texture *Message = NULL;
        SDL_Event event;
        bool quit = false;
        SDL_Color gris = {105, 105, 105, 255};
        
        Noeud* Recherche = NULL;

        //Toutes les variables pour les boutons, compteur etc
        int Menu_nb = 1;
        int sous_menusolo = 0;
        int sous_menu2j	= 0;
        int sous_ajmot	= 0; 
        int Lang	= 0;
        int JeuSol	= 0;
        int Jeu2j = 0;  
        int over = 0;
        int Langused = 0;
        int imgs = 0;
        int compt = 1;
        int joueurtour = 0;
        int times = 0;
        int vic = 0;
        int score1 = 0;
        int erreur1 = 0;
        int temp=0;
        int partie = 0;
        int tour = 0;


        //Text
        SDL_Color TextColor = {255,165,0,255};
        TTF_Font* gFont = NULL;
        SDL_Texture *Box = NULL;
        gFont=TTF_OpenFont("bin/arial.ttf", 25);

        //reste
        char Mot_Eng[31];
        char IMG[31];
        char text[31];
        int Recup_numb;
        
        //Pour le sous-menu Ajout Mot
        char path[31];
        char trad[31];
        char anglais[31];
        char francais[31];

        //Bouton et Image taille et position//
        //Bouton Principaux Menu//
        SDL_Rect buttonsolo = {382,172,239,90};
        SDL_Rect buttondeux = {382,287,239,90};
        SDL_Rect buttonajout = {382,404,239,90};
        //Bouton Sous_Menu Solo//
        SDL_Rect img1 = {381,159,74,90};
        SDL_Rect img5 = {461,159,74,90};
        SDL_Rect img10 = {541,159,74,90};

        SDL_Rect FR = {382,272 ,72,90};
        SDL_Rect Ang = {462,272 ,72,90};
        SDL_Rect Trad = {543,272 ,72,90};
        SDL_Rect Reset = {382,361,239,90};

        SDL_Rect Lancement = {384,476,239,90};
        //SDL_Rect
        //Bouton Sous_Menu 2Joueur//
        

        //Bouton Passer//
        SDL_Rect Passer = {394,565,245,90};
        //Bouton Fin//
        SDL_Rect FIN = {394,667,245,90};
        //Autre//
        SDL_Rect buttonRect = {0, 0,230, 230};
        SDL_Rect dest_rect = {394,150,236,236};
        


        int statut = EXIT_FAILURE;
        /*==========================Remplissage de l'arbre=========================*/
        retrieve_in_csv();
        
        /*==============Remplissage du tableau chaîne de caractère===============*/
        Recup_stock_tabchar();

        /*======================Initialisation des systèmes=====================*/
        if(0 != init(&window, &renderer, 1024, 768))
            Clean_up(window,renderer,NULL,NULL,NULL);


        /*====================Initialisation de SDL_Mixer=======================*/
        setMusique();
        Mix_Music* music = Mix_LoadMUS("music/family.mp3"); // Charge notre musique
        if (music == NULL)
            {
 	            fprintf(stderr, "Erreur SDL_AUDIO : %s", SDL_GetError());
 	            Clean_up(window,renderer,NULL,NULL,music);
            }
        Mix_PlayMusic(music, -1);
        
        /*============================================*/
            Menu_init(renderer,gris);
        /*=============================Title====================================*/
        SDL_SetWindowTitle(window, "SDL Jeu");
        
         

        
        /*==========================Icon for the window============================*/
        Uint16 pixels[16*16] = { 
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0aab, 0x0789, 0x0bcc, 0x0eee, 0x09aa, 0x099a, 0x0ddd,
            0x0fff, 0x0eee, 0x0899, 0x0fff, 0x0fff, 0x1fff, 0x0dde, 0x0dee,
            0x0fff, 0xabbc, 0xf779, 0x8cdd, 0x3fff, 0x9bbc, 0xaaab, 0x6fff,
            0x0fff, 0x3fff, 0xbaab, 0x0fff, 0x0fff, 0x6689, 0x6fff, 0x0dee,
            0xe678, 0xf134, 0x8abb, 0xf235, 0xf678, 0xf013, 0xf568, 0xf001,
            0xd889, 0x7abc, 0xf001, 0x0fff, 0x0fff, 0x0bcc, 0x9124, 0x5fff,
            0xf124, 0xf356, 0x3eee, 0x0fff, 0x7bbc, 0xf124, 0x0789, 0x2fff,
            0xf002, 0xd789, 0xf024, 0x0fff, 0x0fff, 0x0002, 0x0134, 0xd79a,
            0x1fff, 0xf023, 0xf000, 0xf124, 0xc99a, 0xf024, 0x0567, 0x0fff,
            0xf002, 0xe678, 0xf013, 0x0fff, 0x0ddd, 0x0fff, 0x0fff, 0xb689,
            0x8abb, 0x0fff, 0x0fff, 0xf001, 0xf235, 0xf013, 0x0fff, 0xd789,
            0xf002, 0x9899, 0xf001, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0xe789,
            0xf023, 0xf000, 0xf001, 0xe456, 0x8bcc, 0xf013, 0xf002, 0xf012,
            0x1767, 0x5aaa, 0xf013, 0xf001, 0xf000, 0x0fff, 0x7fff, 0xf124,
            0x0fff, 0x089a, 0x0578, 0x0fff, 0x089a, 0x0013, 0x0245, 0x0eff,
            0x0223, 0x0dde, 0x0135, 0x0789, 0x0ddd, 0xbbbc, 0xf346, 0x0467,
            0x0fff, 0x4eee, 0x3ddd, 0x0edd, 0x0dee, 0x0fff, 0x0fff, 0x0dee,
            0x0def, 0x08ab, 0x0fff, 0x7fff, 0xfabc, 0xf356, 0x0457, 0x0467,
            0x0fff, 0x0bcd, 0x4bde, 0x9bcc, 0x8dee, 0x8eff, 0x8fff, 0x9fff,
            0xadee, 0xeccd, 0xf689, 0xc357, 0x2356, 0x0356, 0x0467, 0x0467,
            0x0fff, 0x0ccd, 0x0bdd, 0x0cdd, 0x0aaa, 0x2234, 0x4135, 0x4346,
            0x5356, 0x2246, 0x0346, 0x0356, 0x0467, 0x0356, 0x0467, 0x0467,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff,
            0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff, 0x0fff};
    
        surface = SDL_CreateRGBSurfaceFrom(pixels,16,16,16,16*2,0x0f00,0x00f0,0x000f,0xf000);
        SDL_SetWindowIcon(window, surface);
        SDL_FreeSurface(surface);

    /*================Voir si le mot est valide================*/
    
 	


    SDL_RenderPresent(renderer);
    
    /*==================Attend que la fenêtre soit ferme==================*/




while(quit==false){
  SDL_StartTextInput();
  
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quit=true;
    } else if (event.type == SDL_KEYDOWN) {
      if (event.key.keysym.sym == SDLK_BACKSPACE && strlen(text) > 0) {
        text[strlen(text) - 1] = '\0';
        printf("%s\n",text);
      }
      if(event.key.keysym.sym == SDLK_RETURN){
        if(JeuSol==1){
            printf("\nverif mot\n");
            vic=Verif_motsais(t,text,compt,imgs,Langused);
            if(vic==1){
            compt=compt+1;
            if(compt<=imgs){
                image = passagesuivant(image,compt,t,renderer,dest_rect);
                charge_image(image,renderer,dest_rect);
                }
            else{
                image = loadImage("Menu/FIN_LISTE.jpg",renderer);
                charge_image(image,renderer,dest_rect);
            }
            }}
        else if(Jeu2j==1 && joueurtour==0){
            if (tour<partie){
            Recherche = searchOnTree(B,text);
                if(Recherche==NULL){printf("Recommencez Mot n'est pas dans l'arbre");}
            else{
                joueurtour=1;
                char Imagepath[31] = {"images_sons/"};
                strcat(Imagepath,Recherche->IMGpath);
                strcat(Imagepath,".jpg");
                SDL_Texture* jo1 = loadImage(Imagepath,renderer);
                charge_image(jo1,renderer,dest_rect);
                printf("Joueur 1 tour fini\n");}
            }
            else{printf("Fin Partie veuillez appuyer sur FIN");}
        } else if (Jeu2j==1 && joueurtour==1){
            
            temp=0;
            //Francais
            if (Langused==1){
                if(strcmp(Recherche->motFr,text)==0){
                    printf("Reussis Langue FR\n");
                    
                    score1 = score1 + 1;
                    temp=1;
                    tour=tour+1;
                }
                else{printf("Fail");
                erreur1=erreur1+1;}
            }
            //Anglais
            else if (Langused==2){
                if(strcmp(Recherche->motENG,text)==0){
                    printf("Reussis Langue Ang\n");
                    score1 = score1 + 1;
                    temp=1;
                    tour=tour+1;
                }
                else{printf("Fail");
                erreur1=erreur1+1;}
            }
            //Trad1
            else if (Langused==3){
                if(strcmp(Recherche->trad1,text)==0){
                    printf("Reussis Langue Trad1\n");
                    score1 = score1 + 1;
                    temp=1;
                    tour=tour+1;

                }
                else{printf("Fail");
                erreur1=erreur1+1;}
            }
            if (temp==1){
            joueurtour=0;
            printf("Joueur 2 tour fini\n");}
        }else if (sous_ajmot==1){
            if (tour==0){
                strcpy(francais,text);
                tour=tour+1;
                printf("Mot entre:");
            }
            else if (tour==1){
                strcpy(anglais,text);
                tour=tour+1;
                printf("Mot entre:");
            }
            else if (tour==2){
                strcpy(trad,text);
                tour=tour+1;
                printf("Mot entre:");
            }
            else if (tour==3){
                strcpy(path,text);
                tour=tour+1;
                printf("\nTous les mots sont enregistrer, appuier sur le bouton:");
            }
        }
        } 
        } else if (event.type == SDL_TEXTINPUT) {
            if(JeuSol==1){
                strcat(text, event.text.text);
                printf("%s\n",text);
            } else if(Jeu2j==1){
                strcat(text, event.text.text);
                printf("%s\n",text);
            } else if (sous_ajmot==1){
                strcat(text, event.text.text);
                printf("%s\n",text);
            }
        } 
    
    switch (event.type){
        case SDL_MOUSEBUTTONDOWN:
            if(SDL_PRESSED == SDL_BUTTON_LEFT){
                    if (Menu_nb==1){
                        //Boutton Solo//
                        if(( event.motion.x >= buttonsolo.x
                        && event.motion.x < buttonsolo.x + buttonsolo.w
                        && event.motion.y >= buttonsolo.y
                        && event.motion.y < buttonsolo.y + buttonsolo.h ))
                        {
                            
                            printf("bouton Solo \n %d",Menu_nb);
                            Menu_nb = 0;
                            sous_menusolo=1;
                            Sous_menu_solo(renderer,gris);
                        }
                                    
                        //Bouton 2 Joueur//
                        if(( event.motion.x >= buttondeux.x
                        && event.motion.x < buttondeux.x + buttondeux.w
                        && event.motion.y >= buttondeux.y
                        && event.motion.y < buttondeux.y + buttondeux.h ))
                        {
                            Sous_menu_2j(renderer,gris);
                            printf("bouton 2 joueur");
                            Menu_nb = 0;
                            sous_menu2j=1;
                        }
                        {
                            
                        }
                        //Bouton Ajout Mot//
                        if(( event.motion.x >= buttonajout.x
                        && event.motion.x < buttonajout.x + buttonajout.w
                        && event.motion.y >= buttonajout.y
                        && event.motion.y < buttonajout.y + buttonajout.h ))
                        {
                            Sous_menu_ajout(renderer,gris);
                            Bouton_Retour(renderer,FIN);
                            BoutonValide(renderer,Passer);
                            Regle(renderer, dest_rect);
                            printf("bouton ajout mot");
                            Menu_nb = 0;
                            sous_ajmot = 1;
                        }
                    }
                    //==================Sous Menu Solo=================//
                    
                        if(sous_menusolo==1){
                    //Sous Menu Solo//
                    //Sous Bouton Choix 1img 5img 10img//
                                    //1mg
                                    if(( event.motion.x >= img1.x
                                    && event.motion.x < img1.x + img1.w
                                    && event.motion.y >= img1.y
                                    && event.motion.y < img1.y + img1.h ))
                                    {
                                        printf("bouton img1 presse\n");
                                        imgs = 0;
                                    }
                                    //5img
                                    if(( event.motion.x >= img5.x
                                    && event.motion.x < img5.x + img5.w
                                    && event.motion.y >= img5.y
                                    && event.motion.y < img5.y + img5.h ))
                                    {
                                        printf("bouton img5 presse\n");
                                        imgs = 4;
                                    }
                                    //10img
                                    if(( event.motion.x >= img10.x
                                    && event.motion.x < img10.x + img10.w
                                    && event.motion.y >= img10.y
                                    && event.motion.y < img10.y + img10.h ))
                                    {
                                        printf("bouton img10 presse\n");
                                        imgs = 9;
                                    }

                                    if (Lang==1){//Langue Choix 1 2 3
                                    //Francais
                                    if(( event.motion.x >= FR.x
                                    && event.motion.x < FR.x + FR.w
                                    && event.motion.y >= FR.y
                                    && event.motion.y < FR.y + FR.h ))
                                    {
                                        printf("bouton FR presse\n");
                                        Lang=0;
                                        Langused=1;
                                    }
                                    //Anglais
                                    if(( event.motion.x >= Ang.x
                                    && event.motion.x < Ang.x + Ang.w
                                    && event.motion.y >= Ang.y
                                    && event.motion.y < Ang.y + Ang.h ))
                                    {
                                        printf("bouton Ang presse\n");
                                        Lang=0;
                                        Langused=2;
                                    }
                                    //Langue Trad
                                    if(( event.motion.x >= Trad.x
                                    && event.motion.x < Trad.x + Trad.w
                                    && event.motion.y >= Trad.y
                                    && event.motion.y < Trad.y + Trad.h ))
                                    {
                                        printf("bouton Trad presse\n");
                                        Lang=0;
                                        Langused=3;
                                    }}
                                    //Bouton reset lang
                                    if(( event.motion.x >= Reset.x
                                    && event.motion.x < Reset.x + Reset.w
                                    && event.motion.y >= Reset.y
                                    && event.motion.y < Reset.y + Reset.h ))
                                    {
                                        printf("bouton Reset presse\n");
                                        Lang=1;
                                        Langused=0;
                                    }
                                    
                                    //Bouton Lancement
                            if(( event.motion.x >= Lancement.x
                                && event.motion.x < Lancement.x + Lancement.w
                                && event.motion.y >= Lancement.y
                                && event.motion.y < Lancement.y + Lancement.h ))
                                {
                                    printf("bouton lancement");
                                    Jeusol_2j(renderer,gris);
                                    BoutonPasser(renderer,Passer);
                                    BoutonFin(renderer,FIN);
                                    boucleinsert(imgs);
                                    Recup_numb=NbRandom(219);
                                    recupinsert(Recup_numb);
                                    image=Loading_image( image, t, renderer,dest_rect);
                                    charge_image(image,renderer,dest_rect);
                                    //Peut servir pour verifier la liste
                                    //displayLinkedList(t); 
                                    if(Langused==1){printf("ecrire la traduction en Francais");}
                                    else if(Langused==2){printf("ecrire la traduction en Anglais");}
                                    else if(Langused==3){printf("ecrire la traduction dans la troisème langue ajoute");} 
                                    JeuSol=1;
                                    compt = 0;
                                    sous_menusolo=0;
                                    
                                }
                    }
                    //===========================Sous Menu 2 Joueur=======================//
                    if(sous_menu2j==1){
                    //Bouton nombre de partie//
                        //1 Partie//
                                    if(( event.motion.x >= img1.x
                                    && event.motion.x < img1.x + img1.w
                                    && event.motion.y >= img1.y
                                    && event.motion.y < img1.y + img1.h ))
                                    {
                                        printf("bouton 1 partie");
                                        partie = 1;
                                    }
                        //2 Partie//
                                    if(( event.motion.x >= img5.x
                                    && event.motion.x < img5.x + img5.w
                                    && event.motion.y >= img5.y
                                    && event.motion.y < img5.y + img5.h ))
                                    {
                                        printf("bouton 2 partie");
                                        partie = 2;
                                    }
                        //3 Partie//
                                    if(( event.motion.x >= img10.x
                                    && event.motion.x < img10.x + img10.w
                                    && event.motion.y >= img10.y
                                    && event.motion.y < img10.y + img10.h ))
                                    {
                                        printf("bouton 3 partie");
                                        partie = 3;
                                    }

                                    if (Lang==1){//Langue Choix 1 2 3
                                    //Francais
                                    if(( event.motion.x >= FR.x
                                    && event.motion.x < FR.x + FR.w
                                    && event.motion.y >= FR.y
                                    && event.motion.y < FR.y + FR.h ))
                                    {
                                        printf("bouton FR");
                                        Lang=0;
                                        Langused=1;
                                    }
                                    //Anglais
                                    if(( event.motion.x >= Ang.x
                                    && event.motion.x < Ang.x + Ang.w
                                    && event.motion.y >= Ang.y
                                    && event.motion.y < Ang.y + Ang.h ))
                                    {
                                        printf("bouton Ang");
                                        Lang=0;
                                        Langused=2;
                                    }
                                    //Langue Trad
                                    if(( event.motion.x >= Trad.x
                                    && event.motion.x < Trad.x + Trad.w
                                    && event.motion.y >= Trad.y
                                    && event.motion.y < Trad.y + Trad.h ))
                                    {
                                        printf("bouton Trad");
                                        Lang=0;
                                        Langused=3;
                                    }}
                                    //Bouton reset lang
                                    if(( event.motion.x >= Reset.x
                                    && event.motion.x < Reset.x + Reset.w
                                    && event.motion.y >= Reset.y
                                    && event.motion.y < Reset.y + Reset.h ))
                                    {
                                        printf("bouton Reset");
                                        Lang=1;
                                        Langused=0;
                                    }
                        //Bouton Lancement
                        if( (event.motion.x >= Lancement.x
                            && event.motion.x < Lancement.x + Lancement.w
                            && event.motion.y >= Lancement.y
                            && event.motion.y < Lancement.y + Lancement.h ))
                            {
                                printf("bouton lancement \n");
                                Jeusol_2j(renderer,gris);
                                BoutonPasser(renderer,Passer);
                                BoutonFin(renderer,FIN);
                                if(Langused==1){printf("ecrire la traduction en Francais");}
                                else if(Langused==2){printf("ecrire la traduction en Anglais");}
                                else if(Langused==3){printf("ecrire la traduction dans la troisème langue ajoute");} 
                                Jeu2j=1;
                                tour=0;
                                sous_menu2j=0;
                            }
                    }
                        
                    
                    //===============Ajout Mot Sous Menu=======================//
                    
                    if(sous_ajmot==1){
                        //Bouton pour envoyer dans l'arbre
                    if(( event.motion.x >= Passer.x
                        && event.motion.x < Passer.x + Passer.w
                        && event.motion.y >= Passer.y
                        && event.motion.y < Passer.y + Passer.h ))
                        {
                            B=insert(B,francais,anglais,trad,NULL,path);
                            printf("Le noeud a ete creer");
                        }
                        //Bouton retour
                        if(( event.motion.x >= FIN.x
                        && event.motion.x < FIN.x + FIN.w
                        && event.motion.y >= FIN.y
                        && event.motion.y < FIN.y + FIN.h ))
                        {
                        Menu_nb = 1;
                        sous_ajmot = 0;
                        Menu_init(renderer,gris);
                        }
                    }
                    
                    //=====================Jeu Solo==========================//
                    if (JeuSol==1){
                    //Bouton pour passez
                    if(( event.motion.x >= Passer.x
                        && event.motion.x < Passer.x + Passer.w
                        && event.motion.y >= Passer.y
                        && event.motion.y < Passer.y + Passer.h ))
                        {
                            printf("\n y %d",compt);
                            
                            compt=compt+1;
                            if(compt<=imgs){
                            image = passagesuivant(image,compt,t,renderer,dest_rect);
                            charge_image(image,renderer,dest_rect);
                            }
                            else{
                                image = loadImage("Menu/FIN_LISTE.jpg",renderer);
                                charge_image(image,renderer,dest_rect);
                            }
                        }
                    //Bouton pour revenir au menu//
                    if(( event.motion.x >= FIN.x
                        && event.motion.x < FIN.x + FIN.w
                        && event.motion.y >= FIN.y
                        && event.motion.y < FIN.y + FIN.h ))
                        {
                        Menu_nb = 1;
                        JeuSol = 0;
                        printf("Voici votre score et votre nombre d'erreur: Score=%d/Erreur=%d",score1,erreur1);
                        score1=0;
                        erreur1=0;
                        destroyList(&t);
                        Menu_init(renderer,gris);
                        }
                        
                    }
                    
                    //=====================Jeu 2 Joueur==========================//
                    if (Jeu2j==1){
                        //Bouton pour passez
                    if(( event.motion.x >= Passer.x
                        && event.motion.x < Passer.x + Passer.w
                        && event.motion.y >= Passer.y
                        && event.motion.y < Passer.y + Passer.h ))
                        {

                        }
                    //Bouton pour revenir au menu//
                    if(( event.motion.x >= FIN.x
                        && event.motion.x < FIN.x + FIN.w
                        && event.motion.y >= FIN.y
                        && event.motion.y < FIN.y + FIN.h ))
                        {
                        Menu_nb = 1;
                        Jeu2j = 0;
                        Menu_init(renderer,gris);
                        }
                    }

            
                    }
                    break;
                    }

    
    
  
}

SDL_StopTextInput();
}
    

    

Clean_up(window,renderer,NULL,NULL,music);
}

