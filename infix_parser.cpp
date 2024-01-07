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

bool exists(In::InOrChar a) {
    return a.in || a.c;
}

map<char, int> operators {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'^', 3},
};

int get_operator_value(char c) {
    auto result = operators.find(c);
    if(result != operators.end()) {
        /* cout << "going for " << c << " in operators " << operators[c] << endl; */
        return operators[c];
    } else {
        return 0;
    }
}

bool hasCorrectBrackets(const string &infix) {
    int bracketSum = 0;
    for (unsigned int idx = 0; idx < infix.length(); idx++) {
        if (infix[idx] == '(')
            ++bracketSum;
        if (infix[idx] == ')')
            --bracketSum;
        if(bracketSum < 0) {
            return false;
        }
    }
    return (bracketSum == 0);
}

bool hasNoPairedBrackets(const string &infix) {
    for (int idx = 0; idx < infix.length() - 1; idx++) {
        if(infix[idx] == ')' && infix[idx+1] == '(') {
            return false;
        }
        if(infix[idx] == '(' && infix[idx+1] == ')') {
            return false;
        }
    }
    return true;
}

bool hasNoPairedOperators(const string &infix) {
    for (int idx = 0; idx < infix.length() - 1; idx++) {
        if(get_operator_value(infix[idx]) && get_operator_value(infix[idx+1])) {
            return false;
        }
    }
    return true;
}

bool hasNoUnusedOperators(const string &infix) {
    for (int idx = 0; idx < infix.length(); idx++) {
        if(get_operator_value(infix[idx])) {
            if(idx < 1 || idx > infix.length() - 2) {
                return false;
            }
            if(infix[idx - 1] == '(' || infix[idx + 1] == ')') {
                return false;
            }
        }
    }
    return true;
}

bool hasNoUnusedVariables(const string &infix) {
    for (int idx = 0; idx < infix.length(); idx++) {
        if(!get_operator_value(infix[idx]) && infix[idx] != ')' && infix[idx] != '(') {
            if(idx > 0) {
                if(infix[idx-1] == ')' ) return false;
                if(!get_operator_value(infix[idx-1]) && infix[idx-1] != '(') return false;
            }
            if(idx < infix.length() - 1) {
                if(infix[idx + 1] == '(') return false;
                if(!get_operator_value(infix[idx+1]) && infix[idx+1] != ')') return false;
            }
        }
    }
    return true;
}

In::InOrChar resolve(string& s, int& start, bool must_return = true) {
    In::InOrChar first;
    In::InOrChar second;
    char o = '\0';
    In *i = new(In);
    for(; start < s.size();) {
        char current = s[start];
        if(current == '(') {
            start++;
            if(!exists(first)) {
                first = resolve(s, start);
            } else {
                second = resolve(s, start);
            }
            continue;
        }
        if(current == ')') {
            start++;
            break;
        }
        if(get_operator_value(current)) {
            if(o) {
                if(get_operator_value(current) > get_operator_value(o)) {
                    start--;
                    In::InOrChar new_second;
                    In::InOrChar new_first;
                    new_second = resolve(s, start);
                    new_first.in = new(In);
                    new_first.in->first = first;
                    new_first.in->second = new_second;
                    new_first.in->o = o;
                    first = new_first;
                    second.in = NULL;
                    second.c = '\0';
                    o = '\0';
                    continue;
                } else {
                    if(must_return) {
                        break;
                    }
                    In::InOrChar new_first;
                    new_first.in = new(In);
                    new_first.in->first = first;
                    new_first.in->second = second;
                    new_first.in->o = o;
                    first = new_first;
                    second.in = NULL;
                    second.c = '\0';
                    o = current;
                }
            } else {
                o = current;
            }
            start++;
            continue;
        } else {
            if(!exists(first)) {
                first.c = current;
            } else {
                second.c = current;
            }
            start++;
        }
    }

    In::InOrChar result;
    if(exists(first) && !exists(second)) {
        result = first;
        return result;
    }
    if(first.in) i->first.in = first.in;
    if(first.c) i->first.c = first.c;
    if(second.c) i->second.c = second.c;
    if(second.in) i->second.in = second.in;
    i->o = o;
    result.in= i;
    return result;
}

string infixToPostfixString(In::InOrChar ioc) {
    if(ioc.c) return string(1, ioc.c);
    /* return "(" + IntoString(ioc.in->first) + ioc.in->o + IntoString(ioc.in->second) + ")"; */
    return infixToPostfixString(ioc.in->first) + infixToPostfixString(ioc.in->second) + ioc.in->o;
}

string infixToPrefixString(In::InOrChar ioc) {
    if(ioc.c) return string(1, ioc.c);
    return ioc.in->o + infixToPrefixString(ioc.in->first) + infixToPrefixString(ioc.in->second);
}

In::InOrChar parse(string s) {
    int start = 0;
    return resolve(s, start, false);
}

string infixToPrefix(string infix) {
    In::InOrChar parsed = parse(infix);
    return infixToPrefixString(parsed);
}
string infixToPostfix(string infix) {
    In::InOrChar parsed = parse(infix);
    return infixToPostfixString(parsed);
}

bool is_valid_infix(string &infix) {
    cout <<infix << endl;
    cout << hasCorrectBrackets(infix) << hasNoPairedBrackets(infix) << hasNoPairedOperators(infix) && hasNoUnusedOperators(infix) && hasNoUnusedVariables(infix);
    return hasCorrectBrackets(infix) && hasNoPairedBrackets(infix) && hasNoPairedOperators(infix) && hasNoUnusedOperators(infix) && hasNoUnusedVariables(infix);
}
