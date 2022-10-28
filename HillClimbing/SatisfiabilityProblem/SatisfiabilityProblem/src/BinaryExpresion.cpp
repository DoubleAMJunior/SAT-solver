#include<BinaryExpresion.h>

BinaryExpresion::BinaryExpresion(std::string exp,int n){
	dict = new Dictionary<bool>(n);
	Tokenizer tokenizer(exp);
	Token t;
	do {
		t = tokenizer.Next();
		expresion.push_back(t);
		if (t.type==Token::Variable) {
			dict->Set(t.value, false);
		}
	} while (t.type != Token::Eof);
	ownsDict = true;
}
BinaryExpresion::BinaryExpresion(std::vector<Token> exp,Dictionary<bool> *d) {
	expresion = exp;
	dict = d;
	ownsDict = false;
}
BinaryExpresion::~BinaryExpresion() {
	if(ownsDict)
		delete dict;
}
void operationCalculator(std::vector<Token>& opStack, bool& result, bool value) {
	Token op;
	do {
		op = opStack.back();
		opStack.pop_back();
		if (op.type == Token::Not) {
			value = !value;
		}
	} while (op.type == Token::Not && !opStack.empty());
	if (op.type == Token::And) {
		result = result && value;
	}
	else if (op.type == Token::Or) {
		result = result || value;
	}
	else {
		result = value;
	}
}

bool BinaryExpresion::Evaluate() {
	std::vector<Token> opStack;
	Token oprate;
	oprate.type = Token::Variable;
	bool result = false;
	std::vector<Token>::iterator it = expresion.begin();
	Token currentToken = *it;
	while (it != expresion.end() && currentToken.type != Token::Eof) {
		switch (currentToken.type) {
		case Token::Variable:
			if (opStack.empty()) {
				result = dict->Get(currentToken.value);
			}
			else {
				bool value = dict->Get(currentToken.value);
				operationCalculator(opStack, result, value);
			}
			break;
		case Token::And:
			opStack.push_back(currentToken);
			break;
		case Token::Or:
			opStack.push_back(currentToken);
			break;
		case Token::Not:
			opStack.push_back(currentToken);
			break;
		case Token::OpenP:
			std::vector<Token> subExpresion;
			it++;
			currentToken = *it;
			while (it!=expresion.end())
			{
				if (currentToken.type==Token::CloseP) {
					BinaryExpresion exp(subExpresion, dict);
					bool value= exp.Evaluate();
					operationCalculator(opStack,result,value);
					break;
				}
				else {
					subExpresion.push_back(currentToken);
				}
				it++;
				currentToken = *it;
			}
			break;
		}
		it++;
		if (it!=expresion.end()) {	
			currentToken = *it;
		}
	}
	return result;
}

Tokenizer::Tokenizer(std::string d) {
	data = d;
	pointer = 0;
}

Token Tokenizer::Next() {
	Token result;
	if (pointer >= data.length()) {
		result.type = Token::Eof;
		return result;
	}
	char ct = data[pointer];
	pointer++;
	if (ct=='(') {
		result.value = ct;
		result.type = Token::OpenP;
		return result;
	}
	if (ct==')') {
		result.value = ct;
		result.type = Token::CloseP;
		return result;
	}
	if (ct=='+') {
		result.value = ct;
		result.type = Token::Or;
		return result;
	}
	if (ct=='*') {
		result.value = ct;
		result.type = Token::And;
		return result;
	}
	if (ct=='!') {
		result.value = ct;
		result.type = Token::Not;
		return result;
	}
	if (ct == '$' || ct == ' ' || ct == '\n' || ct == '\r') {
		result.value = ct;
		result.type = Token::Eof;
		return result;
	}
	do {
		result.value += ct;
		ct = data[pointer];
		if (ct != '(' && ct != ')'
			&& ct != '+' && ct != '*'
			&& ct != '!' &&
			ct != '$' && ct != ' ' && ct != '\n' && ct != '\r') {
			pointer++;
		}
		else {
			break;
		}
	} while (pointer >= data.length());
	result.type = Token::Variable;
	return result;
}