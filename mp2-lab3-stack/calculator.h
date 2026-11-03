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
        while (i < infix.size)
        {
            if (infix[i] == '(')
            {
                Token t;
                t.type = OperBr;
                s.str = "(";
                inf_cont.pus_hback(t);
            }
            if (infix[i] >= '0' && infix[i] <= '9' && infix[i] == '.')
            {
                char* p;
                double val = strtod(&infix[i], &p);
                Token t;
                t.val = val;
                t.type = Number;
                t.str =//подстрока
                    inf_cont.push_back(t);
                int dalta = p - &infix[i];
                i += delta;
            }
        }
        i++;
    }
public:
    Calculator()
    {
        infix = "";
        postfix = "";
        inf_count.clear();
        post_count.clear();
    }

    
};