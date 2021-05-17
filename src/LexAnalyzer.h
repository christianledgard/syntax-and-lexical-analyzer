//
// Created by Christian Ledgard on 16/05/21.
//

#ifndef LAB2_LEXANALYZER_H
#define LAB2_LEXANALYZER_H

#include "Lex.h"

class LexAnalyzer{

private:
    string lexToAnalyze;
    vector<Lex> result;

public:
    explicit LexAnalyzer(string lexToAnalyze) : lexToAnalyze(std::move(lexToAnalyze)) {}

    static bool isOperator(char &i) {
        switch (i) {
            case '(':
            case ')':
            case '<':
            case '>':
            case '+':
            case '-':
            case '=':
            case '*':
            case '/':
                return true;
            default:
                return false;
        }
    }
    
    void pushID(const string &identifier) {
        if (identifier == "if"){
            Lex n(IF);
            result.push_back(n);        
        }
        else if (identifier == "else"){
            Lex n(ELSE);
            result.push_back(n);
        }
        else {
            Lex n(ID,identifier);
            result.push_back(n);
        }
    }

    vector<Lex> analyze(){
        string temporalVariable = {};
        for (int i = 0; i < lexToAnalyze.size(); ++i) {
            char c = lexToAnalyze[i];
            switch (c) {

                //[A-z] VARIABLES
                case 'A'...'z': {

//                    //APPEND CASE
//                    if (!result.empty() and result.back().t == ID){
//                        result.back().identifier += c;
//                    }
//                        //FIRST TIME CASE
//                    else {
//                        Lex n(ID, c);
//                        result.push_back(n);
//                    }
                    temporalVariable += c;
                    if(i+1 == lexToAnalyze.size() || isOperator(lexToAnalyze[i+1])){
                        pushID(temporalVariable);
                        temporalVariable.clear();
                    }

                    //CHECK SPECIAL WORDS
/*                    if (!result.empty()){
                        if(result.back().identifier == "if"){
                            result.back().identifier.clear();
                            result.back().t = IF;
                        } else if (result.back().identifier == "else"){
                            result.back().identifier.clear();
                            result.back().t = ELSE;
                        }
                    }*/

                    //CHECK SCI NUMBER
                    if (!result.empty() and result.back().identifier == "E"){
                        if(lexToAnalyze[i+1] == '-' or lexToAnalyze[i+1] == '+'){
                            auto appendIdentifier = result.back().identifier;
                            result.pop_back();
                            result.back().identifier += appendIdentifier;
                            result.back().t = NUMBER;
                        } else {
                            cout << "Error, a scientific number must have a '+' or '-' before the char E." << endl;
                            result.pop_back();
                        }
                    }
                    break;
                }
                    //SIMPLY IGNORE THE WHITE SPACES and \n
                case ' ':{
                    if (temporalVariable.length()){
                        pushID(temporalVariable);
                        temporalVariable.clear();
                    }
                    break;
                }
                case '\n':
                case '\t':
                    break;
                case '(': {
                    Lex n(PAR_BEGIN);
                    result.push_back(n);
                    break;
                }
                case ')': {
                    Lex n(PAR_END);
                    result.push_back(n);
                    break;
                }
                case ';': {
                    Lex n(END_L);
                    result.push_back(n);
                    break;
                }
                    //REAL OPERATION CASES
                case '=':
                case '-':
                case '>':
                case '<': {

                    //SCIENTIFIC NUMBER CASE
                    if(!result.empty() and c == '-' and result.back().identifier[result.back().identifier.size()-1] == 'E'){
                        result.back().identifier += c;
                    }
                        // SPECIAL CASE >= or <=
                    else if (lexToAnalyze[i+1] == '=' and (c == '<' or c == '>')){
                        std::string concatString;
                        concatString = c;
                        concatString += '=';

                        Lex n(REL_OP, concatString);
                        result.push_back(n);
                        ++i;
                    }
                        // SPECIAL CASE == 
                    else if (lexToAnalyze[i+1] == '='){
                        std::string concatString;
                        concatString = c;
                        concatString += '=';

                        Lex n(REL_OP, concatString);
                        result.push_back(n);
                        ++i;
                    }
                        //ASSIGN OP
                    else if (c == '='){
                        Lex n(ASSIGN_OP);
                        result.push_back(n);
                    }
                        //NORMAL BEHAVIOR
                    else {
                        Lex n(REL_OP, c);
                        result.push_back(n);
                    }
                    break;
                }
                case '.':{
                    //CHECK IF THERE IS A NUMBER BEFORE A DOT
                    if (!result.empty() and result.back().t == NUMBER){
                        result.back().identifier += c;
                    } else {
                        cout << "You cant use a dot without a number.";
                    }
                    break;
                }
                case '*':{
                    Lex n(MUL_OP);
                    result.push_back(n);
                    break;
                }
                case '0'...'9':{
                    if (!result.empty() and result.back().t == NUMBER){
                        result.back().identifier += c;
                    } else {
                        Lex n(NUMBER, c);
                        result.push_back(n);
                    }
                    break;
                }
                    //IF IT'S NOT RECOGNIZED, DEFAULT CASE
                default:
                    cout << "Error en el código, caracter " << c << " no soportado.";
                    break;
            }
        }
        return result;
    }

    void print(){
        for (Lex& l: result) {
            l.print();
        }
        cout << endl;
    }

};

#endif //LAB2_LEXANALYZER_H
