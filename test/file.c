int a = 5;

int prova(int a,int b){
int c = 2;
c += a  + b;
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
  a += c + 2;
  return c;
}

int sum(){
  int b = ++a;
  b += 2;
  prova(2,3);
}
//@ (write (prova 2 3))
//@  (write (sum ))
