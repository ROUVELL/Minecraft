#include "Label.hpp"

#include "../Graphics/TextBatch.hpp"
#include <string>

Label::Label(TextBatch* textBatch)
    : Label(textBatch, "Label", 0, 0)
{
}

Label::Label(TextBatch* textBatch, const std::string& text)
    : Label(textBatch, text, 0, 0)
{
}

Label::Label(TextBatch* textBatch, const std::string& text, int x, int y)
    : textBatch(textBatch),
    text(text),
    x(x), y(y),
    r(1.0), g(1.0), b(1.0), a(1.0)
{
}

Label::Label(const Label& other)
    : textBatch(other.textBatch),
    text(other.text),
    x(other.x), y(other.y),
    r(other.r), g(other.g), b(other.b), a(other.a)
{
}

Label::Label(Label&& other) noexcept
    : textBatch(other.textBatch),
    text(other.text),
    x(other.x), y(other.y),
    r(other.r), g(other.g), b(other.b), a(other.a)
{
}

void Label::render()
{
    textBatch->text(text, x, y, r, g, b, a);
}