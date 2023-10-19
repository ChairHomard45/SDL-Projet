#include <stdio.h>
#include <stdlib.h> //has functions malloc() and free()
#include <string.h>


#define NUM_STRING 230
/*
A self-referential structures contains a pointer 
that points to another structure of the same type
and link together to form dynamic data structures.
data: stores a word (string)
next: is a pointer to the next node
*/
struct list_t{
    char motfrance[31];
    char mot_ang[31]; //30 case utilisanle et la 31eme réserver por '\0'
    char mot_a_chercher[31]; //30 case utilisanle et la 31eme réserver por '\0'
    char IMG_path[31];
    struct list_t* next;
};

//type definition for "new" data types
typedef struct list_t Node;
typedef struct list_t* NodePointer;

//function prototypes 
void insertIntoLinkedList(char [],char [],char [],char [], NodePointer *);
void displayLinkedList(NodePointer);
//void deleteFromLinkedList(char [], NodePointer *);

/*
Inserts a word in alphabetical order into a linked list
motfr: is a string
head2: is the a pointer to the 1st node in a linked list 
This parameter is a pointer to a pointer, 
because we are passing the address of the linked list to the function, 
and the linked list itself is a pointer to the 1st node in the list.
*/
void insertIntoLinkedList(char mot_trad1[],char Mot_Eng[],char IMG[],char motfr[], NodePointer *head2){
    
//pointer to a new node to be inserted into linked list
   NodePointer newNode = NULL;
//pointer to the previous node in the linked list
   NodePointer previous = NULL;
//pointer to the current node in the linked list
   NodePointer current = *head2;

//create a node on the heap
   newNode = malloc(sizeof(Node));
/*
check to see if space is available
if no space on heap, malloc() will return NULL
*/
   if(NULL != newNode){
   //copy over word to the node
    strcpy(newNode->motfrance, motfr);
    strcpy(newNode->mot_ang , Mot_Eng);
    strcpy(newNode->mot_a_chercher , mot_trad1);
    strcpy(newNode->IMG_path, IMG);

   //figure out where to insert in linked list
      while(NULL != current && strcmp(motfr, current->motfrance)>0){
      //move previous to current
         previous = current;
      //move current to next node
         current = current->next;
      }//end of while
      //insert at beginning of linked list
      if(NULL == previous){
         newNode->next = current;
         //change the address stored in head
         *head2 = newNode; 
      }//end of if
      else{
      //insert between previous and current
         previous->next = newNode;
         newNode->next = current;
      }//end of else
   }//end of if
}//end of function


//displays the linked list
void displayLinkedList(NodePointer current){
   //for empty list
   if(NULL == current){
      printf("The linked list is empty!\n\n");
      return;
   }
   printf("\nlinked list items: ");
   //loop through list
   while(NULL != current){
   //display each node
      printf("%s, ", current->motfrance);
      printf("%s, ",current->mot_ang);
      printf("%s, ", current->mot_a_chercher);
      printf("%s --", current->IMG_path);
      //go to next node
      current = current->next;
   }
   printf("\n\n");
}//end of function

void destroyList(NodePointer* head) {
    NodePointer current = *head;
    NodePointer next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    *head = NULL;
}