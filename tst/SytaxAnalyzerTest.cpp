//
// Created by Christian Ledgard on 17/05/21.
//

#include <gtest/gtest.h>
#include <fstream>
#include "LexAnalyzer.h"
#include "SyntaxAnalyzer.h"

TEST(SyntaxAnalyzerTestSuite, ExpectedOutputsDiscord){
    std::ifstream input_true( "test_true.txt" );
    std::ifstream input_false( "test_false.txt" );

    // Se define la regla propuesta en el lab.
    // Se utilizará punteros a funciones.
    bool (*term)(const Lex&) = &isTerm;
    bool (*relop)(const Lex&) = &isRelop;
    std::vector<int> recursiveBlocks = {1};
    vector<vector<bool(*)(const Lex&)>> blocks = {{term}, {relop, term}};
    auto S = SyntaxAnalyzer(recursiveBlocks, blocks);


    for( std::string line; getline( input_true, line ); )
    {
        LexAnalyzer  one(line);
        EXPECT_TRUE(S.analyze(one.analyze()));
    }

    for( std::string line; getline( input_false, line ); )
    {
        LexAnalyzer  one(line);
        EXPECT_FALSE(S.analyze(one.analyze()));
    }
}