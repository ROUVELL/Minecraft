#include "Label.hpp"

#include "../../Graphics/UIBatch.hpp"


Label::Label(const std::string& text, int x, int y)
    : text(text),
    x(x), y(y)
{
}

void Label::render(UIBatch& textBatch)
{
    textBatch.text(text, x, y, {r, g, b, a});
}