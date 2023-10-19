#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Saissis_mot(char *motsais){
    scanf("%31s",motsais);
}



int Verif_motsais(NodePointer t,char motsais[],int times,int a, int lang){
    
    printf("Liste2\n");
    displayLinkedList(t);
    int i = 1;
    if(a>1){
    for(i=0;i<times;i++){
        t=t->next;
    }}
    
    if (lang == 1||lang==0){
        if (strcmp(t->motfrance,motsais)==0){
        printf("Bravo! vous avez trouver la traduction");
        return 1;
        }
        else{printf("Dommage, perdu\n");
        
        return 0;
        }
    }
    else if (lang==2){

        if (strcmp(t->mot_ang,motsais)==0){
        
        printf("Bravo! vous avez trouver la traduction");
        
        return 1;
        }
        else{printf("Dommage, perdu\n");
        return 0;
        }
        }
        else if (lang==3){

            if (strcmp(t->mot_a_chercher,motsais)==0){
        printf("Bravo! vous avez trouver la traduction");
        return 1;
        }
        else{printf("Dommage, perdu\n");
        return 0;
        }
    }

}

/*int Boucle_verif(NodePointer t,char *motsais,int a, int lang){
    int eval = 0;
    int vic = 0;
    while (eval<3){
    Saissis_mot(motsais);
    vic = Verif_motsais(t,motsais,eval,a, lang);
    eval=eval+1;
    if (vic==1){return 1;}
    }
    return 0;
}*/