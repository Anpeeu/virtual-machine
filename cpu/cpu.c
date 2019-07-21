/*  P1G94 854723 873888    */
#include "cpu.h"


/* 
    variabile che definisce lo stack
    definisco il puntatore allo stack come variabile globale
*/
static int *stack;
static int *reg;

static unsigned int ip;
static unsigned int sp;

/*
    Creo lo stack in base alla grandezza che mi è stata data
    return
        - 1 problema riscontrato con malloc
        - 0 nessun problema con la malloc 
*/
int initialize(){
    free_cpu();

    stack = (int *) malloc(SIZE_STACK * sizeof(int));
    reg = (int *) malloc(sizeof(int) * NUM_REGISTER);

    if (!stack || !reg)
        free_cpu();

    return (stack == NULL || reg == NULL);
}
/*
    Pulisco i puntatori allo stack e all'array dei registri
*/
void free_cpu(){
    if(stack){
        free(stack);
        stack = NULL;
    }if(reg){
        free(reg);
        reg = NULL;
    }
}

/*----------------------------------------------------------------------------------------------*/

/* Funzione per controllare se l'indice di un registro è dentro i limite dell'array di registri*/
int check_reg(int r1)
{
    return (r1 >= 0 && r1 < NUM_REGISTER);
}

int execute(int *instr_arr,unsigned int dim,int inizio){    
    int i;
    
    int err = 0;
    ip = inizio;
    sp = 0;

    /*inizializzo la cpu*/
    if (initialize())
    {
        err = MALLOC_FAILURE_CPU;
    }
    else
    {
        /* azzero i registri ?*/    
        for ( i = 0; i < NUM_REGISTER; i++)
        {
            reg[i]= 0;
        }
        
        while (!err && ip < dim )
        {

            switch (instr_arr[ip])
            {
            case HALT:
                halt();
                ip = dim;
                break;
            case DISPLAY:
                if ( check_reg(instr_arr[ip+1]))
                    display(instr_arr[ip+1],reg[instr_arr[ip+1]]);
                else
                    err = REGISTRER_UNKNOWN;
                ip+=2;
                break;
            case PRINT_STACK:
                print_stack(stack,sp,instr_arr[ip+1]);
                ip+=2;
                break;
            case PUSH:
                if ( check_reg(instr_arr[ip+1]))
                    err = push(stack,&sp,reg[instr_arr[ip+1]]);
                else
                    err = REGISTRER_UNKNOWN;
                ip+=2;
                break;
            case POP:
                if ( check_reg(instr_arr[ip+1]))
                    err = pop(stack,&sp,&reg[instr_arr[ip+1]]);
                else
                    err = REGISTRER_UNKNOWN;
                ip+=2;
                break;
            case MOV:
                if ( check_reg(instr_arr[ip+1]))
                    mov(&reg[instr_arr[ip+1]],instr_arr[ip+2]);
                else
                    err = REGISTRER_UNKNOWN;
                ip+=3;
                break;
            case CALL:
                err =  call(stack,&sp,&ip,dim,instr_arr[ip+1]);
                break;
            case RET:
                err = ret(stack,&sp,&ip,dim);
                break;
            case JMP:
            case JZ:
            case JPOS:
            case JNEG:
                err = istr_jump(instr_arr[ip],stack,&sp,&ip,dim,instr_arr[ip+1]);
                break;
            case ADD:
            case SUB:
            case MUL:
            case DIV: 
                if ( check_reg(instr_arr[ip+1]) && check_reg(instr_arr[ip+2]))
                {
                    err = istr_aritm(instr_arr[ip],stack,&sp,reg[instr_arr[ip+1]],reg[instr_arr[ip+2]]);
                }
                else
                {
                    err = REGISTRER_UNKNOWN;
                }
                ip+=3;
                break;
            default:
                err = INSTRUCTION_NOT_RECOGNIZED; /*istruzione non riconosciuta*/
                break;
            }
        }
    }
    if (err)
    {
        print_err(err,-1,NULL);
    }
    free_cpu();
    return err;
}

