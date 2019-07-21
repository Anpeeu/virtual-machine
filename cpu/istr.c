/*  P1G94 854723 873888    */
#include "istr.h"

void halt(){    
    return;
}

void display(int num_r1,int r1){
    printf("REG[%02d] : %d\n",num_r1,r1);
}

void print_stack(int *stack,unsigned int sp,int numero){
    int spi = (int) sp;
    int end = (--spi) -  numero +1;
    while ( spi >= 0 && spi >= end)
    {
        printf("%d - stack[%d]\n",stack[spi],spi);
        spi--;
    }
    printf("\n");
}

int push(int *stack,unsigned int *sp,int r1){
    /*da fare il controllo di sp< stack max size*/
    if ((*sp) + 1 <=  SIZE_STACK)
    {
        stack[*sp] = r1;
        (*sp)+=1;
        return 0;
    }
    else
        return STACK_FULL;   /* errore sp ha raggiunto il max*/
    
    
}

int pop(int *stack,unsigned int *sp,int *r1){
    if (((int)(*sp)) - 1 >= 0)
    {
        *sp -=1;
        *r1 = stack[*sp];
        return 0;
    }
    else
    {
        return STACK_EMPTY;   /* errore sp ha raggiunto il minimo*/
    }
    
   
}

void mov(int *r1,int numero){
    *r1 = numero; 
}

int call(int *stack,unsigned int *sp,unsigned int *ip,int dim,int index){
    if (!push(stack,sp,(*ip)+2)){
        return istr_jump(JMP,stack,sp,ip,dim,index);;
    }else
        return STACK_EMPTY; /* errore sp ha raggiunto il max*/
    
}
int ret(int *stack,unsigned int *sp,unsigned int *ip, int dim){
    int res;
    int err;
    err = pop(stack,sp,&res);
    if (!err)
    {
        if (res >= 0 && res < dim){
            *ip = res;
            return NO_PROBLEM;
        }
        else 
            return JUMP_NOT_VALID; /* valore di ritorno non valido*/
    }
    
    return res;
}
int istr_jump(int type,int *stack,unsigned int *sp,unsigned int *ip,int dim,int index){
    int err = 0;
    int res;
    /*printf("%d %d %d\n",index, *ip, dim);*/
    switch (type)
    {
    case JMP:
        if (index >= 0 && index < dim)
        {
            *ip = index;
            /*printf("%d\n",*ip);*/
        }
        else
        {
            err = JUMP_NOT_VALID; /* valore di ritorno non valido*/
        }
        break;
    case JZ:
        err = pop(stack,sp,&res);
        if (res == 0)
        {
            if (index >= 0 && index < dim)
            {
                *ip = index;
                /*printf("%d\n",*ip);*/
            }
            else
            {
                err = JUMP_NOT_VALID; /* valore di ritorno non valido*/
            }
        }
        else
        {
            (*ip) += 2;
        }
        break;
    case JPOS:
        err = pop(stack,sp,&res);
        if (res > 0)
        {
            if (index >= 0 && index < dim)
            {
                *ip = index;
                /*printf("%d\n",*ip);*/
            }
            else
            {
                err = JUMP_NOT_VALID; /* valore di ritorno non valido*/
            }
        }
        else
        {
            (*ip) += 2;
        }
        break;
    case JNEG:
        err = pop(stack,sp,&res);
        /*printf("foca %d %d\n",res,index);*/
        if (res < 0)
        {
            if (index >= 0 && index < dim)
            {
                *ip = index;
            }
            else
            {
                err = JUMP_NOT_VALID; /* valore di ritorno non valido*/
            }
        }
        else
        {
            (*ip) += 2;
        }
        break;
    default:
        err = INSTRUCTION_NOT_RECOGNIZED; /*istruzione non riconosciuta*/
        break;
    }
    return err;
}
int istr_aritm(int type,int *stack,unsigned int *sp,int r1,int r2){
    int err = NO_PROBLEM;
    long res = 0;
    long overflow=0; 
    int assoluto;

    switch (type)
    {
    case ADD:
        res =((long)r1)+(r2);
        overflow = !(res >= -__INT32_MAX__-1 && res<= __INT32_MAX__);
        break;
    case SUB:
        res =((long)r1)-(r2);
        overflow = !(res >= -__INT32_MAX__-1 && res<= __INT32_MAX__);
        break;
    case MUL:
        res = r1;
        assoluto = r2 * ((r2 >= 0)? 1 : -1);
        while (assoluto > 1 && !overflow)
        {
            res += r1;
            overflow = !(res > -__INT32_MAX__-1 && res<= __INT32_MAX__);
            assoluto--;
        }
        res = res *  ((r2 != 0)? ((r2 >= 0)? 1 : -1) : 0);
        overflow = !(res > -__INT32_MAX__-1 && res<= __INT32_MAX__);
        break;
    case DIV:
        if (r2 != 0)
        {
            if (r1 == (-__INT32_MAX__-1) && r2 == -1 )
            {
                err = OVERFLOW_DETECTED;
            }
            else
            {
                res =((long)r1)/(r2);
            }
        }
        else
        {
            err = DIV_ZERO;
        }
        break;
    default:
        err = INSTRUCTION_NOT_RECOGNIZED; 
        break;
    }
    if (!err)
    {
        if (!overflow)
        {
            err = push(stack,sp,res);
        }
        else
        {
            err = OVERFLOW_DETECTED;
        }
    }
    return err;
    
}
