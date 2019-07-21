/*  P1G94 854723 873888    */
#ifndef ISTR
#define ISTR
#include "../err.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
/*
    Define di tutte le istruzioni possibili
----------------------------------------------------------------------------------------
*/

/*Fine programma*/
#define HALT 0
/*stampa registro*/
#define DISPLAY 1
/*Stampa n posizioni dello stack*/
#define PRINT_STACK 2
/*Inserisce un valore nello stack*/
#define PUSH 10
/*Estrae un valore dallo stack*/
#define POP 11
/*Carica un intero in un registro*/
#define MOV 12
/*Chiamata a funzione*/
#define CALL 20
/*Faccio una pop e salto al valore estratto*/
#define RET 21
/*Salto ad un indice*/
#define JMP 22
/*Faccio una pop e controllo se il valore estratto è uguale a 0*/
#define JZ 23
/*Faccio una pop e controllo se il valore estratto è minore di 0*/
#define JPOS 24
/*Faccio una pop e controllo se il valore estratto è maggiore di 0*/
#define JNEG 25
/*Sommo i valori di 2 registri ( push del risultato )*/
#define ADD 30
/*Sottraggo i valori di 2 registri ( push del risultato )*/
#define SUB 31
/*Moltiplico i valori di 2 registri ( push del risultato )*/
#define MUL 32
/*Divido i valori di 2 registri ( push del risultato )*/
#define DIV 33




/* termino il programma */
void halt();
/* stampo in stdout un registro*/
void display(int num_reg,int r1);
/* stampo lo stack in stdout da sp-1 a sp-n */
void print_stack(int *stack,unsigned int sp,int numero);
/* Inserisce il contenuto del registro indicato nello stack (in posizione SP) ed incrementa SP */
int push(int *stack,unsigned int *sp,int r1);
/* Estrae l'ultima cella dello stack  */
int pop(int *stack,unsigned int *sp,int *r1);
/*Copia un int in un registro*/
void mov(int *r1,int numero);
/*Chiamata a funzione*/
int call(int *stack,unsigned int *sp,unsigned int *ip,int dim,int index);
/*Cambio di ip con l'ultimo elemento nello stack */
int ret(int *stack,unsigned int *sp,unsigned int *ip, int dim);
/*Effettuo un jump (dipende dal valore di type il tipo di jump)*/
int istr_jump(int type,int *stack,unsigned int *sp,unsigned int *ip,int dim,int index);
/*Eseguo un operazione algebrica*/
int istr_aritm(int type,int *stack,unsigned int *sp,int r1,int r2);



#endif
