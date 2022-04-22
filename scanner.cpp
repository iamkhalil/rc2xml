#include "scanner.hpp"

/**
 * add_token - Adds a token to the list of tokens, then resets it.
 * @token: the given token
 * @tokens: the list of tokens
 */
void Scanner::add_token(Token &token, std::vector<Token> &tokens)
{
    // We check if a module or an identifier matches anything in the map.
    // If so, we use that keyword's token type instead of the current one.
    if (token.m_type == IDENTIFIER || token.m_type == MODULE) {
        auto itr = keywords.find(token.m_value);
        if (itr != keywords.end())
            token.m_type = itr->second;
    }

    if (token.m_type != WHITESPACE)
        tokens.push_back(token);

    token.m_type = WHITESPACE;
    token.m_value.erase();
}

/**
 * scan - Performs lexical analysis over an input resource file.
 * @filename: the given resource file (*.rc)
 *
 * Return: A list of tokens.
 */
std::vector<Token> Scanner::scan(const std::string &filename)
{
    std::vector<Token> tokens;
    Token current_token = Token{WHITESPACE, "", 1};

    for (auto itr = filename.begin(); itr != filename.end(); ++itr) {
        switch (*itr) {
        case '/':
            while (*itr != '\n')
                ++itr;
            ++current_token.m_line;
            break;

        case '\n':
            add_token(current_token, tokens);
            ++current_token.m_line;
            break;

        case ' ':
        case '\r':
        case '\t':
            add_token(current_token, tokens);
            break;

        case '(':
            if (current_token.m_type == WHITESPACE) {
                current_token.m_type = LEFT_PAREN;
                current_token.m_value.append(1, *itr);
            }
            break;

        case ')':
            if (current_token.m_type == WHITESPACE ||
                current_token.m_type == STRING ||
                current_token.m_type == INTEGER ||
                current_token.m_type == HEXA) {

                current_token.m_type = RIGHT_PAREN;
                current_token.m_value.append(1, *itr);
                add_token(current_token, tokens);
            }
            break;

        case ':':
            if (current_token.m_type == IDENTIFIER) {
                add_token(current_token, tokens);
                current_token.m_type = COLON;
                current_token.m_value.append(1, *itr);
                add_token(current_token, tokens);
            } else {
                current_token.m_value.append(1, *itr);
            }
            break;

        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (current_token.m_type == WHITESPACE) {
                current_token.m_type = INTEGER;
                current_token.m_value.append(1, *itr);
            } else {
                current_token.m_value.append(1, *itr);
            }
            break;

        case 'x':
            if (current_token.m_type == INTEGER) {
                current_token.m_type = HEXA;
                current_token.m_value.append(1, *itr);
            } else {
                current_token.m_value.append(1, *itr);
            }
            break;

        case '"':
            if (current_token.m_type != STRING)
                current_token.m_type = STRING;
            else
                add_token(current_token, tokens);
            break;

        default:
            if (current_token.m_type == WHITESPACE) {
                add_token(current_token, tokens);
                current_token.m_type = IDENTIFIER;
                current_token.m_value.append(1, *itr);
            } else if (current_token.m_type == LEFT_PAREN) {
                add_token(current_token, tokens);
                current_token.m_type = MODULE;
                current_token.m_value.append(1, *itr);
            } else {
                current_token.m_value.append(1, *itr);
            }
            break;
        }
    }
    return tokens;
}
