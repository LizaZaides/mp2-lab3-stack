#pragma once
enum TokenType
{
	Number,
	Operat,
	OpenBr,
	CloseBr
};

struct Token
{
	TokenType type;
	string str;
	double val;
};