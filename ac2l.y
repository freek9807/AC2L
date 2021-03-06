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
      array_content_node* content;
      args_node* args;
      assign_node* assign;
      exp_node* exp;
      termine_node* term;
      operando_node* op;
      list_exp_node* ls_exp;
      as_ar_list_node* ar_ls;
      funcall_node* funcall;
      block_node* block;
      if_node* if_n;
      else_node* else_n;
      def_assign_node* assign_block;
      pre_post_inc_node* pp;
      loop_node* loop;
      var_list_node* var_ls;
      input_node* input;
      output_node* output;
      AST_node* ast;
}

%token <value> NUMBER
%token <string> IDENTIF
%token <string> INTEGER VOID
%token <string> LISP_STRING STRING
%token <string> DO WHILE IF THEN ELSE PRINT SCAN PUTS RETURN FOR
%token <string> INC DEC PLUSVAL MINUSVAL MULTVAL DIVVAL
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
%type <content> assign_array array_content
%type <ls_exp> list_exp base_list_exp
%type <ar_ls> as_ar_list as_ar_support
%type <assign_block> assign_with_op
%type <funcall> funcall
%type <block> block
%type <if_n> if_block
%type <else_n> else_block
%type <pp> pre_post_inc
%type <loop> loop
%type <var_ls> var_list
%type <input> input
%type <output> output
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

array       :       '[' exp ']' array { $$ = generate_array_node($2,$4); }
            | /* lambda */        { $$ = NULL; }
             ;

assign       : '=' exp     { $$ = generate_exp_assign_node($2); }
            | '=' assign_array  { $$ = generate_array_assign_node($2); }
            | /* lambda */ { $$ = NULL; }
             ;

assign_with_op : var PLUSVAL exp  { $$ = generate_reduce_def_assign(OP_PLUS,$1,$3); }
                | var MULTVAL exp  { $$ = generate_reduce_def_assign(OP_MINUS,$1,$3); }
                | var MINUSVAL exp  { $$ = generate_reduce_def_assign(OP_MULT,$1,$3); }
                | var DIVVAL exp  { $$ = generate_reduce_def_assign(OP_DIV,$1,$3); }
                ;

block        : def_var block { $$ = generate_def_block_node($1,$2); }
             | assign_with_op ';' block { $$ = generate_assign_block_node($1,$3); }
             |   var assign ';' block { $$ = generate_assign_ext_block_node($1,$2,$4); }
             |   if_block block   { $$ = generate_if_block_node($1,$2); }
             |   pre_post_inc ';' block { $$ = generate_pre_post_block_node($1,$3); }
             |   funcall ';' block { $$ = generate_funcall_block_node($1,$3); }
             |   loop block { $$ = generate_loop_block_node($1,$2); }
             |   RETURN exp ';' block { $$ = generate_return_block_node($2,$4); }
             |   input ';' block      { $$ = generate_input_block_node($1,$3); }
             |   output ';' block     { $$ = generate_output_block_node($1,$3); }
             | /* lambda */   { $$ = NULL; }
             ;

output:      PRINT '(' STRING list_exp ')'{ $$ = generate_output_node($3,$4); }
             ;

input:       SCAN '(' STRING var_list ')' { $$ = generate_input_node($4); }
             ;

var_list     : ',' var var_list { $$ = generate_var_list($2,$3); }
             | /* lambda */           { $$ = NULL; }
             ;

loop         : WHILE '(' exp ')' '{' block '}' { $$ = generate_while_node($3,$6); }
              | DO '{' block '}' WHILE '(' exp ')' ';' { $$ = generate_do_while_node($7,$3); }
              | FOR '('def_var exp ';' var assign ')' '{' block '}' { $$ = generate_for_var_assign($3,$4,$6,$7,$10); }
              | FOR '('def_var exp ';' assign_with_op ')' '{' block '}' { $$ = generate_for_awo($3,$4,$6,$9); }
              | FOR '('def_var exp ';' pre_post_inc ')' '{' block '}' { $$ = generate_for_pp($3,$4,$6,$9); }
              ;

pre_post_inc : var INC  { $$ = generate_pre_post_inc_node(POST,'+',$1); }
              | var DEC { $$ = generate_pre_post_inc_node(POST,'-',$1); }
              | INC var { $$ = generate_pre_post_inc_node(PRE,'+',$2); }
              | DEC var { $$ = generate_pre_post_inc_node(PRE,'-',$2); }
              ;

if_block     : IF '(' exp ')' '{' block '}' else_block { $$ = generate_if_node($3,$6,$8); }
             ;

else_block   : ELSE '{' block '}' { $$ = generate_else_node($3); }
             | /* lambda */       { $$ = NULL; }
             ;

assign_array : '{' array_content '}' { $$ = $2;  }
             ;

array_content :   as_ar_list     { $$ = generate_ls_matrix_array($1); }
              |   base_list_exp  { $$ = generate_ls_exp_array($1); }
              ;

as_ar_list    :  assign_array as_ar_support { $$ = generate_as_ar_list_node($1,$2); }
              ;

as_ar_support : ',' assign_array as_ar_support { $$ = generate_as_ar_list_node($2,$3); }
              | /* lambda */ { $$ = NULL; }
              ;

base_list_exp:  exp list_exp { $$ = generate_list_exp_node($1,$2); }
              ;
list_exp      : ',' exp list_exp { $$ = generate_list_exp_node($2,$3); }
              | /* lambda */ { $$ = NULL; }
              ;

func         :          INTEGER IDENTIF '(' arg ')' '{' block '}' { $$ = generate_func_node(FUNC_INT,$2,$7,$4); }
             |         VOID IDENTIF '(' arg ')' '{' block '}' { $$ = generate_func_node(FUNC_VOID,$2,$7,$4); }
             ;

arg          :          INTEGER var args { $$ = generate_args_node($2,$3); }
              |         INTEGER '*' var args { $$ = generate_args_node($3,$4); }
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
             |  funcall       { $$ = generate_func_operando_node($1); }
             | pre_post_inc   { $$ = generate_pp_operando_node($1); }
             ;

funcall      : IDENTIF '(' base_list_exp ')' { $$ = generate_funcall_node($1,$3); }
             ;

lisp_code    :     /* lambda */      { $$ = NULL; }
             | LISP_STRING lisp_code {  $$ = generate_lisp_code_node($1,$2); }
             ;
%%
