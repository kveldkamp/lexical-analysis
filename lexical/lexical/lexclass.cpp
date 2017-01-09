#include "lexclass.h"




void Lexclass::getChar(){

	if ((nextChar = fin.get()) != EOF){
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;

	}

	else
		charClass = EOF;

}


void Lexclass::addChar(){

	if (lexLen <= 98){
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}

	else
		cout << "Error, lexeme is too long" << endl;
}



void Lexclass::getNonBlank(){
	while (isspace(nextChar))
		getChar();

}

int Lexclass::lex(){
	lexLen = 0;
	getNonBlank();
	switch (charClass){

	//parse identifiers
	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT)
		{
			addChar();
			getChar();
		}
		
		if (lexeme[0] == 'P' && lexeme[1] == 'R' && lexeme[2] == 'O' && lexeme[3] == 'G' &&
			lexeme[4] == 'R' && lexeme[5] == 'A' && lexeme[6] == 'M')
			nextToken = PROGRAM;

		else if (lexeme[0] == 'B' && lexeme[1] == 'E' && lexeme[2] == 'G' && lexeme[3] == 'I' &&
			lexeme[4] == 'N')
			nextToken = BEGIN;

		else if (lexeme[0] == 'E' && lexeme[1] == 'N' && lexeme[2] == 'D')
			nextToken = END;

		else if (lexeme[0] == 'I' && lexeme[1] == 'N' && lexeme[2] == 'T' && lexeme[3] == 'E' &&
			lexeme[4] == 'G' && lexeme[5] == 'E' && lexeme[6] == 'R')
			nextToken = INTEGER;
		
		else nextToken = IDENT;
		
		
		break;

	//parse digits

	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT){
			addChar();
			getChar();
		}
		nextToken = CONST;
		break;

	case UNKNOWN:
		lookup(nextChar);
		getChar();
		break;

	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;

	}

	//cout << "Next token is: " << nextToken << " Next Lexeme is: " << lexeme << endl;
	return nextToken;

}

int Lexclass::lookup(char ch){

	switch (ch){

	case '(':
		addChar();
		nextToken = LEFTPAREN;
		break;
	case ')':
		addChar();
		nextToken = RIGHTPAREN;
		break;
	case '+':
		addChar();
		nextToken = PLUS;
		break;
	case '-':
		addChar();
		if ((nextChar1 = fin.get()) == '>'){

			nextChar = '>';
			nextToken = DECLARE;
			addChar();
		}
		else{
			nextToken = MINUS;
		}
		break;
	case '*':
		addChar();
		nextToken = TIMES;
		break;
	case '/':
		addChar();
		nextToken = DIVIDE;
		break;

	case'<':
		addChar();
		if ((nextChar1 = fin.get()) == '='){
			nextChar = '=';
			nextToken = ASSIGN_OP;
			addChar();
		}
		else{
			nextToken = COMPARE;
		}
		break;
	case ';':
		addChar();
		nextToken = SEMICOLON;
		break;
	case'.':
		addChar();
		nextToken = PERIOD;
		break;
	case ',':
		addChar();
		nextToken = COMMA;
		break;
	default:
		addChar();
		nextToken = EOF;
		break;
	}
	return nextToken;

	}


void Lexclass::starter(){
	fin.open("test4.txt", ifstream::in);

	if (fin.is_open()){
		cout << "open!" << endl;
	}
	getChar();
	lex();
	program();

	fin.close();
}

void Lexclass::program(){
	

	if (nextToken == PROGRAM){
		lex();
		
	}
	else
		error(01, __LINE__);

	if (nextToken == IDENT || nextToken == CONST)
		lex();
	else
		error(02, __LINE__);

	if (nextToken == SEMICOLON){
		lex();
		declaration();
	}
		else{
			error(00,__LINE__);
			declaration();
		}
	
	
	body();
	//cout << "<exiting program>" << endl;
}

