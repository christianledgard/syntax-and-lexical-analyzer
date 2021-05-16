#include <sstream>
#include <fstream>
#include <map>

#include "LexAnalyzer.h"
#include "SyntaxAnalyzer.h"

bool isTerm(const Lex& term){
    return (term.t == ID || term.t == NUMBER);
}

bool isRelop(const Lex& relop){
    switch(relop.t){
        case ASSIGN_OP:
        case MUL_OP:
        case REL_OP:
            return true;
        default:
            return false;   
    }
}

bool grammarS(vector<Lex> lexical){
    int i = 0;
    if (!isTerm(lexical[i])) return false;
    i++;
    while(isRelop(lexical[i])){
        if (!isRelop(lexical[i])) return false;
        i++;
        if (!isTerm(lexical[i])) return false;
        i++;
    }
    return true;
}

int main() {

    std::ifstream input( "input.txt" );

    bool (*term)(const Lex&) = &isTerm;
    bool (*relop)(const Lex&) = &isRelop;
    vector<int> recursiveBlocks = {1};
    vector<vector<bool(*)(const Lex&)>> blocks = {{term}, {relop, term}};
    auto S = SyntaxAnalyzer(recursiveBlocks, blocks);
    
    for( std::string line; getline( input, line ); )
    {
        cout << line << endl;
        LexAnalyzer  one(line);
        vector<Lex> lexical = one.analyze();
        cout << S.analyze(lexical) << endl;
        one.print();
        cout << "\t---" << endl;
    }
    return 0;
}