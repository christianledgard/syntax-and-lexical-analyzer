//
// Created by Christian Ledgard on 16/05/21.
//

#ifndef LAB2_LEX_H
#define LAB2_LEX_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

enum Type {ID, ASSIGN_OP, MUL_OP, NUMBER, IF,ELSE, PAR_BEGIN, PAR_END, REL_OP, END_L};

struct Lex{
    Type t;
    string identifier;

    explicit Lex(Type t) : t(t) {
        identifier.clear();
    }

    Lex(Type t, string identifier) : t(t), identifier(std::move(identifier)) {}

    Lex(Type t, char identifier) : t(t) {
        string s(1, identifier);
        this->identifier = s;
    }

    void print() const{
        const char* typeText[] = {"ID", "ASSIGN_OP", "MUL_OP", "NUMBER", "IF", "ELSE", "PAR_BEGIN", "PAR_END", "REL_OP", "END_L"} ;

        if(identifier.empty()){
            cout << '<' << typeText[t] << '>' << ' ';
        }else{
            string ident;
            if(t==REL_OP){
                ident = '\'' + identifier + '\'';
            } else {
                ident = identifier;
            }
            cout << '<' << typeText[t] << ',' << ident << '>' << ' ';
        }
    }
};


#endif //LAB2_LEX_H
