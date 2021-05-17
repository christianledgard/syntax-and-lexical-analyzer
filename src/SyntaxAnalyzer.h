//
// Created by Christian Ledgard on 16/05/21.
//

#ifndef LAB2_SYNTAXANALYZER_H
#define LAB2_SYNTAXANALYZER_H

#include <utility>
#include <sstream>
#include <fstream>
#include <map>

#include "Lex.h"
#include "LexAnalyzer.h"

class SyntaxAnalyzer {
    vector<int> recursiveBlocks;
    vector<vector<bool(*)(const Lex&)>> blocks;
    
    
public:
    SyntaxAnalyzer(vector<int> recB, vector<vector<bool(*)(const Lex&)>> b) : recursiveBlocks(std::move(recB)), blocks(std::move(b)) {}
    
    bool analyze(const vector<Lex> &lexical) {
        int id = 0;
        for (int i = 0; i < blocks.size(); i++) {
            if (count(recursiveBlocks.begin(), recursiveBlocks.end(), i))
                while (blocks[i][0](lexical[id]) && id < lexical.size()) {
                    for (auto func : blocks[i]) {
                        if (!func(lexical[id])) return false;
                        id++;
                    }
                }
            else {
                for (auto func : blocks[i]) {
                    if (!func(lexical[id])) return false;
                    id++;
                }
            }
        }
        return (id == lexical.size());
    }
};


static bool isTerm(const Lex& term){
    return (term.t == ID || term.t == NUMBER);
}

static bool isRelop(const Lex& relop){
    switch(relop.t){
        case ASSIGN_OP:
        case MUL_OP:
        case REL_OP:
            return true;
        default:
            return false;
    }
}

#endif //LAB2_SYNTAXANALYZER_H
