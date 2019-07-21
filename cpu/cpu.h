/*  P1G94 854723 873888    */
#ifndef CPU
#define CPU

#include "istr.h"
#include <stdlib.h>
#include <stdio.h>
#include "../err.h"

#define SIZE_STACK 16384                          /* 64K Byte*/ 
#define NUM_REGISTER 32

/*funzioni per inizializzare o chiudere lo stack*/
int initialize();
void free_cpu();                                 /*void close();*/

/*scorro la lista di istruzioni*/
/*mi serve la lista di istruzioni*/
int execute(int *instr_arr,unsigned int dim,int inizio);
#endif
