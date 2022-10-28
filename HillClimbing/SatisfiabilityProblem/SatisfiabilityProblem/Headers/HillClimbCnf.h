#pragma once
#include<BinaryExpresion.h>
class HillCLimbCnf {
private:
	BinaryExpresion** _expresions;
public:
	HillCLimbCnf(std::string exp,int n);
	Dictionary<bool> *dict;
	int GetScore();
	int maxScore;
};