#include "Parser.h"
#include <iostream>
#include "stdutil.h"
using namespace std;

int interpret(string code) {
    TokenList tokens = Lexer(code).tokenize();
    Expression * exprTree = Parser(tokens).parse();
    int res = exprTree->eval();
    delete exprTree;
    return res;
}

void testAll();

int main() {
   /* testAll();*/
    cout << "Enter expressions in one string:" << endl;
    string code;
    getline(cin, code);
    try {
        cout << "Result = " << interpret(code);
    } catch (SyntaxError e) {
        cout << "Syntax error: " << e.what();
    } catch (RuntimeError e) {
        cout << "Runtime error: " << e.what();
    }
    catch (exception e)  {
        cout << "INTERNAL ERROR: " << e.what();
    }
    pause();
    return 0;
}

// ----

void check(string msg, bool cond) {
    if (cond) { cout << "OK\n"; }
    else { cout << msg << " FAILED!\n"; }
}

void testLexer() {
    check("1",  Lexer("1").tokenize() == TokenList({ Token(NUMBER, "1") }));
    check("+-", Lexer("25+3-112").tokenize() == TokenList({ Token(NUMBER, "25"), Token(PLUS, "+"), Token(NUMBER, "3"), Token(MINUS, "-"), Token(NUMBER, "112") }));
    check("()", Lexer("( 2 * 3 ) ").tokenize() == TokenList({ Token(LP, "("), Token(NUMBER, "2"), Token(MULT, "*"), Token(NUMBER, "3"), Token(RP, ")") }));
}

void testEval() {
    Expression * expr = new Multiply(new Number(3), new Multiply(new Number(4), new Number(5)));
    check("eval", expr->eval() == 60);
}

void testAll() {
    testLexer();
    testEval();
}