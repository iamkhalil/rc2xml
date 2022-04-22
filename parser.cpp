#include "parser.hpp"

Root Parser::parse(std::vector<Token> &tokens)
{
    Root root = Root{{}};

    m_current_token = tokens.begin();
    m_end_token = tokens.end();

    while (m_current_token != m_end_token) {
        root.add_module(parse_module());
    }
    return root;
}

Module Parser::parse_module()
{
    std::optional<Token> lparen = expect_lparen();
    if (!lparen.has_value())
        throw std::runtime_error("Expected '(' at start of a module.");

    std::optional<Token> keyword = expect_keyword();
    if (!keyword.has_value())
        throw std::runtime_error("Expected a Module name after '('.");

    Module module = Module{keyword.value(), {}};
    bool check_rec = true;
    while (check_rec) {
        module.add_statement(parse_statement(&check_rec));
    }

    std::optional<Token> rparen = expect_rparen();
    if (!rparen.has_value())
        throw std::runtime_error("Expected ')' at the end of a module.");

    return module;
}

Statement Parser::parse_statement(bool *check_rec)
{
    std::optional<Token> identifier = expect_identifier();
    if (!identifier.has_value())
        throw std::runtime_error("Expected an IDENTIFIER at start of a statement.");

    std::optional<Token> colon = expect_colon();
    if (!colon.has_value())
        throw std::runtime_error("Expected a COLON after an IDENTIFIER.");

    std::optional<Token> literal = expect_literal();
    if (!literal.has_value())
        throw std::runtime_error("Expected a literal after a COLON.");

    if (m_current_token->m_type == RIGHT_PAREN) // we've reached the end of a module
        *check_rec = false;

   return Statement{identifier.value(), literal.value()};
}

std::optional<Token> Parser::expect_lparen()
{
    if (m_current_token->m_type != LEFT_PAREN)
        return std::nullopt;

    Token tok = *m_current_token;
    ++m_current_token;
    return tok;
}

std::optional<Token> Parser::expect_rparen()
{
    if (m_current_token == m_end_token)
        return std::nullopt;

    if (m_current_token->m_type != RIGHT_PAREN)
        return std::nullopt;

    Token tok = *m_current_token;
    ++m_current_token;
    return tok;
}

std::optional<Token> Parser::expect_keyword()
{
    for (const auto &e : keywords) {
        if (m_current_token->m_type == e.second) {
            Token tok = *m_current_token;
            ++m_current_token;
            return tok;
        }
    }
    return std::nullopt;
}

std::optional<Token> Parser::expect_identifier()
{
    if (m_current_token->m_type != IDENTIFIER)
        return std::nullopt;

    Token tok = *m_current_token;
    ++m_current_token;
    return tok;
}

std::optional<Token> Parser::expect_colon()
{
    if (m_current_token->m_type != COLON)
        return std::nullopt;

    Token tok = *m_current_token;
    ++m_current_token;
    return tok;
}

std::optional<Token> Parser::expect_literal()
{
    if (m_current_token->m_type == INTEGER || m_current_token->m_type == HEXA ||
        m_current_token->m_type == STRING || m_current_token->m_type == NIL) {
        Token tok = *m_current_token;
        ++m_current_token;
        return tok;
    }
    return std::nullopt;
}
