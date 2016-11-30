#ifndef GCode_H
#define GCode_H

#include "Token.h"

#define isCharacter(x)      (((x) >= 'a' && (x) <= 'z') || ((x) >= 'A' && (x) <= 'z'))
#define isDigit(x)          ((x) >= '0' && (x) <= '9')
#define isSpace(x)          ((x) == ' ' || (x) == '\t')

typedef int (*GcodeFunction)(char *str);

extern GcodeFunction gcodeTable[];

Token *tokenCreate(TokenType type, char *str, int length);
Token *getToken(char **strPtr);
int tokenConvertToNumber(Token *token);
int tokenGetNumbers(char **strPtr, int *arrInt, int length);
int tokenGetNumber(char **strPtr);

int gcodeInterpret(char *str);

#endif // GCode_H
