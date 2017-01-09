#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <string>

using namespace std;

class Lexclass {
public:
 Lexclass(){
 };

 ifstream fin;

 /* Functions */
 void addChar();
 void getChar();
 void getNonBlank();
 int lex();
 int lookup(char ch);
 void program();
 void body();
 void declaration();
 void idList();
 void statList();
 void statement();
 void expr();
 void term();
 void factor();
 void starter();
 void error(int error,int linenum);

private:
 /* Variables */
 int charClass;
 char lexeme[100];
 char templexeme[100];
 char nextChar;
 char nextChar1;
 int lexLen;
 int token;
 int nextToken;





 /* Token codes */
#define LETTER 0
#define DIGIT 1
#define CONST 10
#define IDENT 11
#define ASSIGN_OP 20

#define SEMICOLON 21
#define RIGHTPAREN 22
#define LEFTPAREN 23
#define PERIOD 24
#define COMMA 25
#define MINUS 26
#define PLUS 27
#define TIMES 28
#define DIVIDE 29
#define DECLARE 30
#define PROGRAM 31
#define BEGIN 32
#define END 33
#define INTEGER 34
#define COMPARE 35
#define UNKNOWN 99



};