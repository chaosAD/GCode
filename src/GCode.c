#include <stdio.h>
#include <malloc.h>
#include "GCode.h"
#include "Token.h"

Token *tokenCreate(TokenType type, char *str, int length) {
  Token *t = malloc(sizeof(Token));
  t->type = type;
  t->str = str;
  t->length = length;
  return t;
}

Token *getToken(char **strPtr) {
  int len = 0;
  Token *t;
  volatile k;
  char c, *startStr, *str = *strPtr;
  while(isSpace(*str)) str++;
  
  startStr = str;
  if(isCharacter(c = *str)) {
    c = *++str;
    while(isCharacter(c) || isDigit(c)) {
      c = *++str;
    }
    t = tokenCreate(IDENTIFIER_TOKEN, startStr, str - startStr);
  } else if(isDigit(c)) {
    str++;
    while(isDigit(*(str))) {
      str++;
    }
    c = *str;
    if(!isSpace(c) && c != (int)NULL) {
      // Todo: should throw and error
      printf("Error: a number is prefixed with some character: %c\n", c);
    }
    t = tokenCreate(NUMBER_TOKEN, startStr, str - startStr);
  } 
  *strPtr = str;  
  return t; 
}

int tokenConvertToNumber(Token *token) {
  if(token->type == NUMBER_TOKEN) {
    int integer = 0, len = token->length;
    while(len--) {
      integer *= 10;
      integer += *(token->str++) - '0';
    }
    return integer;
  } else {
    // Todo: Throw and error if Token is not of IDENTIFIER TYPE
    // ...
    return -1;
  }  
}
