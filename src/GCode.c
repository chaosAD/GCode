#include <stdio.h>
#include <malloc.h>
#include "GCode.h"
#include "Token.h"

#define tokenGet  getToken

int gcodeReadMemory(char *str);
int gcodeWriteMemory(char *str);

GcodeFunction gcodeTable[100] = {
  [97] = gcodeReadMemory,
  [98] = gcodeWriteMemory,
};

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
    while(isDigit(*str)) {
      str++;
    }
    c = *str;
    if(!isSpace(c) && c != 0) {
      // Todo: should throw and error
      // ...
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
    printf("Error: the token is not an identifier\n");
    return -1;
  }
}

int tokenGetNumbers(char **strPtr, int *arrInt, int length) {
  Token *t;

  while(length--) {
    t = tokenGet(strPtr);
    if(t->type == NUMBER_TOKEN) {
      *(arrInt++) = tokenConvertToNumber(t);
      free(t);
    }
  }
  return 0;
}

int tokenGetNumber(char **strPtr) {
  Token *t;
  int value;
  t = tokenGet(strPtr);
  value = tokenConvertToNumber(t);
  free(t);
  return value;
}

int isNumberTokenGood(Token *token) {
  int i = 0;
  char *str;
  if(token->type == NUMBER_TOKEN) {
    str = token->str;
    while(isDigit(*(str))) {
      str++;
      i++;
    }
    return 1;
  } else {
    // Todo: Throw and error if Token is not of IDENTIFIER TYPE
    // ...
    printf("Error: the token is not an identifier\n");
    return -1;
  }
}

int gcodeGetCode(Token *token) {
  token->type = NUMBER_TOKEN;
  token->length--;
  token->str++;
  if(!isNumberTokenGood(token)) {
    // Todo: Throw if not good
    return -1;
  }
  return tokenConvertToNumber(token);
}

int gcodeInterpret(char *str) {
  Token *token = getToken(&str);
  char c = *(token->str);
  if(token->type == IDENTIFIER_TOKEN && (c == 'g' || c == 'G')) {
    gcodeTable[gcodeGetCode(token)](str);
  }
}

/**
 * G97
 */
int gcodeReadMemory(char *str) {
  int data[2];
  tokenGetNumbers(&str, data, 2);

  printf("Read %d bytes from memory address %d\n", data[1], data[0]);
}

/**
 * G98
 */
int gcodeWriteMemory(char *str) {
  int data[2];
  tokenGetNumbers(&str, data, 2);

  printf("Write to memory @ address %d the following %d bytes:\n", data[0], data[1]);
  while(data[1]--)
    printf("%d ", tokenGetNumber(&str));
  putchar('\n');
}