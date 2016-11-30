#ifndef GCode_H
#define GCode_H

#include "Token.h"

#define isCharacter(x)      (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'z'))
#define isDigit(x)          ((x) >= '0' && (x) <= '9')
#define isSpace(x)          ((x) == ' ' || (x) == '\t')

Token *tokenCreate(TokenType type, char *str, int length);
Token *getToken(char **strPtr);
int tokenConvertToNumber(Token *token);
int tokenGetNumbers(char **strPtr, int *arrInt, int length);

#endif // GCode_H
