#include <stdio.h>

int mimatriz [5][5] ;
int i ;
int j ;
int aux ;


int main () {
	printf("Matrice non inizializzata \n") ;
	i = 0 ;
	while (i < 5) {
		j = 0 ;
		while (j < 5) {
			printf ("%d ", mimatriz [i][j]) ;
			j = j + 1 ;
		}
		printf("\n" );
		i = i + 1 ;
	}

	i = 0 ;
	while (i < 5) {
		j = 0 ;
		while (j < 5) {
			mimatriz [i][j] = i + 2*j ;
			j = j + 1 ;
		}
		i = i + 1 ;
	}
	printf("\nMatrice inizializzata \n") ;
	i = 0 ;
	while (i < 5) {
		j = 0 ;
		while (j < 5) {
			printf ("%d ", mimatriz [i][j]) ;
			j = j + 1 ;
		}
		printf("\n" );

		i = i + 1 ;
	}
    i = 0 ;
    do {
       j = i+1 ;
       while (j < 5) {
           aux = mimatriz [i][j] ;
           mimatriz [i][j] = mimatriz [j][i] ;
           mimatriz [j][i] = aux ;
           j = j + 1 ;
       }
       i = i + 1 ;
    } while  (i < 5) ;

	printf ("\nMatrice trasposta \n") ;

	i = 0 ;
	while (i < 5) {
		j = 0 ;
		while (j < 5) {
			printf ("%d ", mimatriz [i][j]) ;
			j = j + 1 ;
		}
		printf("\n" );
		i = i + 1 ;
	}

//    system ("pause") ;
}

//@ (main)
