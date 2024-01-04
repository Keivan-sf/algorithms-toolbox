#ifndef infix_parser
#define infix_parser

#include <bits/stdc++.h>
#include <string>
using namespace std;

struct In {
    struct InOrChar {
        In* in = NULL;
        char c = '\0';
    };
    InOrChar first;
    char o;
    InOrChar second;
};

string infixToPrefix(string infix);
string infixToPostfix(string infix);

#endif
