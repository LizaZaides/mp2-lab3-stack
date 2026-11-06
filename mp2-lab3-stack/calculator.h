#pragma once
#include <string>
#include "container.h"
#include "Token.h"
#include <cctype>
#include <cstdlib>

using std::string;


class Calculator
{
    string infix, postfix;
    Container<Token> inf_cont, post_cont;
    void infix_to_cont()
    {
        inf_cont.clear();
        int i = 0;
        Token t;
        while (i < infix.size())
        {
            if (infix[i] == '(')
            {
                Token t;
                t.type = OpenBr;
                t.str = "(";
                inf_cont.push_back(t);
            }
            if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == '.')
            {
                char* p;
                double val = strtod(&infix[i], &p);
                t.val = val;
                t.type = Number;
                int delta = p - &infix[i];
                t.str = infix.substr(i, delta);
                inf_cont.push_back(t);
                i += delta-1;
            }
            if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/') {
                t.type = Operat;
                t.str = infix[i];
                inf_cont.push_back(t);
            }
            i++;
        }
    }
public:
    Calculator()
    {
        infix = "";
        postfix = "";
        inf_cont.clear();
        post_cont.clear();
    }

    
};