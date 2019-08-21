int factorial(int n){
	int retorno;
	if(n==1){
		retorno = 1;
	}else{
		retorno = n*factorial(n-1);
	}

        printf ("%d %d\n", n, retorno) ;

	return retorno;
}

int main ()
{
	int resultado;
	printf("\n" );
	resultado = factorial(7);
  printf("%d\n", resultado);
}

//@ (main)
