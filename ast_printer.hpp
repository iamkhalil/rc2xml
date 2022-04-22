#ifndef AST_PRINTER_HPP
#define AST_PRINTER_HPP

#include "token.hpp"
#include <iostream>
#include <vector>

class Statement {
public:
    Statement(Token left, Token right);
    void print(const size_t &indent) const;

    Token m_left;
    Token m_right;
};

class Module {
public:
    Module(Token keyword, std::vector<Statement> stmts);
    void add_statement(const Statement &stmts);
    void print(const size_t &indent) const;

    Token m_keyword;
    std::vector<Statement> m_stmts;
};

class Root {
public:
    Root(std::vector<Module> modules);
    void add_module(const Module &mod);
    void print(size_t indent = 1) const;

    std::vector<Module> m_modules;
};

#endif // AST_PRINTER_HPP
