#pragma once
#include "Errors.h"

class Expression {
public:
    virtual int eval() = 0;

    virtual ~Expression() {}
};

class Number : public Expression {
public:
    Number(int val) {
        value = val;
    }
    virtual int eval() {
        return value;
    }
private:
    int value;
};

class BinaryOperation : public Expression {
public:
    BinaryOperation(Expression * left, Expression * right) {
        leftOp = left;
        rightOp = right;
    }

    virtual ~BinaryOperation() {
        delete leftOp;
        delete rightOp;
    }
protected:
    Expression * leftOp;
    Expression * rightOp;
};

class Multiply : public BinaryOperation {
public:
    Multiply(Expression * left, Expression * right) : BinaryOperation(left, right) {}

    virtual int eval() {
        return leftOp->eval() * rightOp->eval();
    }

};

class Divide : public BinaryOperation {
public:
    Divide(Expression * left, Expression * right) : BinaryOperation(left, right) {}

    virtual int eval() {
        int left = leftOp->eval();
        int right = rightOp->eval();
        if (right == 0) { throw RuntimeError("division by zero"); }
        return left / right;
    }
};

class Plus : public BinaryOperation {
public:
    Plus(Expression * left, Expression * right) : BinaryOperation(left, right) {}

    virtual int eval() {
        return leftOp->eval() + rightOp->eval();
    }
};

class Minus : public BinaryOperation {
public:
    Minus(Expression * left, Expression * right) : BinaryOperation(left, right) {}

    virtual int eval() {
        return leftOp->eval() - rightOp->eval();
    }
};

