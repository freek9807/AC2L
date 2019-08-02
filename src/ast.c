#define ALLOC(t,n) (t *) malloc((n)*sizeof(t))
#define generate_func_def_node(f,n) generate_def_node(DEF_FUNC,f,NULL,n)
#define generate_def_var_def_node(v,n)  generate_def_node(DEF_VAR,NULL,v,n)
#define generate_num_exp_node(term) generate_new_exp_node(OP_NUMERIC,term,NULL,NULL,NULL)
#define generate_ternary_exp_node(term1,term2,term3) generate_new_exp_node(OP_TERNARY,NULL,term1,term2,term3)
#define generate_not_exp_node(term1) generate_new_exp_node(OP_NOT,NULL,term1,NULL,NULL)
#define generate_exp_node(type,term1,term2) generate_new_exp_node(type,NULL,term1,term2,NULL)
#define generate_num_operando_node(n) generate_operando_node(TERM_NUMBER,n,NULL,NULL,NULL)
#define generate_exp_operando_node(e) generate_operando_node(TERM_EXP,0,e,NULL,NULL)
#define generate_var_operando_node(v) generate_operando_node(TERM_VARIABLE,0,NULL,v,NULL)
#define generate_func_operando_node(f) generate_operando_node(TERM_FUNCALL,0,NULL,NULL,f)
#define generate_exp_assign_node(e) generate_assign_node(ASS_VAR,e,NULL)
#define generate_array_assign_node(a) generate_assign_node(ASS_ARRAY,NULL,a)
#define generate_ls_exp_array(e) generate_array_content_node(NULL,e)
#define generate_ls_matrix_array(c) generate_array_content_node(c,NULL)

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
// Tipo di termine
typedef enum TermineType
{
  TERM_NUMBER,
  TERM_EXP,
  TERM_FUNCALL,
  TERM_VARIABLE
} TERM_TYPE;
// Defizione nodo array o matrice
typedef struct array{
  int dim;
  struct array* next;
} array_node;
//
typedef struct assign assign_node;
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
// Definzione di una lista di argomenti di funzione
typedef struct args{
  var_node* var;
  struct args* next;
} args_node;
//Definizione del nodo funzione
typedef struct func{
  char* id;
  FUNC_TYPE type;
  args_node* args;
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
typedef struct exp exp_node;

typedef struct funcall funcall_node;
// Nodo che definisce un operatore
typedef struct operando{
  int num;
  exp_node* exp;
  TERM_TYPE type;
  var_node* var;
  funcall_node* func;
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

typedef struct list_exp{
  exp_node* exp;
  struct list_exp* next;
} list_exp_node;

typedef struct as_ar_list as_ar_list_node;

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

typedef struct as_ar_list{
  array_content_node* node;
  struct as_ar_list* next;
} as_ar_list_node;

typedef struct funcall{
  char* id;
  list_exp_node* ls_exp;
} funcall_node;
// Funzione che restituisce un nodo di tipo array
array_node* generate_array_node(int info, array_node* next){
  array_node* node = ALLOC(array_node,1);

  node->dim = info;
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
// Funzione che restituisce un nodo di funzione
func_node* generate_func_node(FUNC_TYPE type,char* id,args_node* args){

  func_node* func = ALLOC(func_node,1);

  func->id = strdup(id);
  func->type = type;
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
operando_node* generate_operando_node(TERM_TYPE type,int num,exp_node* exp,var_node* var,funcall_node* func){
  operando_node* node = ALLOC(operando_node,1);

  node->type = type;
  node->num = num;
  node->exp = exp;
  node->var = var;
  node->func = func;

  return node;
}
// Genera un nodo termine
termine_node* generate_termine_node(char c,operando_node* op){
  termine_node* node = ALLOC(termine_node,1);

  node->unary_sign = c;
  node->op = op;

  return node;
}

list_exp_node* generate_list_exp_node(exp_node* exp, list_exp_node* next ){
    list_exp_node* node = ALLOC(list_exp_node,1);

    node->exp = exp;
    node->next = next;

    return node;
}

array_content_node* generate_array_content_node(as_ar_list_node* content , list_exp_node* ls)
{
  array_content_node* node = ALLOC(array_content_node,1);

  node->ls = ls;
  node->content = content;

  return node;
}

as_ar_list_node* generate_as_ar_list_node(array_content_node* node,as_ar_list_node* next){
  as_ar_list_node* val = ALLOC(as_ar_list_node,1);

  val->node = node;
  val->next = next;

  return val;
}

funcall_node* generate_funcall_node(char* id,list_exp_node* ls){
  funcall_node* node = ALLOC(funcall_node,1);

  node->id = strdup(id);
  node->ls_exp = ls;

  return node;
}
