%{
// Macro per allocare memoria
#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))
#define STR_SIZE(id) (strlen(id) + 1)
// Librerie incluse
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "ac2l.tab.c"
// Numero di linea corrente
int n_linea = 1 ;
// Funzione lexer
int yylex();
// Funzione parser
int yyparse();
%}
%%
[0-9]+          {
                  yylval.value = atoi(yytext);
                  return(NUMBER);
                }
"int"           { return(INTEGER); }
"while"         { return(WHILE); }
"if"            { return(IF); }
"else"          { return(ELSE); }
"do"            { return(DO); }
"for"           { return(FOR); }
"printf"        { return(PRINT); }
"scanf"         { return(SCAN); }
"puts"          { return(PUTS); }
"return"        { return(RETURN); }
"void"          { return(VOID); }
"++"            { return(INC); }
"--"            { return(DEC); }
"&&"            { return(ANDL); }
"||"            { return(ORL); }
">="            { return(GREATER_EQ); }
"<="            { return(LESS_EQ); }
"=="            { return(EQ); }
"!="            { return(NOTEQ); }
"+="            { return(PLUSVAL); }
"-="            { return(MINUSVAL); }
"*="            { return(MULTVAL); }
"/="            { return(DIVVAL); }
[ \t\v\f\r]		  { ; }
[\n]            { n_linea++; }
\#(.*)          { n_linea++; }
\/\/@(.*)       {
                  n_linea++;
                  yylval.string = ALLOC(char , STR_SIZE(yytext-3));
                  strncpy(yylval.string, &yytext[3], strlen(yytext));
                  return (LISP_STRING) ;
                }
\/\/(.*)        { n_linea++; }
\".*\"          {
                  n_linea++;
                  yylval.string = ALLOC(char , STR_SIZE(yytext-2));
                  strncpy(yylval.string, &yytext[1], strlen(yytext)-2);
                  return (STRING) ;
                }
[a-z][a-z0-9]*  {
                  yylval.string = strdup(yytext) ;
                  return (IDENTIF) ;
                }
<<EOF>>         { return -1; }
.               {
                  return yytext[0];
                }
%%

/* Funzione che stampa l'errore e la linea in cui si trova l'errore */
int yyerror (message)
char *message ;
{
    fprintf (stderr, "%s alla linea %d\n", message, n_linea) ;
    // Cpmando per la chiusura di CLisp
    printf ( "(quit)\n") ;
}

/* Main */
int main ()
{
    yyparse () ;
}
