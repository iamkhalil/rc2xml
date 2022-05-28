#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <unordered_map>

typedef enum {
    // single-char tokens
    WHITESPACE,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,

    // Literals
    MODULE,
    IDENTIFIER,
    STRING,
    INTEGER,
    HEXA,

    // Keywords
    NIL,
    WINDOW,
    PANEL,
    PALET,
    TAREA,
    AFTED,
    PBUT,
    CBOX,
    CBUT

} token_t;

static const char *token_types[] = {
    "WHITESPACE",
    "LEFT_PAREN",
    "RIGHT_PAREN",
    "COLON",
    "MODULE",
    "IDENTIFIER",
    "STRING",
    "INTEGER",
    "HEXA",
    "NIL",
    "WINDOW",
    "PANEL",
    "PALET",
    "TAREA",
    "AFTED",
    "PBUT",
    "CBOX",
    "CBUT"
};

static const std::unordered_map<std::string, token_t> keywords = {
    {"Win.Compile", WINDOW},
    {"Panel.Compile", PANEL},
    {"Palet.Compile", PALET},
    {"TArea.Compile", TAREA},
    {"AFTEd.Compile", AFTED},
    {"PBut.Compile", PBUT},
    {"CBox.Compile", CBOX},
    {"CBut.Compile", CBUT},
    {"NULL", NIL}
};

class Token {
public:
    Token(token_t type, std::string value, size_t line)
        : m_type(type), m_value(value), m_line(line) {}
    void print() const;

    token_t m_type;
    std::string m_value;
    size_t m_line;
};

#endif // TOKEN_HPP
