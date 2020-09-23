#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define OPERAND 0
#define OPERATOR 1

#define OP_PLUS '+'
#define OP_SUB '-'
#define OP_MUL '*'
#define OP_DIV '/'

#define TRUE 1
#define FALSE 0

#define CHAR_LIMIT 100
#define STOP "exit"

#define NEW_LINE '\n'
#define STR_END '\0'

struct Token{
  int type;
  int value_i;
  char value_c;
};


char *remove_nl(char *input){
  char *cp_input = strdup(input);
  int len = strlen(cp_input);
  if (cp_input[len - 1] == NEW_LINE){
    cp_input[len - 1] = STR_END;
  }
  return cp_input;
}

char *read_expr(){
  char input[CHAR_LIMIT];
  printf("calc> ");
  fgets(input, CHAR_LIMIT, stdin);
  return remove_nl(input);
}

struct Token get_next_token(int pos, char *expr){
  struct Token token;
  char current_char;

  if (pos > strlen(expr)){
    token.type = EOF;
    token.value_c = STR_END;
    token.value_i = 0;
    return token;
  }

  current_char = expr[pos];

  if(isdigit(current_char)){
    token.type = OPERAND;
    token.value_i = atoi((char[]) {current_char, '\0'});
    token.value_c = current_char;
    return token;
  }

  token.type = OPERATOR;
  token.value_i = 0;
  token.value_c = current_char;

  return token;
}

void eval(char *expr){
  int pos = 0;
  int right, left;
  char operator;

  struct Token token = get_next_token(pos, expr);
  if (token.type == OPERAND){
    right = token.value_i;
  } else {
    printf("Invalid syntax\n");
    return;
  }

  token = get_next_token(++pos, expr);
  if(token.type == OPERATOR){
    operator = token.value_c;
  } else {
    printf("Invalid syntax\n");
    return;
  }

  token = get_next_token(++pos, expr);
  if(token.type == OPERAND){
    left = token.value_i;
  } else {
    printf("Invalid syntax\n");
    return;
  }

  switch(operator){
    case '+':
      printf("%d\n", right + left);
      break;
    case '-':
      printf("%d\n", right - left);
      break;
    case '*':
      printf("%d\n", right * left);
      break;
    case '/':
      printf("%d\n", right / left);
      break;
    default:
      printf("Invalid syntax\n");
      break;
  }

}

int main(int argc, char *argv[]){
  while(TRUE){
    char *expr = read_expr();
    if (strcmp(STOP, expr) == 0){
      return 0;
    }
    eval(expr);
  }
}
