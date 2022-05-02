#include "genxml.hpp"
#include <fmt/core.h>

FILE *Generator::generate(std::string ui, const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f)
        return nullptr;

    fprintf(f, "%s", ui.data());
    return f;
}

namespace ui_template {

std::string base_model(const Root &ast, struct module_s &m)
{
    return fmt::format(
            "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
            "<ui version=\"4.0\">\n"
            "{}\n{}\n{}\n"
            "</ui>",
            parent_widget_model(ast, m), resources_model(),
            connections_model());
}

std::string parent_widget_model(const Root &ast, struct module_s &m)
{
    struct module_s win;

    for (const auto &mod : ast.m_modules) {
        if (mod.m_keyword.m_type == WINDOW) {
            process_module(mod, win);
            break;
        }
    }

    return fmt::format(
        "<class>{0}</class>\n"
        "<widget class=\"QMainWindow\" name=\"{0}\">\n"
        "{1}"
        "<widget class=\"QWidget\" name=\"centralwidget\">\n"
        "{2}"
        "</widget>\n"
        "{3}\n{4}\n"
        "</widget>",
        win.name, widget_properties(WINDOW, win), central_widget_model(ast, m),
        menu_bar_model(), status_bar_model());
}

std::string central_widget_model(const Root &ast, struct module_s &m)
{
    std::string central_widget;

    for (const auto &mod : ast.m_modules) {
        if (mod.m_keyword.m_type == MODULE || mod.m_keyword.m_type == WINDOW ||
            mod.m_keyword.m_type == PALET || mod.m_keyword.m_type == PANEL)
            continue;
        process_module(mod, m);
        central_widget.append(widget_model(mod.m_keyword.m_type, m));
    }
    return central_widget;
}

std::string widget_model(token_t widget, const struct module_s &m)
{
    auto itr = qt_widgets_classes.find(widget);
    if (itr == qt_widgets_classes.end())
        throw std::runtime_error("Widget not found.");

    return fmt::format("<widget class=\"{}\" name=\"{}\">\n{}</widget>\n",
                       itr->second, m.name, widget_properties(widget, m));
}

void process_module(const Module &mod, struct module_s &m)
{
    for (const auto &stmt : mod.m_stmts) {
        if (stmt.m_left.m_value == "Name")
            m.name = stmt.m_right.m_value;
        else if (stmt.m_left.m_value == "X")
            m.x = stmt.m_right.m_value;
        else if (stmt.m_left.m_value == "Y")
            m.y = stmt.m_right.m_value;
        else if (stmt.m_left.m_value == "W")
            m.w = stmt.m_right.m_value;
        else if (stmt.m_left.m_value == "H")
            m.h = stmt.m_right.m_value;
        else if (stmt.m_left.m_value == "Label")
            m.label = stmt.m_right.m_value;
    }
}

std::string widget_properties(token_t widget, const struct module_s &m)
{
    // Geometry is a common property to all widgets.
    std::string s = geometry(m);

    switch (widget) {
    case WINDOW:
        s.append(text(m));
        break;

    case TAREA:
        s.append(text(m));
        break;

    case AFTED:
        break;

    case PBUT:
        s.append(text(m));
        break;

    default:
        break;
    }

    return s;
}

std::string geometry(const struct module_s &m)
{
    return fmt::format(
        "<property name=\"geometry\">\n"
        "<rect>\n"
        "<x>{}</x>\n"
        "<y>{}</y>\n"
        "<width>{}</width>\n"
        "<height>{}</height>\n"
        "</rect>\n"
        "</property>\n",
        m.x, m.y, m.w, m.h);
}

std::string text(const struct module_s &m)
{
    return fmt::format(
        "<property name=\"text\">\n<string>{}</string>\n</property>\n",
        m.label);
}

std::string resources_model(void) { return "<resources/>"; }

std::string connections_model(void) { return "<connections/>"; }

std::string menu_bar_model(void)
{
    return "<widget class=\"QMenuBar\" name=\"menubar\"/>";
}

std::string status_bar_model(void)
{
    return "<widget class=\"QStatusBar\" name=\"statusbar\"/>";
}

} // namespace ui_template
