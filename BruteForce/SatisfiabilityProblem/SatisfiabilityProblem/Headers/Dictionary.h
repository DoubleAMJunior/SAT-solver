#pragma once
#include<iostream>
#include<string>
template <class T>
class Dictionary {
private:
	std::map<std::string, T*> dict;
	T* variable;
	int size;
public:
	Dictionary(int n);
	~Dictionary();
	T Get(std::string key);
	T Get(unsigned int index);
	void Set(std::string key, T value);
	void Set(unsigned int index, T value);
};

template <class T>
Dictionary<T>::Dictionary(int n) {
	variable = new T[n];
	size = 0;
}

template <class T>
Dictionary<T>::~Dictionary() {
	delete[]variable;
}

template <class T>
T Dictionary<T>::Get(std::string key) {
	T result;
	try {
		result = *(dict.at(key));
	}
	catch (...) {
		std::cerr << key + " does not exist in dictionary" << std::endl;
	}
	return result;
}
template <class T>
T Dictionary<T>::Get(unsigned int index) {
	if (size > index)
		return variable[index];
	std::cerr << "Out of bound dictionary " + index << std::endl;
	return false;
}
template <class T>
void  Dictionary<T>::Set(std::string key, T value) {
	if (dict.count(key)) {
		*dict[key] = value;
		return;
	}
	variable[size] = value;
	dict[key] = &variable[size];
	size++;
}
template <class T>
void Dictionary<T>::Set(unsigned int index, T value) {
	if (size > index)
		variable[index] = value;
}