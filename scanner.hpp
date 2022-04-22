#ifndef SCANNER_HPP
#define SCANNER_HPP

#include "token.hpp"
#include <vector>

class Scanner {
public:
    std::vector<Token> scan(const std::string &filename);
private:
    void add_token(Token &token, std::vector<Token> &tokens);
};

#endif // SCANNER_HPP
