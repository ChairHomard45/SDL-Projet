# SDL-Projet
Commande pour le faire fonctionner sur windows Mingw:
gcc src/main.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL_mixer
bin\prog.exe 

Commande pour le faire fonctionner sur Linux:
```bash
gcc src/main.c  `sdl-config --cflags --libs` -o bin/prog
bin\prog.exe 
```
Tous d'abord la fonction TTF qui aurait dù servir pour l'affichage du texte sur l'écran n'a pas fonctionner et je n'avais plus de temps ou d'idée pour que celle-ci fonctione, donc j'ai dû modifier
en partie mon code pour qu'il puisse être jouer avec le terminal.
Pour l'ajout d'une langue, il faut remplir a la main le dossier csv dans la première colonne vide.
Cependant les deux modes de jeu fonctionne, le mode solo a quelque ralentissement quand il doit charger et inserer dans une liste le nombre d'image saisis.
Le choix de langue commence par appuyer le bouton Reset qui permet de debloque la variable pour pouvoir choisir.
