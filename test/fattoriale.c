#include <stdio.h>


int main ()
{
    int res ;
    int n ;

    n = 7 ;
    res = 1 ;

    while (n>1) {
        res = res * n;
        n = n - 1 ;
        printf("n = %d \n",n );
        printf("risultato = %d \n",res );

    }
    printf("%d\n", res) ;

//    system ("pause") ;
}

//@ ( main )
