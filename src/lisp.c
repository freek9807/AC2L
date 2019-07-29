#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void LISP_operando_node(operando_node* node);

void LISP_termine_node(termine_node* node){
  if(node->unary_sign == '-')  {
      printf(" ( -" );
      LISP_operando_node(node->op);
      printf(" )" );
      return;
    }

  LISP_operando_node(node->op);
}

void LISP_exp_node(exp_node* node);

void LISP_operando_node(operando_node* node){
  switch (node->type) {

    case TERM_NUMBER:
      printf(" %d", node->num );
    break;

    case TERM_VARIABLE:
    
    break;
    case TERM_EXP:
      LISP_exp_node(node->exp);
    break;
  }
}

void LISP_switch_op(EXP_Type val){
  switch (val) {
    case OP_PLUS:
    printf(" +");
    break;

    case OP_MINUS:
    printf(" -");
    break;

    case OP_MULT:
    printf(" *");
    break;

    case OP_DIV:
    printf(" /");
    break;

    case OP_MOD:
    printf(" %s", "%" );
    break;

    case OP_GREATER:
    printf(" >");
    break;

    case OP_LESS:
    printf(" <");
    break;

    case OP_AND:
    printf(" logand");
    break;

    case OP_OR:
    printf(" logor");
    break;

    case OP_ANDL:
    printf(" and");
    break;

    case OP_ORL:
    printf(" or");
    break;

    case OP_GREATER_EQ:
    printf("%s", " >=");
    break;

    case OP_LESS_EQ:
    printf("%s", " <=");
    break;

    case OP_NOTEQ:
    printf("%s", " /=");
    break;

    case OP_EQ:
    printf("%s", " =");
    break;
  }
}

void LISP_exp_node(exp_node* node){
  switch (node->type) {

    case OP_NUMERIC:
      LISP_termine_node(node->term);
    break;

    case OP_TERNARY:
      printf(" (if ");
      LISP_exp_node(node->term1);
      LISP_exp_node(node->term2);
      LISP_exp_node(node->term3);
      printf(" )" );
    break;

    case OP_NOT:
      printf(" ( not");
      LISP_exp_node(node->term1);
      printf(" )");
    break;

    default:
      printf(" (" );
      LISP_switch_op(node->type);
      LISP_exp_node(node->term1);
      LISP_exp_node(node->term2);
      printf(" )" );
    break;
  }
}

void LISP_args_node(args_node* args){
  if(args == NULL)
    return ;

  printf(" %s", args->var->id );
  LISP_args_node(args->next);
}

void LISP_func_node(func_node* node){
  printf("( defun %s", node->id );
  printf(" (" );
  LISP_args_node(node->args);
  printf(" )");
  printf(" (" );
  printf(" )");
  printf(" )\n" );
}

void LISP_array_node(array_node* node){
  if (node == NULL)
    return ;

  printf(" %d", node->dim );
  LISP_array_node(node->next);
}

void LISP_def_var_node(def_var_node* node){
  printf(" (defvar %s",node->var->id);
  switch (node->var->type) {
    case VAR_INT:
      if(node->assign == NULL)
        printf(" 0" );
      else
        LISP_exp_node(node->assign->exp);
    break;

    case VAR_ARRAY:
    printf("( make-array '(");
    LISP_array_node(node->var->array);
    printf(" ))");
    break;
  }
  printf(")\n");
}

void LISP_def_node(def_node* def){
  if(def == NULL)
    return;

  switch (def->type) {
    case DEF_FUNC:
      LISP_func_node(def->func);
      break;
    case DEF_VAR:
      LISP_def_var_node(def->def_var);
      break;
  }

  LISP_def_node(def->next);
}

void LISP_lisp_code_node(lisp_code_node* node){
  if(node == NULL)
    return;

  printf("%s\n", node->value);
  LISP_lisp_code_node(node->next);
}

void LISP_AST_node(AST_node*  node){
  LISP_def_node(node->def);
  LISP_lisp_code_node(node->lisp);
}
