#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Container {
	int size;
	T* pMew;
public:
	Container(int _size = 10) {
		if (_size <= 0) throw "размер меньше 0";
		size = _size;
		pMew = new T[size];
	}

	~Container() {
		if (pMew != nullptr) {
			delete[] pMew;
		}
	}

	Container(const Container& c) : size(c.size) {
		pMew = new T[c.size];
		for (int i = 0; i < size; i++) {
			pMew[i] = c.pMew[i];
		}
	}

	Container(Container&& c) {
		size = c.size;
		pMew = c.pMew;
		c.size = 0;
		c.pMew = nullptr;
	}

	Container& operator=(const Container& c);
	Container& operator=(Container&& c) {
		if (this != &c) {
			size = c.size;
			delete[] pMew;
			pMew = c.pMew;
			c.pMew = nullptr;
			c.size = 0;
		}
		return *this;
	}
	T& operator[](int ind) {
		return pMew[ind];
	}
	Container& Size(int s) {
		if (s <= 0)
			throw "размер меньше или равен 0";
		if (size != s) {
			T* pNew = new T[s];
			int min = (size < s) ? size : s;
			for (int i = 0; i < min; i++) {
				pNew[i] = pMew[i];
			}
			delete[]pMew;
			pMew = pNew;
			pNew = nullptr;
			size = s;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const Container& v) {
		for (int i = 0; i < v.size; i++) out << v.pMew[i] << " ";
		return out;
	}
	friend istream& operator>>(istream& in, Container& v) {
		for (int i = 0; i < v.size; i++) in >> v.pMew[i];
		return in;
	}
};

template <typename T>
Container<T>& Container<T> :: operator=(const Container<T>& c) {
	if (this != &c) {
		if (size != c.size) {
			size = c.size;
			delete[] pMew;
			pMew = new T[size];
		}
		for (int i = 0; i < size; i++) {
			pMew[i] = c.pMew[i];
		}
	}
	return *this;
}




