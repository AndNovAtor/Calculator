#include "Parser.h"
#include <exception>
#include <stdexcept>
using namespace std;

Expression * Parser::parse() {
    Expression * res = tryPlusMinus();
    if (res == NULL) { // ни одно правило не сработало
        throw SyntaxError(string("Expected expression, found ") + look_ahead().value);
    }
    if (!is_empty()) { // какое-то правило сработало, но в конце остались символы
        throw SyntaxError(string("Unexpected symbols at the end starting from: ") + look_ahead().value);
    }
    return res;
}

// парсит T [ +|- T] где T - это результат tryMultDiv
// (любое число + и -, в том числе ни одного, т.е. просто T)
Expression * Parser::tryPlusMinus() {
    Expression * res = tryMultDiv();
    if (res == NULL) { return NULL; }
    while (true) {
        if (look_ahead().type == PLUS) {
            next_token();
            Expression * res2 = tryMultDiv();
            if (res2 == NULL) {
                throw SyntaxError(string("Expected another argument after +, found ") + look_ahead().value);
            }
            res = new Plus(res, res2);
        }
        else if (look_ahead().type == MINUS) {
            next_token();
            Expression * res2 = tryMultDiv();
            if (res2 == NULL) {
                throw SyntaxError(string("Expected another argument after -, found ") + look_ahead().value);
            }
            res = new Minus(res, res2);
        } else {
            return res;
        }
    }
}

// парсит F [ *|/ F] где F - это результат tryAtom
// (любое число * и /, в том числе ни одного, т.е. просто F)
Expression * Parser::tryMultDiv() {
    Expression * res = tryAtom();
    if (res == NULL) { return NULL; }
    while (true) {
        if (look_ahead().type == MULT) {
            next_token();
            Expression * res2 = tryAtom();
            if (res2 == NULL) {
                throw SyntaxError(string("Expected another argument after *, found ") + look_ahead().value);
            }
            res = new Multiply(res, res2);
        } else if (look_ahead().type == DIV) {
            next_token();
            Expression * res2 = tryAtom();
            if (res2 == NULL) {
                throw SyntaxError(string("Expected another argument after /, found ") + look_ahead().value);
            }
            res = new Divide(res, res2);
        } else {
            return res;
        }

    }
}

// парсит NUMBER | ( E ) где E - это любое выражение
Expression * Parser::tryAtom() {
    Expression * res;
    res = tryNumber();
    if (res != NULL) {
        return res;
    }
    return tryParens();
}

// парсит NUMBER
Expression * Parser::tryNumber() {
    Token t = look_ahead();
    if (t.type == NUMBER) {
        next_token();
        try {
            int val = stoi(t.value);
            // TODO: проверка на корректность числа
            return new Number(val);
        } catch (invalid_argument e) {
            throw SyntaxError(string("INTERNAL ERROR: invalid number: ") + t.value);
        }  catch (out_of_range e) {
            throw SyntaxError(string("Too big number: ") + t.value);
        }
    } else {
        return NULL;
    }
}

// парсит ( E ) где E - это любое выражение (в скобках), т.е. результат tryPlusMinus
Expression * Parser::tryParens() {
    if (look_ahead().type == LP) {
        next_token();
        Expression * res = tryPlusMinus();
        if (look_ahead().type != RP) {
            throw SyntaxError("Not found closing ')'");
        }
        next_token();
        return res; // res может быть NULL: если tryPlusMinus не сработал
    } else {
        return NULL;
    }
}

bool Parser::is_empty() {
    return pos >= tokens.size();
}

Token Parser::look_ahead() {
    if (is_empty()) {
        return Token(NOTHING, "<END OF STRING>");
    } else {
        return tokens[pos];
    }
}

void Parser::next_token() {
    pos += 1;
}