#include <malloc.h>
#include "unity.h"
#include "GCode.h"
#include "Token.h"

void setUp(void) {}

void tearDown(void) {}

void test_isCharacter() {
//  char *str = "abcdefg";
//  TEST_ASSERT_TRUE(isCharacter(*++str));
//  TEST_ASSERT_EQUAL_STRING("bcdefg", str);

  TEST_ASSERT_TRUE(isCharacter('a'));
  TEST_ASSERT_TRUE(isCharacter('f'));
  TEST_ASSERT_TRUE(isCharacter('z'));
  TEST_ASSERT_TRUE(isCharacter('A'));
  TEST_ASSERT_TRUE(isCharacter('Y'));
  TEST_ASSERT_TRUE(isCharacter('A'));
  TEST_ASSERT_FALSE(isCharacter('0'));
  TEST_ASSERT_FALSE(isCharacter('@'));
  TEST_ASSERT_FALSE(isCharacter('+'));
  TEST_ASSERT_FALSE(isCharacter(' '));
  TEST_ASSERT_FALSE(isCharacter('\t'));
}

void test_isDigit() {
  TEST_ASSERT_TRUE(isDigit('0'));
  TEST_ASSERT_TRUE(isDigit('6'));
  TEST_ASSERT_TRUE(isDigit('9'));
  TEST_ASSERT_FALSE(isDigit('A'));
  TEST_ASSERT_FALSE(isDigit('G'));
  TEST_ASSERT_FALSE(isDigit('Z'));
  TEST_ASSERT_FALSE(isDigit('a'));
  TEST_ASSERT_FALSE(isDigit('e'));
  TEST_ASSERT_FALSE(isDigit('z'));
  TEST_ASSERT_FALSE(isDigit('\n'));
  TEST_ASSERT_FALSE(isDigit('@'));
  TEST_ASSERT_FALSE(isDigit('+'));
  TEST_ASSERT_FALSE(isDigit(' '));
  TEST_ASSERT_FALSE(isDigit('\t'));
}

void test_getToken_given_g23_ballpark_should_return_identifier_token_with_g23() {
	Token *t;
  char *origStr = "  g123 ballpark", *str = origStr;

  t = getToken(&str);

  TEST_ASSERT_EQUAL(4, t->length);
  TEST_ASSERT_EQUAL_MEMORY("g123", t->str, t->length);
  TEST_ASSERT_EQUAL(IDENTIFIER_TOKEN, t->type);
  TEST_ASSERT_EQUAL_HEX8(' ', *str);
  free(t);
}

void test_getToken_given_987_should_return_identifier_token_with_987() {
	Token *t;
  char *origStr = "  98765", *str = origStr;

  t = getToken(&str);

  TEST_ASSERT_EQUAL(5, t->length);
  TEST_ASSERT_EQUAL_MEMORY("98765", t->str, t->length);
  TEST_ASSERT_EQUAL(NUMBER_TOKEN, t->type);
  TEST_ASSERT_EQUAL_HEX8(0, *str);
  free(t);
}

void test_getToken_given_456j_should_return_identifier_token_with_456() {
	Token *t;
  char *origStr = "  456j", *str = origStr;

  t = getToken(&str);

  TEST_ASSERT_EQUAL(3, t->length);
  TEST_ASSERT_EQUAL_MEMORY("456", t->str, t->length);
  TEST_ASSERT_EQUAL(NUMBER_TOKEN, t->type);
  TEST_ASSERT_EQUAL_HEX8('j', *str);
  free(t);
}

void test_tokenConvertToNumber_given_45735658_should_return_45735658() {
  char *str = "  45735658 ";
	Token *t = getToken(&str);
  int n;

  n = tokenConvertToNumber(t);

  TEST_ASSERT_EQUAL(45735658, n);
  free(t);
}

void test_tokenGetNumbers_given_123_456_9874_should_return_an_array_of_the_integers() {
  char *str = "  123 4567  \t 987401 ";
	int arrInt[3];

  tokenGetNumbers(&str, arrInt, 3);

  TEST_ASSERT_EQUAL(123, arrInt[0]);
  TEST_ASSERT_EQUAL(4567, arrInt[1]);
  TEST_ASSERT_EQUAL(987401, arrInt[2]);
}

void test_gcodeInterpret_given_G97_987654_20_should_call_g97_function() {
  char *str = " \t G97 987654  \t \t  20 ";

  gcodeInterpret(str);
}

void test_gcodeInterpret_given_G98_1234567890_4_23_245_0212_0067_should_call_g98_function() {
  char *str = "  G98 1234567890 4   23    245  0212 0067 ";

  gcodeInterpret(str);
}