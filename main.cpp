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

int main() {

    std::ifstream input( "input.txt" );

    // Se define la regla propuesta en el lab.
    // Se utilizará punteros a funciones.
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
    }
    return 0;
}