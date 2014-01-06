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
     ������ ������� try... ����������:
     1) ���������, ���� ������� ���������
     2) NULL, ���� ������� �� ���������
     3) ������ exception, ���� ������� ��������� � �������
    */
    Expression * tryPlusMinus(); // E
    Expression * tryMultDiv();   // T
    Expression * tryAtom();      // F
    Expression * tryNumber();    // NUMBER
    Expression * tryParens();    // ()

    unsigned int pos;
    TokenList tokens;
};