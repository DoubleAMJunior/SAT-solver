#pragma once
#include<map>
#include<vector>
#include<dictionary.h>
class Token {
public:
	enum TokenType {
		Variable, And, Or, OpenP, CloseP, Eof,Not
	};
	std::string value;
	TokenType type;
};
class Tokenizer {
private:
	std::string data;
	int pointer;
public:
	Tokenizer(std::string d);
	Token Next();
};

class BinaryExpresion {
private:
	std::vector<Token> expresion;
	bool ownsDict;
public:
	Dictionary<bool> *dict;
	BinaryExpresion(std::string exp,int n);
	BinaryExpresion(std::vector<Token> exp, Dictionary<bool> *d);
	~BinaryExpresion();
	bool Evaluate();
};


