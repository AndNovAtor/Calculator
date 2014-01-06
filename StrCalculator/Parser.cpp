#include "Parser.h"
#include <exception>
#include <stdexcept>
using namespace std;

Expression * Parser::parse() {
    Expression * res = tryPlusMinus();
    if (res == NULL) { // �� ���� ������� �� ���������
        throw SyntaxError(string("Expected expression, found ") + look_ahead().value);
    }
    if (!is_empty()) { // �����-�� ������� ���������, �� � ����� �������� �������
        throw SyntaxError(string("Unexpected symbols at the end starting from: ") + look_ahead().value);
    }
    return res;
}

// ������ T [ +|- T] ��� T - ��� ��������� tryMultDiv
// (����� ����� + � -, � ��� ����� �� ������, �.�. ������ T)
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

// ������ F [ *|/ F] ��� F - ��� ��������� tryAtom
// (����� ����� * � /, � ��� ����� �� ������, �.�. ������ F)
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

// ������ NUMBER | ( E ) ��� E - ��� ����� ���������
Expression * Parser::tryAtom() {
    Expression * res;
    res = tryNumber();
    if (res != NULL) {
        return res;
    }
    return tryParens();
}

// ������ NUMBER
Expression * Parser::tryNumber() {
    Token t = look_ahead();
    if (t.type == NUMBER) {
        next_token();
        try {
            int val = stoi(t.value);
            // TODO: �������� �� ������������ �����
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

// ������ ( E ) ��� E - ��� ����� ��������� (� �������), �.�. ��������� tryPlusMinus
Expression * Parser::tryParens() {
    if (look_ahead().type == LP) {
        next_token();
        Expression * res = tryPlusMinus();
        if (look_ahead().type != RP) {
            throw SyntaxError("Not found closing ')'");
        }
        next_token();
        return res; // res ����� ���� NULL: ���� tryPlusMinus �� ��������
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