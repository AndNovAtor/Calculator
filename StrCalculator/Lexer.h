#pragma once
#include <string>
#include <vector>
#include "Errors.h"

enum TokenType {
    NUMBER,
    LP,
    RP,
    PLUS,
    MINUS,
    MULT,
    DIV,

    NOTHING // Для возврата ошибки
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, std::string v) {
        type = t;
        value = v;
    }

    Token(TokenType t, char v) {
        type = t;
        value = std::string(1, v);
    }

};

bool operator==(const Token & first, const Token & second);

typedef std::vector<Token> TokenList;

class Lexer {
public:
    Lexer(std::string code_) {
        code = code_;
        digit_acc = "";
    }
    TokenList tokenize();
private:
    void end_number();

    std::string code;
    std::string digit_acc;
    TokenList tokens;
};