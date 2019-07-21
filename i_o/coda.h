/*  P1G94 854723 873888    */
#ifndef CODA
#define CODA
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../err.h"

typedef enum{assembly,machinecode_label,machinecode,not_def} typecoda;

struct word
{
    char *word;
    int row;
    struct word *next;
};
typedef struct word word;
typedef struct word *pword;

struct coda
{
    pword head;
    pword tail;
    typecoda tipo;
    size_t lengt;
};
typedef struct coda coda;
typedef coda *pcoda;
/*controllo se la coda è vuota*/
int isempty(pcoda pc);
/*ritorno una coda vuota*/
pcoda getempty();
/*inserisci in coda*/
int append(pcoda pc, char *s, int riga);
/*estrai in testa*/
char *extract(pcoda pc,int *riga);
/*Funzione utile a ritornare il numero della riga di una string (utile anche per ritornare l'indice dell array di istruzioni usando label)*/
int get_row(pcoda pc,char *s);
/*controllo se un elemento è presente*/
int ispresent(pcoda pc, char *s);
/*Pulizia della coda, effettuando tutte le free*/
void clear(pcoda *pc);
/*Questa funzione serve a spostare all'inizio della coda una funzione (cercata tramite il suo label)  ( utile nel assembla per avere la certezza di trovare come prima istruzione un istruzione del main)*/
int movetotop(pcoda pc,char *s1,char *s2);
/*Funzione utile durante il debug*/
void stampa(pcoda pc);
#endif
