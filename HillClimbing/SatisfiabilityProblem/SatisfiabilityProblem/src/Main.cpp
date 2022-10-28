#include <iostream>
#include<HillClimbCnf.h>
#include<fstream>
#define size 10
#define limit 300
bool binaryVariables[10];

bool Eval() {
	return binaryVariables[0] || !binaryVariables[0];
}

bool RecursiveSolver(int index);
bool IterativeSolver(int number);
bool BinaryExpresionRecursiveSolver(int index, BinaryExpresion& exp);
bool BinaryExpresionIterativeSolver(int number, BinaryExpresion& exp);
void print(Dictionary<bool>* dict, int n);
int main() {
	/*int n;
	std::cin >> n;
	bool result=RecursiveSolver(n-1);
	bool result2 = IterativeSolver(n);
	std::cout << result<<std::endl<<result2;*/
	int n;
	std::string s;
	std::ifstream fInput("Input.txt");
	fInput >> n >> s;
	s += "$";
	
	HillCLimbCnf exp(s,n);
	int lastScore=exp.GetScore();
	if (lastScore==exp.maxScore) {
		print(exp.dict,n);
		std::cout << "score :" <<lastScore << "/" << exp.maxScore;
		return 0;
	}
	for (int i = 0; i < limit;i++) {
		int j = 0;
		while (j < n) {
			exp.dict->Set(j,!exp.dict->Get(j));
			int currentScore=exp.GetScore();
			if (currentScore == exp.maxScore) {
				std::cout << "problem satisfied!\n sequence is : \n";
				print(exp.dict, n);
				std::cout << "score :" << currentScore << "/" << exp.maxScore;
				return 0;
			}
			if (currentScore >= lastScore) {
				lastScore = currentScore;
				break;
			}
			exp.dict->Set(j, !exp.dict->Get(j));
			j++;
			if (j == n) {
				std::cout << "No progress Available \n";
				print(exp.dict, n);
				std::cout << "score :" << lastScore << "/" << exp.maxScore;
				return 0;
			}
		}
	}
	std::cout << "limit reached \n last state : \n";
	print(exp.dict, n);
	std::cout << "score :" << lastScore << "/" << exp.maxScore;

	/*BinaryExpresion Exp(s, n);
	std::cout << BinaryExpresionRecursiveSolver(n-1, Exp) << std::endl;
	std::cout << BinaryExpresionIterativeSolver(n, Exp) << std::endl;*/
}


void print(Dictionary<bool>* dict,int n) {
	for (int i = 0; i < n;i++) {
		std::cout << dict->GetKey(i) << " : " << dict->Get(i)<<" ";
	}
	std::cout << std::endl;
}


bool RecursiveSolver(int index) {
	binaryVariables[index] = false;
	if (index == 0) {
		if (Eval())
			return true;
		binaryVariables[index] = true;
		if (Eval())
			return true;
		return false;
	}
	bool result= RecursiveSolver(index-1);
	if (result)
		return true;
	binaryVariables[index] = true;
	result = RecursiveSolver(index-1);
	if (result)
		return true;
	return false;
}

bool BinaryExpresionRecursiveSolver(int index,BinaryExpresion& exp) {
	exp.dict->Set(index, false);
	if (index == 0) {
		if (exp.Evaluate())
			return true;
		exp.dict->Set(index,true);
		if (exp.Evaluate())
			return true;
		return false;
	}
	bool result = BinaryExpresionRecursiveSolver(index - 1,exp);
	if (result)
		return true;
	exp.dict->Set(index , true);
	result = BinaryExpresionRecursiveSolver(index - 1,exp);
	if (result)
		return true;
	return false;
}

bool IterativeSolver(int number) {
	//initialize data
	for (int i = 0; i < number;i++) {
		binaryVariables[i] = false;
	}
	while (true) {
		if (Eval())
			return true;
		int i = 0;
		while (binaryVariables[i]) {
			binaryVariables[i] = false;
			i++;
			if (i >= number)
				return false;
		}
		binaryVariables[i] = true;
	}
	return false;
}
bool BinaryExpresionIterativeSolver(int number,BinaryExpresion& exp) {
	//initialize data
	for (int i = 0; i < number; i++) {
		exp.dict->Set(i, false);
	}
	while (true) {
		if (exp.Evaluate())
			return true;
		int i = 0;
		while (exp.dict->Get(i)) {
			exp.dict->Set(i, false);
			i++;
			if (i >= number)
				return false;
		}
		exp.dict->Set(i, true);
	}
	return false;
}