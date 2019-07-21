/*  P1G94 854723 873888    */
#ifndef ERRFILE
#define ERRFILE
#include "./cpu/istr.h"

/*
    Define di tutti gli errori (CPU-ISTR)
*/
/*Codice eseguito senza errori*/
#define NO_PROBLEM 0
/*Stack è completamente pieno (push)*/
#define STACK_FULL 1
/*Stack è completamente vuoto (pop)*/
#define STACK_EMPTY 2
/*Valore di jump non valido*/
#define JUMP_NOT_VALID 3
/*overflow trovato (calcolo arimetico)*/
#define OVERFLOW_DETECTED 4
/*divisone per zero trovata*/
#define DIV_ZERO 5
/*indice registro errata*/
#define REGISTRER_UNKNOWN 6
/*Istruzione non riconosciuta*/
#define INSTRUCTION_NOT_RECOGNIZED 10

/*
    Define di tutti gli errori (I-O)
*/
/*parola non riconosciuta */
#define UNKOWN_WORD 101
/*grandezza dell'array errata*/
#define ARR_SIZE_INCORRECT 102
/*errore nell'apertura del file*/
#define CANT_OPEN_FILE 103              
/*file vuoto*/
#define EMPTY_FILE 104                  
/*main non trovato*/
#define MAIN_NOT_FOUND 105              
/*formato non riconosciuto*/
#define UNKNOWN_FORMAT 106              

/*
    Define degli errori nel main
*/
/* Parametri inseriti nel programma non riconosciuti*/
#define UNKOWN_PARAMETER 404
/* Numero di parametri inseriti nel programma non corretti */
#define WRONG_NUMBER_PARAMETER 405
/*impossibilita di salvare il file assemblato */
#define CANNOT_SAVE_CVM 500 

/*
    Define del fail della malloc
*/
/*malloc fallita */
#define MALLOC_FAILURE 1000
/*malloc fallita in cpu.c */
#define MALLOC_FAILURE_CPU 1001
/*malloc fallita in coda.c*/
#define MALLOC_FAILURE_CODA 1002
/*malloc fallita in instr_arr*/
#define MALLOC_FAILURE_INSTR_ARR 1003
/* malloc fallita in read_file */
#define MALLOC_FAILURE_READ_FILE 1004
/*malloc fallita in assembly_to_mac */
#define MALLOC_FAILURE_ASSEMBLY_TO_MAC 1005
/*malloc fallita in read_file */
#define MALLOC_FAILURE_READ_FILE 1004


/* stampa il codice d'errore e altre informazioni utili a correggerlo*/
void print_err(int err,int row,char *word);


#endif
