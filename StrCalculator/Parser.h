#pragma once
#include "Expressions.h"
#include "Lexer.h"

class Parser {
public:
    Parser(TokenList tokens_) {
        tokens = tokens_;
        pos = 0;
    }
    Expression * parse();
private:

    bool is_empty();
    Token look_ahead();
    void next_token();

    /**
      аждое правило try... возвращает:
     1) поддерево, если правило сработало
     2) NULL, если правило не сработало
     3) кидает exception, если правило сработало с ошибкой
    */
    Expression * tryPlusMinus(); // E
    Expression * tryMultDiv();   // T
    Expression * tryAtom();      // F
    Expression * tryNumber();    // NUMBER
    Expression * tryParens();    // ()

    unsigned int pos;
    TokenList tokens;
};