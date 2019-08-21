#include <stdio.h>

void pascaltriangle(int n)
{
  int c;
  printf("\n");
  for(int i=0; i < n; i++) {
    c = 1;
    for(int j=1; j <= 2*(n-1-i); j++){
      printf(" ");
    }
    for(int k=0; k <= i; k++) {
      printf("%d ", c);
      c = c * (i-k)/(k+1);
    }
    printf("\n");
  }
}

int main()
{
  pascaltriangle(8);
  return 0;
}

//@ (main)
