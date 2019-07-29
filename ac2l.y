%{

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "src/ast.c"
#include "src/lisp.c"

int yylex();
int yyerror (char* mensaje);

%}
%union {
      int value ;
      char *string;
      lisp_code_node* emb;
      def_var_node* variable;
      var_node* var;
      func_node* func;
      def_node* def;
      array_node* array;
      args_node* args;
      assign_node* assign;
      exp_node* exp;
      termine_node* term;
      operando_node* op;
      AST_node* ast;
}

%token <value> NUMBER
%token <string> IDENTIF
%token <string> INTEGER VOID
%token <string> LISP_STRING STRING
%token <string> DO WHILE IF THEN ELSE PRINT PUTS RETURN FOR
%token <string> INC DEC PLUSONE MINUSONE MULTONE DIVONE
%token <string> ANDL ORL GREATER_EQ LESS_EQ EQ NOTEQ
%right '=' '?' ':'
%left ANDL ORL
%left '&' '|'
%left EQ NOTEQ
%left GREATER_EQ LESS_EQ '>' '<'
%left '+' '-'
%left '*' '/' '%'
%left SEGNO_UNARIO  '!'
%left  INC DEC
%type <variable> def_var
%type <func> func
%type <def> def
%type <emb> lisp_code
%type <ast> principale
%type <array> array
%type <var> var
%type <args> arg args
%type <exp> exp
%type <term> termine
%type <op> operando
%type <assign> assign
%%

principale  :   def lisp_code { $$ = generate_ast_node($1,$2); LISP_AST_node($$); }
             ;

def          :         func def { $$ = generate_func_def_node($1,$2); }
             | def_var def { $$ = generate_def_var_def_node($1,$2); }
             |  /* lambda */  { $$ = NULL; }
             ;

def_var      :     INTEGER var assign ';'	{ $$ = generate_def_var_node($2,$3); }
             ;

var          :     IDENTIF array  { $$ = generate_var_node($1,$2); }
            ;

array       :       '[' NUMBER ']' array { $$ = generate_array_node($2,$4); }
            | /* lambda */        { $$ = NULL; }
             ;

assign       : '=' exp     { $$ = generate_assign_node($2); }
            | /* lambda */ { $$ = NULL; }
             ;
func         :          INTEGER IDENTIF '(' arg ')' '{' '}' { $$ = generate_func_node(FUNC_INT,$2,$4); }
              |         VOID IDENTIF '(' arg ')' '{' '}' { $$ = generate_func_node(FUNC_VOID,$2,$4); }
             ;

arg          :          INTEGER var args { $$ = generate_args_node($2,$3); }
              |         /* lambda */ { $$ = NULL; }
             ;

args         :        ',' arg { $$ = $2 ; }
              | /* lambda */ { $$ = NULL; }
             ;

exp          :     termine				{ $$ = generate_num_exp_node($1);  }
             | exp  '+' exp		{ $$ = generate_exp_node(OP_PLUS,$1,$3); }
             | exp  '-' exp		{ $$ = generate_exp_node(OP_MINUS,$1,$3); }
             | exp  '*' exp		{ $$ = generate_exp_node(OP_MULT,$1,$3); }
             | exp  '/' exp		{ $$ = generate_exp_node(OP_DIV,$1,$3); }
             | exp  '%' exp   { $$ = generate_exp_node(OP_MOD,$1,$3); }
             | exp  '&' exp   { $$ = generate_exp_node(OP_AND,$1,$3); }
             | exp  '|' exp   { $$ = generate_exp_node(OP_OR,$1,$3); }
             | exp  '>' exp   { $$ = generate_exp_node(OP_GREATER,$1,$3); }
             | exp  '<' exp   { $$ = generate_exp_node(OP_LESS,$1,$3); }
             | exp  ANDL exp   { $$ = generate_exp_node(OP_ANDL,$1,$3); }
             | exp  ORL exp   { $$ = generate_exp_node(OP_ORL,$1,$3); }
             | exp  GREATER_EQ exp   { $$ = generate_exp_node(OP_GREATER_EQ,$1,$3); }
             | exp  LESS_EQ exp   { $$ = generate_exp_node(OP_LESS_EQ,$1,$3); }
             | exp  EQ exp   { $$ = generate_exp_node(OP_EQ,$1,$3); }
             | exp  NOTEQ exp   { $$ = generate_exp_node(OP_NOTEQ,$1,$3); }
             | exp '?' exp ':' exp { $$ = generate_ternary_exp_node($1 , $3, $5); }
             | '!' exp   { $$ = generate_not_exp_node($2); }
             ;

termine      :       operando				{ $$ = generate_termine_node('+' , $1); }
             | '+' operando %prec SEGNO_UNARIO	{ $$ = generate_termine_node('+' , $2); }
             | '-' operando %prec SEGNO_UNARIO	{ $$ = generate_termine_node('-' , $2); }
             ;

operando     :      NUMBER 			        { $$ = generate_num_operando_node($1); }
             | '(' exp ')'		{ $$ = generate_exp_operando_node($2); }
             |  var           { $$ = generate_var_operando_node($1); }
             ;

lisp_code    :     /* lambda */      { $$ = NULL; }
             | LISP_STRING lisp_code {  $$ = generate_lisp_code_node($1,$2); }
             ;
%%
