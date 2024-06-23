#include "Label.hpp"

#include "../../Graphics/UIBatch.hpp"


void Label::render(const UIBatch& textBatch) const noexcept
{
    textBatch.text(text, rect.position.x, rect.position.y, color);
}