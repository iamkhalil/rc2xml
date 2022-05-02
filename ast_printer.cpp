#include "ast_printer.hpp"

Statement::Statement(Token left, Token right)
    : m_left(left), m_right(right) {}

void Statement::print(const size_t &indent) const
{
    std::cout << std::string(indent, '\t') << "@STATEMENT (\n";
    std::cout << std::string(indent + 1, '\t') << '@' << token_types[m_left.m_type]
              << " -> " << m_left.m_value << '\n';
    std::cout << std::string(indent + 1, '\t') << '@' <<token_types[m_right.m_type]
              << " -> " << m_right.m_value << '\n' << std::string(indent, '\t') << ")\n";
}

Module::Module(Token keyword, std::vector<Statement> stmts)
    : m_keyword(keyword), m_stmts(stmts) {}

void Module::add_statement(const Statement &stmts)
{
    m_stmts.push_back(stmts);
}

void Module::print(const size_t &indent) const
{
    std::cout << "@MODULE: " << token_types[m_keyword.m_type] << "(\n";
    for (const auto &s : m_stmts) {
        s.print(indent);
    }
    std::cout << ")\n";
}

Root::Root(std::vector<Module> modules)
    : m_modules(modules) {}

void Root::add_module(const Module &mod)
{
    m_modules.push_back(mod);
}

void Root::print(size_t indent) const
{
    for (const auto &m : m_modules) {
        m.print(indent);
        std::cout << '\n';
    }
}
