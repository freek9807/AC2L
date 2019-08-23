#include<stdio.h>

int primo(int n){
  int i = 3;

  if(n < 2){
    return 0;
  }
  if(n == 2){
    return 1;
  }
  if(n % 2 == 0){
    return 0;
  }

  while( i < n){
    if(n % i == 0){
      return 0;
    }
    i++;
  }
  return 1;
}

int main(){
  int i = 1;
  printf("\n");
  do{
    if(primo(i) == 1){
      printf(" %d -",i );
    }
    else{
      printf(" / -");
    }
  } while( ++i <= 100);
  printf("\n");
}
//@ (main)
