// Macro che alloca dinamicamente la memoria
#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))
// Macro che definiscono i nodi def
#define generate_func_def_node(f,n) generate_def_node(DEF_FUNC,f,NULL,n)
#define generate_def_var_def_node(v,n)  generate_def_node(DEF_VAR,NULL,v,n)
// Macro che definiscono i nodi espressione
#define generate_num_exp_node(term) generate_new_exp_node(OP_NUMERIC,term,NULL,NULL,NULL)
#define generate_ternary_exp_node(term1,term2,term3) generate_new_exp_node(OP_TERNARY,NULL,term1,term2,term3)
#define generate_not_exp_node(term1) generate_new_exp_node(OP_NOT,NULL,term1,NULL,NULL)
#define generate_exp_node(type,term1,term2) generate_new_exp_node(type,NULL,term1,term2,NULL)
// Macro che definiscono i nodi operando
#define generate_num_operando_node(n) generate_operando_node(TERM_NUMBER,n,NULL,NULL,NULL,NULL)
#define generate_exp_operando_node(e) generate_operando_node(TERM_EXP,0,e,NULL,NULL,NULL)
#define generate_var_operando_node(v) generate_operando_node(TERM_VARIABLE,0,NULL,v,NULL,NULL)
#define generate_func_operando_node(f) generate_operando_node(TERM_FUNCALL,0,NULL,NULL,f,NULL)
#define generate_pp_operando_node(pp) generate_operando_node(TERM_PP,0,NULL,NULL,NULL,pp)
// Macro che definiscono i nodi assegnamento
#define generate_exp_assign_node(e) generate_assign_node(ASS_VAR,e,NULL)
#define generate_array_assign_node(a) generate_assign_node(ASS_ARRAY,NULL,a)
// Macro che definiscono i nodi dell'inizializzazione di un array
#define generate_ls_exp_array(e) generate_array_content_node(NULL,e)
#define generate_ls_matrix_array(c) generate_array_content_node(c,NULL)
// Macro che definisce la costruzione di un nodo assegnamento ridotto
#define generate_reduce_def_assign(o,v,e) generate_def_assign_node(v,generate_exp_assign_node(generate_exp_node(o,generate_num_exp_node(generate_termine_node('+' , generate_var_operando_node(v))),e)))
// Macro che definiscono la costruzione di un blocco
#define generate_def_block_node(d,n) generate_block_node(BLOCK_DEF,d,n)
#define generate_assign_block_node(a,n) generate_block_node(BLOCK_ASSIGN,a,n)
#define generate_assign_ext_block_node(v,a,n) generate_block_node(BLOCK_ASSIGN,generate_def_assign_node(v,a),n)
#define generate_if_block_node(i,n) generate_block_node(BLOCK_IF,i,n)
#define generate_pre_post_block_node(e,n) generate_block_node(BLOCK_PP,e,n)
#define generate_funcall_block_node(f,n)  generate_block_node(BLOCK_FUNCALL,f,n)
#define generate_loop_block_node(l,n) generate_block_node(BLOCK_LOOP,l,n)
#define generate_return_block_node(e,n) generate_block_node(BLOCK_RETURN,generate_return_node(e),n)
#define generate_input_block_node(i,n) generate_block_node(BLOCK_INPUT,i,n)
#define generate_output_block_node(o,n) generate_block_node(BLOCK_OUTPUT,o,n)
// Macro che definiscono la costruzione di un ciclo
#define generate_while_node(e,b) generate_loop_node(LOOP_WHILE,USELESS,e,b,NULL,NULL,NULL,NULL,NULL)
#define generate_do_while_node(e,b) generate_loop_node(LOOP_DO_WHILE,USELESS,e,b,NULL,NULL,NULL,NULL,NULL)
#define generate_for_var_assign(d,e,v,a,b) generate_loop_node(LOOP_FOR,FOR_N,e,b,d,v,NULL,a,NULL)
#define generate_for_awo(d,e,a,b) generate_loop_node(LOOP_FOR,FOR_AWO,e,b,d,NULL,a,NULL,NULL)
#define generate_for_pp(d,e,pp,b) generate_loop_node(LOOP_FOR,FOR_PP,e,b,d,NULL,NULL,NULL,pp)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

