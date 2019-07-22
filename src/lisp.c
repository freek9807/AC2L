#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* scope = NULL;

void LISP_args_node(args_node* args){
  if(args == NULL)
    return ;

  printf(" %s", args->id );
  LISP_args_node(args->next);
}

void LISP_func_node(func_node* node){
  scope = strdup(node->id);
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
      printf(" 0" );
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
