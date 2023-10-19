#include<stdio.h>
#include<stdlib.h>
#include <string.h>

 typedef struct Noeud{ 
    char motFr[31];
    char motENG[31];
    char IMGpath[31]; 
    char trad1[31];
    char trad2[31];
    int height;
    struct Noeud* ABR_gauche;
    struct Noeud* ABR_droit;
}Noeud;

// A utility function to get maximum of two integers
//int max(int a, int b);
 
// A utility function to get height of the tree
int height(struct Noeud *N) {
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}
 
/* Helper function that allocates a new node with the given key and
 NULL left and right pointers. */
Noeud* newNode(char mot_FR[],char mot_ENG[],char mot_trad1[],char mot_trad2[],char IMG_path[]) {
    Noeud* node = (Noeud*) malloc(sizeof(Noeud));
    strcpy(node->motFr,mot_FR);
    strcpy(node->motENG,mot_ENG);
    strcpy(node->IMGpath,IMG_path);
    if(mot_trad1!=NULL){strcpy(node->trad1,mot_trad1);}
    node->ABR_gauche = NULL;
    node->ABR_droit = NULL;
    node->height = 1; // new node is initially added at leaf
    return (node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
Noeud *rightRotate(Noeud* y) {
    Noeud *x = y->ABR_gauche;
    Noeud *T2 = x->ABR_droit;
 
    // Perform rotation
    x->ABR_droit = y;
    y->ABR_gauche = T2;
 
    // Update heights
    y->height = max(height(y->ABR_gauche), height(y->ABR_droit)) + 1;
    x->height = max(height(x->ABR_gauche), height(x->ABR_droit)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
Noeud *leftRotate(Noeud *x) {
    Noeud *y = x->ABR_droit;
    Noeud *T2 = y->ABR_gauche;
 
    // Perform rotation
    y->ABR_gauche = x;
    x->ABR_droit = T2;
 
    //  Update heights
    x->height = max(height(x->ABR_gauche), height(x->ABR_droit)) + 1;
    y->height = max(height(y->ABR_gauche), height(y->ABR_droit)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Noeud *N) {
    if (N == NULL)
        return 0;
    return height(N->ABR_gauche) - height(N->ABR_droit);
}
 
Noeud *insert(Noeud *node, char mot_FR[],char mot_ENG[],char mot_trad1[],char mot_trad2[],char IMG_path[]) {
    /* 1.  Perform the normal BST rotation */
    if (node == NULL)
        return (newNode(mot_FR,mot_ENG,mot_trad1,mot_trad2,IMG_path));
 
    if (strcmp(mot_FR,node->motFr)<=0)
        node->ABR_gauche = insert(node->ABR_gauche, mot_FR,mot_ENG,mot_trad1,mot_trad2,IMG_path);
    else
        node->ABR_droit = insert(node->ABR_droit, mot_FR,mot_ENG,mot_trad1,mot_trad2,IMG_path);
 
    /* 2. Update height of this ancestor node */
    node->height = max(height(node->ABR_gauche), height(node->ABR_droit)) + 1;
 
    /* 3. Get the balance factor of this ancestor node to check whether
     this node became unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then there are 4 cases
 
    // Left Left Case
    if (balance > 1 && strcmp(mot_FR,node->ABR_gauche->motFr)<=0)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && strcmp(mot_FR,node->ABR_droit->motFr)>=0)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && strcmp(mot_FR,node->ABR_gauche->motFr)>=0) {
        node->ABR_gauche = leftRotate(node->ABR_gauche);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && strcmp(mot_FR,node->ABR_droit->motFr)<=0) {
        node->ABR_droit = rightRotate(node->ABR_droit);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints height of every node
void preOrderPrint(Noeud *BNoeud) {
    if(BNoeud!=NULL){printf("\n");
    printf("%s ", BNoeud->motFr);
    printf("%s ", BNoeud->motENG);
    printf("%s ", BNoeud->IMGpath);
    if(BNoeud->trad1!=NULL){printf("%s ",BNoeud->trad1);}
    printf("%d", BNoeud->height);
    preOrderPrint(BNoeud->ABR_gauche);
    preOrderPrint(BNoeud->ABR_droit);
    }
}

Noeud* searchOnTree(Noeud *BNoeud, char mot_FR[] )
{
    Noeud *currentNoeud = BNoeud;
    int flag = 0;
    
    if (currentNoeud==NULL){return NULL;}
    else{
        
        if(strcmp(mot_FR,currentNoeud->motFr)==0)
        {
            return currentNoeud;
        }
        else {
            if (searchOnTree(currentNoeud->ABR_gauche,mot_FR)==NULL){
                return searchOnTree(currentNoeud->ABR_droit,mot_FR);
            }
            else {return searchOnTree(currentNoeud->ABR_gauche,mot_FR);}
        }
    }
}

