#include "token.hpp"
#include <iostream>

void Token::print() const
{
    std::cout << "Token: [\"" << m_value << "\", " << token_types[m_type]
              << ", " << m_line << "]\n";
}
