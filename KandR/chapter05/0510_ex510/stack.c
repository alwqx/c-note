#include <stdio.h>

#include "calc.h"

static int sp = 0;
static double val[MAXVAL];

/* push: push f to stack */
void push(double f){
    if(sp<MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: return f from stack */
double pop(void){
    if(sp>0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}