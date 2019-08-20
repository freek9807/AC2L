int prova(int a,int b){
int c = 2;
int array [3] = {1,2,3};
c += a  + b;
do {
  printf("%d \n", a );
}while( a++ < 7);

if(a > 2){
  a = 2;
}
else{
  if( c > 6 )
  {
    a += 8;
    c += 8;
  }
  a +=  3;
}
  a += ++c + 2;
//  scanf("%d",c );
  printf("%d \n", array[0] );
  return c;
}

int sum(){
  int b = 5;
  b += prova(2,3);
}
//@ (write (prova 2 3))
//@ (write (sum))
