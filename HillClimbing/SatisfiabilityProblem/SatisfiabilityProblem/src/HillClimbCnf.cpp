#include<HillClimbCnf.h>
#include<algorithm>
#include<string>
HillCLimbCnf::HillCLimbCnf(std::string exp,int n) {
	dict = new Dictionary<bool>(n);
	maxScore = std::count(exp.begin(), exp.end(), '(');
	_expresions = new BinaryExpresion*[maxScore];
	Tokenizer tokenizer(exp);
	Token t;
	int expCounter = 0;
	std::vector<Token> expresion;
	do {
		t = tokenizer.Next();
		if (t.type==Token::OpenP) {
			expresion.empty();
			continue;
		}
		if (t.type == Token::CloseP) {
			_expresions[expCounter] = new BinaryExpresion(expresion, dict);
			expCounter++;
			continue;
		}
		expresion.push_back(t);
		if (t.type == Token::Variable) {
			dict->Set(t.value, false);
		}
	} while (t.type != Token::Eof);
}
int HillCLimbCnf::GetScore() {
	int score = 0;
	for (int i = 0; i < maxScore; i++) {
		if (_expresions[i]->Evaluate()) {
			score++;
		}
	}
	return score;
}