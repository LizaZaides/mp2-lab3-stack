#pragma once
#include <string>

enum TokenType
{
	Number,
	Operat,
	OpenBr,
	CloseBr,
	Function,
	Variable
};

struct Token
{
	enum TokenType t_type; 
	std::string str;
	double val;
	int priority;

	Token(enum TokenType t = Number, std::string s = "", double v = 0.0, int p = 0)
		: t_type(t), str(s), val(v), priority(p) {
	}
};