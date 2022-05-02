#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"
#include "ast_printer.hpp"
#include <optional>

class Parser {
public:
    Root parse(std::vector<Token> &tokens);
private:
    Module parse_module();
    Statement parse_statement(bool *check_rec);

    std::optional<Token> expect_lparen();
    std::optional<Token> expect_rparen();
    std::optional<Token> expect_colon();
    std::optional<Token> expect_keyword();
    std::optional<Token> expect_identifier();
    std::optional<Token> expect_literal();

    std::vector<Token>::iterator m_current_token;
    std::vector<Token>::iterator m_end_token;
};

#endif // PARSER_HPP

/*
 * Grammar:
 *
 * Root -> Module* ;
 * Module -> Left_paren Keyword Statement+ Right_paren ;
 * Statement -> Identifier Colon Literal Statement | Identifier Colon Literal ;
 *
 * // Terminals
 * Left_paren -> LEFT_PAREN ;
 * Right_paren -> RIGHT_PAREN ;
 * Colon -> COLON ;
 * Keyword -> WINDOW | PANEL | PALET | TAERA | ... ;
 * Identifier -> IDENTIFIER ;
 * Literal -> INTEGER | HEXA | STRING | NIL ;
 *
 *        /_____________
 *        |             |
 *        |             |
 *      Module_1       ...
 *        |
 *        |
 *   ( WIN Statement )
 *           |
 *           |
 *       IDENTIFIER COLON VALUE Statement
 *                                   |
 *                                   |
 *                           IDENTIFIER COLON VALUE ;;
 */
