#include "Lexer.h"
using namespace std;

TokenList Lexer::tokenize() {

    for (unsigned pos = 0; pos < code.size(); ++pos) {
        char cur = code[pos];
        switch (cur) {
        case ' ':
            // игнорируем
            end_number();
            break;
        case '(':
            end_number();
            tokens.push_back(Token(LP, cur));
            break;
        case ')':
            end_number();
            tokens.push_back(Token(RP, cur));
            break;
        case '+':
            end_number();
            tokens.push_back(Token(PLUS, cur));
            break;
        case '-':
            end_number();
            tokens.push_back(Token(MINUS, cur));
            break;
        case '*':
            end_number();
            tokens.push_back(Token(MULT, cur));
            break;
        case '/':
            end_number();
            tokens.push_back(Token(DIV, cur));
            break;
        default:
            if (isdigit(cur)) {
                digit_acc.push_back(cur);
            } else {
                throw SyntaxError(string("Invalid character ") + cur);
            }
            break;
        }
    }
    end_number();
    
    return tokens;
}

void Lexer::end_number() {
    if (!digit_acc.empty()) {
        tokens.push_back(Token(NUMBER, digit_acc));
        digit_acc = "";
    }
}

bool operator==(const Token & first, const Token & second) {
    return (first.type == second.type) && (first.value == second.value);
}