// Definizione dei tipi di variabile
typedef enum {
  VAR_INT,
  VAR_ARRAY
} VAR_TYPE;
// Definizione dei tipi di funzone
typedef enum  {
  FUNC_VOID,
  FUNC_INT
} FUNC_TYPE;
// Definizione dei tipi di definizione
typedef enum {
  DEF_FUNC,
  DEF_VAR
} DEF_TYPE;
// Definizione dei tipi di assegnamento
typedef enum {
  ASS_VAR,
  ASS_ARRAY
} ASS_TYPE;
// Defizione dei tipi di precedenza
typedef enum {
  PRE,
  POST
} PRIORITY_TYPE;
// Definzione del tipo di operazione pre/post
typedef enum {
  PLUS,
  MINUS
} OPERATION_TYPE;
// Definizione del tipo di ciclo
typedef enum {
  LOOP_FOR,
  LOOP_WHILE,
  LOOP_DO_WHILE
} LOOP_TYPE;
// Defizione del tipo di for
typedef enum {
  USELESS,
  FOR_N,
  FOR_AWO,
  FOR_PP
} FOR_TYPE;
//Tipo di operatore
typedef enum ExpType
{
  OP_PLUS,
  OP_MINUS,
  OP_MULT,
  OP_DIV,
  OP_MOD,
  OP_GREATER,
  OP_LESS,
  OP_AND,
  OP_OR,
  OP_ANDL,
  OP_ORL,
  OP_GREATER_EQ,
  OP_LESS_EQ,
  OP_NOTEQ,
  OP_EQ,
  OP_NOT,
  OP_TERNARY,
  OP_NUMERIC
} EXP_Type;
// Definzione del tipo di blocco
typedef enum {
  BLOCK_DEF,
  BLOCK_ASSIGN,
  BLOCK_IF,
  BLOCK_PP,
  BLOCK_FUNCALL,
  BLOCK_LOOP,
  BLOCK_RETURN,
  BLOCK_INPUT,
  BLOCK_OUTPUT
} BLOCK_TYPE;
// Tipo di termine
typedef enum TermineType
{
  TERM_NUMBER,
  TERM_EXP,
  TERM_FUNCALL,
  TERM_VARIABLE,
  TERM_PP
} TERM_TYPE;
// Defizione delle funzioni con priorità
typedef struct exp exp_node;
typedef struct assign assign_node;
typedef struct funcall funcall_node;
typedef struct pre_post_inc pre_post_inc_node;
typedef struct as_ar_list as_ar_list_node;
typedef struct if_block if_node;
// Defizione nodo array o matrice
typedef struct array{
  exp_node* dim;
  struct array* next;
} array_node;
// Definzione variabile
typedef struct var{
  char* id;
  array_node* array;
  VAR_TYPE type;
} var_node;
// Definzione della struttura del nodo variabile
typedef struct def_var{
  var_node* var;
  assign_node* assign;
} def_var_node;
// Definzione della struttura del nodo variabile
typedef struct def_assign{
  var_node* var;
  assign_node* assign;
} def_assign_node;
// Definzione di una lista di argomenti di funzione
typedef struct args{
  var_node* var;
  struct args* next;
} args_node;
typedef struct block block_node;
//Definizione del nodo funzione
typedef struct func{
  char* id;
  FUNC_TYPE type;
  args_node* args;
  block_node* block;
} func_node;
// Definzione del nodo definizione
typedef struct def{
  DEF_TYPE type;
  func_node* func;
  def_var_node* def_var;
  struct def* next;
} def_node;
// Definzione del nodo con embedded code lisp
typedef struct lisp_code {
  char* value;
  struct lisp_code* next;
} lisp_code_node;
// Definzione nodo principale
typedef struct principale{
  def_node* def;
  lisp_code_node* lisp;
} AST_node;
// Nodo che definisce un operatore
typedef struct operando{
  int num;
  exp_node* exp;
  TERM_TYPE type;
  var_node* var;
  funcall_node* func;
  pre_post_inc_node* pp;
} operando_node;
// Nodo che definisce un termine
typedef struct termine{
  char unary_sign;
  operando_node* op;
} termine_node;
//Nodo que definisce una espressione
typedef struct exp{
  EXP_Type type;
  termine_node* term;
  struct exp* term1;
  struct exp* term2;
  struct exp* term3;
} exp_node;
// Definzione di una lista di espressioni
typedef struct list_exp{
  exp_node* exp;
  struct list_exp* next;
} list_exp_node;
// Definzione dell'inizializzazione di un array
typedef struct array_content{
  list_exp_node* ls;
  as_ar_list_node* content;
} array_content_node;
// Nodo con il valore di un assegnamento
typedef struct assign{
  ASS_TYPE type;
  exp_node* exp;
  array_content_node* array;
} assign_node;
// Definzione del contenuto di una matrice
typedef struct as_ar_list{
  array_content_node* node;
  struct as_ar_list* next;
} as_ar_list_node;
// Definzione di una chiamata a Funzione
typedef struct funcall{
  char* id;
  list_exp_node* ls_exp;
} funcall_node;
// Definzione di un operatore di pre/post incremento
typedef struct pre_post_inc{
  PRIORITY_TYPE p_type;
  char sign;
  var_node* var;
} pre_post_inc_node;
// Definzione di un blocco
typedef struct block{
  BLOCK_TYPE type;
  void* node;
  struct block* next;
} block_node;
// Defizione di un nodo else
typedef struct else_block{
  block_node* block;
} else_node;
// Defizione di un nodo if
typedef struct if_block{
  exp_node* exp;
  block_node* block;
  else_node* else_n;
} if_node;
// Defizione di un nodo loop
typedef struct loop{
  LOOP_TYPE type;
  FOR_TYPE for_type;
  exp_node* exp;
  block_node* block;
  def_var_node* def;
  var_node* var;
  def_assign_node* ass;
  assign_node* a;
  pre_post_inc_node* pp;
} loop_node;
// Defizione di un nodo return
typedef struct return_g{
  exp_node* exp;
} return_node;
// Definzione di una lista di variabili
typedef struct var_list{
  var_node* var;
  struct var_list* next;
} var_list_node;
// Defizione di un input
typedef struct scan{
  var_list_node* ls;
} input_node;
// Definzione di un output
typedef struct print{
  char* string;
  list_exp_node* exp_ls;
} output_node;
// Funzione che restituisce un nodo di tipo array
array_node* generate_array_node(exp_node* exp, array_node* next){
  array_node* node = ALLOC(array_node,1);

  node->dim = exp;
  node->next = next;

  return node;
}
// Funzione che restituisce un nodo con del code embedded di lisp
lisp_code_node* generate_lisp_code_node(char* string,lisp_code_node* next){
  lisp_code_node* lisp = ALLOC(lisp_code_node,1);

  lisp->value = strdup(string);
  lisp->next = next;

  return lisp;
}
// Funzione che restituisce un nodo con definizione di variabile
def_var_node* generate_def_var_node(var_node* var,assign_node* assign){

  def_var_node* def_var = ALLOC(def_var_node,1);

  def_var->var = var;
  def_var->assign = assign;

  return def_var;

}
// Funzione che restituisce un nodo con definizione di variabile
def_assign_node* generate_def_assign_node(var_node* var,assign_node* assign){

  def_assign_node* def_assign = ALLOC(def_assign_node,1);

  def_assign->var = var;
  def_assign->assign = assign;

  return def_assign;

}
// Funzione che restituisce un nodo di funzione
func_node* generate_func_node(FUNC_TYPE type,char* id,block_node* block,args_node* args){

  func_node* func = ALLOC(func_node,1);

  func->id = strdup(id);
  func->type = type;
  func->block = block;
  func->args = args;

  return func;
}
// Funzione che restituisce una definzione di funzione oppure array (Dipende dalla macro)
def_node* generate_def_node(DEF_TYPE type,func_node* func ,def_var_node* def_var,def_node* next){
  def_node* def = ALLOC(def_node,1);

  def->type = type;
  def->func = func;
  def->def_var = def_var;
  def->next = next;

  return def;
}
// Funzione che genera un nodo ti tipo variabile
var_node* generate_var_node(char* id, array_node* array){
  var_node* node = ALLOC(var_node,1);

  node->id = id;
  if(array == NULL)
    node->type = VAR_INT;
  else
    node->type = VAR_ARRAY;
  node->array = array;

  return node;
}
// Funzione che genera AST
AST_node* generate_ast_node(def_node* def,lisp_code_node* lisp){
  AST_node* node = ALLOC(AST_node,1);

  node->def = def;
  node->lisp = lisp;

  return node;
}
// Genera un nuovo nodo di argomenti di funzione
args_node* generate_args_node(var_node* var,args_node* next){
  args_node* node = ALLOC(args_node,1);

  node->var = var;
  node->next = next;

  return node;
}
// Genera un nuovo nodo exp vuoto
exp_node* generate_new_exp_node(EXP_Type type,termine_node* term,exp_node* term1,exp_node* term2,exp_node* term3){
  exp_node* exp = ALLOC(exp_node,1);

  exp->term = term;
  exp->term1 = term1;
  exp->term2 = term2;
  exp->term3 = term3;
  exp->type = type;

  return exp;
}
// Genera un nodo con un assegnamento
assign_node* generate_assign_node(ASS_TYPE type,exp_node* exp,array_content_node* content){
  assign_node* node = ALLOC(assign_node,1);

  node->type = type;
  node->exp = exp;
  node->array = content;

  return node;
}
// Genera un nodo operando
operando_node* generate_operando_node(TERM_TYPE type,int num,exp_node* exp,var_node* var,funcall_node* func,pre_post_inc_node* pp){
  operando_node* node = ALLOC(operando_node,1);

  node->type = type;
  node->num = num;
  node->exp = exp;
  node->var = var;
  node->func = func;
  node->pp = pp;

  return node;
}
// Genera un nodo termine
termine_node* generate_termine_node(char c,operando_node* op){
  termine_node* node = ALLOC(termine_node,1);

  node->unary_sign = c;
  node->op = op;

  return node;
}
// Genera una lista di espressioni
list_exp_node* generate_list_exp_node(exp_node* exp, list_exp_node* next ){
    list_exp_node* node = ALLOC(list_exp_node,1);

    node->exp = exp;
    node->next = next;

    return node;
}
// Genera una dichiarazione di matrici
array_content_node* generate_array_content_node(as_ar_list_node* content , list_exp_node* ls){
  array_content_node* node = ALLOC(array_content_node,1);

  node->ls = ls;
  node->content = content;

  return node;
}
// Genera un assegnamento di array
as_ar_list_node* generate_as_ar_list_node(array_content_node* node,as_ar_list_node* next){
  as_ar_list_node* val = ALLOC(as_ar_list_node,1);

  val->node = node;
  val->next = next;

  return val;
}
// Genera una chiamata a funzione
funcall_node* generate_funcall_node(char* id,list_exp_node* ls){
  funcall_node* node = ALLOC(funcall_node,1);

  node->id = strdup(id);
  node->ls_exp = ls;

  return node;
}
// Genera un nodo di pre/post incremento
pre_post_inc_node* generate_pre_post_inc_node(PRIORITY_TYPE p_type,char sign,var_node* var){
  pre_post_inc_node* node = ALLOC(pre_post_inc_node,1);

  node->p_type = p_type;
  node->sign = sign;
  node->var = var;

  return node;
}
// Genera un nodo blocco
block_node* generate_block_node(BLOCK_TYPE type,void* p, block_node* next){
  block_node* node = ALLOC(block_node,1);

  node->type = type;
  node->node = p;
  node->next = next;
  return node;
}
// Genera un nodo else
else_node* generate_else_node(block_node* block){
  else_node* node = ALLOC(else_node,1);

  node->block = block;

  return node;
}
// Genera un nodo if
if_node* generate_if_node(exp_node* exp,block_node* block,else_node* else_n){
  if_node* node = ALLOC(if_node,1);

  node->exp = exp;
  node->block = block;
  node->else_n = else_n;

  return node;
}
// Genera un nodo loop
loop_node* generate_loop_node(LOOP_TYPE type,FOR_TYPE for_type,exp_node* exp,block_node* block,def_var_node* def,var_node* var,def_assign_node* ass,assign_node* a,pre_post_inc_node* pp){
  loop_node* node = ALLOC(loop_node,1);

  node->type = type;
  node->for_type = for_type;
  node->exp = exp;
  node->block = block;
  node->def = def;
  node->ass = ass;
  node->var = var;
  node->a = a;
  node->pp = pp;

  return node;
}
// Genera un nodo return
return_node* generate_return_node(exp_node* exp){
  return_node* node = ALLOC(return_node,1);

  node->exp = exp;

  return node;
}
// Genera una lista di variabili
var_list_node* generate_var_list(var_node* var,var_list_node* next){
  var_list_node* node = ALLOC(var_list_node,1);

  node->var = var;
  node->next = next;

  return node;
}
// Genera un nodo input
input_node* generate_input_node(var_list_node* ls){
  input_node* node = ALLOC(input_node,1);

  node->ls = ls;

  return node;
}
// Genera un nodo output
output_node* generate_output_node(char* string,list_exp_node* ls){
  output_node* node = ALLOC(output_node,1);

  node->string = strdup(string);
  node->exp_ls = ls;

  return node;
}
