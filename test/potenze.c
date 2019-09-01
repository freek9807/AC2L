#include <stdio.h>

int potencias [100] ;
int m ;

int main()
{
    int i ;

    m = 30 ;

    i = 1 ;
    potencias [0] = 1 ;
    while (i < m) {
        potencias [i] = potencias [i-1] * 2 ;
        i = i + 1 ;
    }

    i = 1 ;
    printf("\n");
    while (i < m) {
        printf ("Potencia de 2 a la %d : %d  \n",i, potencias [i]) ;
        i = i + 1 ;
    }
}

//@ ( main)
