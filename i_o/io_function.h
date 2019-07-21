/*  P1G94 854723 873888    */
#ifndef IOFUN
#define IOFUN


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../cpu/istr.h"
#include "coda.h"
#include "./../err.h"



/*legge un file e genera una pcoda (con un type in base al tipo del file che sto leggendo)*/
pcoda readfile(const char *filename,int *err);                       

/*data una lista (di codice assembly) ritornare una lista di codice macchina (se la pcoda passata è di machine code la funzione ritona il parametro passato in input)*/
pcoda assembly_to_machinecode(pcoda lista,int op, int*err);            

/*
    Data un pcoda, genero l'array di istruzioni, ovviamente a seconda del tipo di pcoda che ricevo in input ho differenti istruzioni da fare.
    La pcoda può essere di 2 tipi :
     - machinecode (se il file letto da readfile contiene dei numeri interi)
     - machinecode_label ( se il file letto da readfile contiene una parola, dopo readfile è neccesario far passare il file letto per assembly_to_machinecode)
*/
int * get_instruction_array(pcoda pc,int *dim,int *inizio,int * err);
/*Stampa su schermo l'array di istruzioni nel formato assembly*/
void machinecode_print(int *instr_arr,int dim,int * err);
/*dato un formato assembly genera un file di tipo cvm */
int print_ass_to_cvm(int *instr_arr,int dim,const char *output);




#endif
