#ifndef GENXML_HPP
#define GENXML_HPP

#include "ast_printer.hpp"
#include <string>
#include <unordered_map>

namespace ui_template {

struct module_s {
    std::string name;
    std::string x;
    std::string y;
    std::string w;
    std::string h;
    std::string label;
};

static const std::unordered_map<token_t, std::string> qt_widgets_classes = {
    {TAREA, "QLabel"},
    {AFTED, "QLineEdit"},
    {PBUT, "QPushButton"}
};

// models
std::string base_model(const Root &ast, struct module_s &m);
std::string parent_widget_model(const Root &ast, struct module_s &m);
std::string resources_model(void);
std::string connections_model(void);

std::string central_widget_model(const Root &ast, struct module_s &m);
std::string widget_model(token_t widget, const struct module_s &m);
std::string menu_bar_model(void);
std::string status_bar_model(void);

// widget properties
std::string geometry(const struct module_s &m);
std::string text(const struct module_s &m);
//std::string font(const struct module_s &m);

std::string widget_properties(token_t widget, const struct module_s &m);
void process_module(const Module& mod, struct module_s &m);

} // ui_namespace

class Generator {
public:
    FILE *generate(std::string ui, const char *filename);
};

#endif // GENXML_HPP
