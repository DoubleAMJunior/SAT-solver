#include <iostream>
#include<BinaryExpresion.h>
#include<fstream>
#define size 10;
bool binaryVariables[10];

bool Eval() {
	return binaryVariables[0] || !binaryVariables[0];
}

bool RecursiveSolver(int index);
bool IterativeSolver(int number);
bool BinaryExpresionRecursiveSolver(int index, BinaryExpresion& exp);
bool BinaryExpresionIterativeSolver(int number, BinaryExpresion& exp);

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
	BinaryExpresion Exp(s, n);
	std::cout << BinaryExpresionRecursiveSolver(n-1, Exp) << std::endl;
	std::cout << BinaryExpresionIterativeSolver(n, Exp) << std::endl;
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