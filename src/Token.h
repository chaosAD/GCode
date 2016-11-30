#ifndef Token_H
#define Token_H

typedef enum {
  UNKNOWN_TOKEN,
  IDENTIFIER_TOKEN,
  NUMBER_TOKEN,
} TokenType;

typedef struct Token Token;
struct Token {
  TokenType type;
  char *str;
  int length;  
};

#endif // Token_H
