#include "scanner.hpp"
#include "parser.hpp"
#include "genxml.hpp"
#include <iostream>
#include <cstring>

/**
 * main - Entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: On success, 0 is returned. On error, non-zero is returned.
 */
int main(int argc, char *argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Usage: ./rc2xml file.rc\n";
            exit(1);
        }

        auto len = std::strlen(argv[1]);
        if (argv[1][len - 1] != 'c' || argv[1][len - 2] != 'r' || argv[1][len - 3] != '.') {
            std::cerr << "Error: Bad extension.\n";
            exit(2);
        }

        FILE *f = fopen(argv[1], "r");
        if (!f) {
            std::cerr << "Error: Can't find " << argv[1] << ".\n";
            exit(3);
        }

        fseek(f, 0, SEEK_END);
        std::size_t file_size = ftell(f);
        fseek(f, 0, SEEK_SET);
        std::string file_contents(file_size, ' ');
        fread(file_contents.data(), 1, file_size, f);
        fclose(f);

        std::cout << file_contents << "\n\n";

        Scanner scanner;
        std::vector<Token> tokens = scanner.scan(file_contents);
        for (const Token &tok : tokens) {
            tok.print();
        }

        Parser parser;
        Root root = parser.parse(tokens);
        root.print();

        char tmp[len - 3];
        for (auto i = 0; i < len - 3; ++i)
            tmp[i] = argv[1][i];
        char *filename = std::strcat(tmp, ".ui");

        Generator genxml;
        struct ui_template::module_s m;

        std::string ui = ui_template::base_model(root, m);
        f = genxml.generate(ui, filename);
        if (!f) {
            std::cerr << "Error: can't find " << filename << ".\n";
            exit(4);
        }
        fclose(f);

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << '\n';
        exit(42);
    }
    return 0;
}
