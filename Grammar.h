//
// Created by Christian Ledgard on 16/05/21.
//

#ifndef LAB2_GRAMMAR_H
#define LAB2_GRAMMAR_H

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Tn{
    string b;
    char n;

    Tn(const string &b, char n) : b(b), n(n) {}
};

class Grammar{
private:
    map<char, vector<Tn>> rule;
    char start;

    static char checkInRow( map<char, vector<Tn>> r, char row, const string& input){

        for (const Tn& elem : r[row])
            if(input == elem.b)
                return elem.n;

        return false;
    }

public:
    Grammar(const map<char, vector<Tn>> &rule, char start) : rule(rule), start(start) {}

    bool isRuleValid(const vector<string>& inputVec){
        char current = start;

        for(auto &input: inputVec){
            char next = checkInRow(rule, current, input);
            current = next;
            if(!next) return false;
        }
        return true;
    }
    
};


#endif //LAB2_GRAMMAR_H
