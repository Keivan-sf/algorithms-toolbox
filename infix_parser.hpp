#include <bits/stdc++.h>
#include <string>
using namespace std;

class InfixParser {
private:
    struct In {
        struct InOrChar {
            In* in = NULL;
            char c = '\0';
        };
        InOrChar first;
        char o;
        InOrChar second;
    };
public:
    In::InOrChar parsed;
    string infix;
    InfixParser(string i);
    string toPrefix();
    string toPostfix();
};