void Lexclass::declaration(){
	

	if (nextToken == INTEGER){
		
		lex();
	
	}
	else{
		error(11, __LINE__);
		lex();
	}
	if (nextToken == DECLARE){
		
		idList();
	}
			
	else{
		error(10, __LINE__);
			idList();
		}
	
	
	

	if (nextToken == SEMICOLON)
		lex();
	else{
		error(12, __LINE__);
		
	}
	//cout << "<exiting declaration>" << endl;
}

void Lexclass::idList(){
	cout << "INT ";
	lex();
	cout << lexeme << endl;

	while (nextToken == IDENT || nextToken == CONST){
		
		lex();
		
		if (nextToken == COMMA){
			cout << "INT ";
			lex();
			cout << lexeme << endl;
		}
		else if(nextToken == IDENT || nextToken == CONST){
			error(20, __LINE__);
			
		}
	}

	//cout << "<exiting idList>" << endl;
}

void Lexclass::body(){
	
	if (nextToken == BEGIN){
		lex();
		statList();
	}
	else{
		error(30, __LINE__);
		lex();
		statList();
	}

	if (nextToken == END){
		lex();
		if (nextToken == PERIOD)
			fin.close();
		else{
			error(32, __LINE__);
			fin.close();
		}
	}
	else{
		error(31, __LINE__);
		fin.close();
	}

	//cout << "<exiting body>" << endl;
}

void Lexclass::statList(){

	statement();
	
	while (nextToken == SEMICOLON){
		cout << "POP ";
		cout << templexeme << endl;
		lex();
		statement();
		
	}

	//cout << "<exiting statList>" << endl;
}

void Lexclass::statement(){
	for (int i = 0; i < 100; i++){
		templexeme[i] = lexeme[i];
	}
	//cout << lexeme << endl;
	lex();
	//cout << lexeme << endl;

		
	if (nextToken != END)
	{

		if (nextToken == ASSIGN_OP){
			
			
			lex();
			
			expr();
		}
		else{
			error(50, __LINE__);
			lex();
			expr();
			
		}
	}

	

		
	
	
	//cout << "<exiting statement>" << endl;
}


void Lexclass::expr(){

	term();

	while (nextToken == PLUS || nextToken == MINUS){
		if (nextToken == PLUS){
			
			lex();
			
			term();
			cout << "ADD " << endl;
		}
		else if (nextToken == MINUS){
			
			lex();
			
			term();
			cout << "SUB " << endl;
		}
	}

	//cout << "<exiting expr>" << endl;
}

void Lexclass::term(){
	

	factor();

	while (nextToken == TIMES || nextToken == DIVIDE){
		if (nextToken == TIMES){
			
			lex();
			
			term();
			cout << "MUL " << endl;
		}
		else if (nextToken == DIVIDE){
			
			lex();
			
			term();
			cout << "DIV " << endl;
		}
	}

	//cout << "<exiting term>" << endl;
	
}

void Lexclass::factor(){
	

	if (nextToken == IDENT || nextToken == CONST){
		cout << "PUSH ";
		cout << lexeme << endl;
		lex();
	}
	else {
		if (nextToken == LEFTPAREN){
			lex();
			expr();
			if (nextToken == RIGHTPAREN){
				lex();
			}

		else
			error(80, __LINE__);
		}
	}
	
	//cout << "<exiting factor>" << endl;
}

void Lexclass::error(int error, int linenum){
	switch (error){
	case 00:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, expected a semicolon"<<" at line: "<<linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 01:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, need to declare PROGRAM" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;

	case 02:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, give your programa a name" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;

	case 10:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Invalid declaration" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 11:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Expected 'INTEGER' keyword" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 12:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, missing semicolon after declaration" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 20:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Exptected a comma" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 30:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Didn't find a 'BEGIN'" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;
	case 31:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Didn't find 'END'" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;

	case 32:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Missing Period after 'END' " << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;

	case 50:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Didn't find an assignment operator at line" << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;

	case 51:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, Missing semicolon after statement at line" << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;



	case 80:
		cout << " " << endl;
		cout << "------------ERROR----------" << endl;
		cout << "Error, didn't find closing parenthesis" << " at line: " << linenum << endl;
		cout << "------------ERROR----------" << endl;
		cout << " " << endl;
		break;

	}
	}


