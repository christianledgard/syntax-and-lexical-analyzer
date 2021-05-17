#include <sstream>
#include <fstream>
#include <map>

#include "LexAnalyzer.h"
#include "SyntaxAnalyzer.h"


int main() {
    cout << "Hello";

    std::ifstream input( "inputold.txt" );

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