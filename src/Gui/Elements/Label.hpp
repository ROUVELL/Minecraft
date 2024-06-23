#pragma once

#include <string>

#include "UIElement.hpp"

/*
TODO: Perhaps it makes sense to divide the label into static and dynamic.

In a static label, the text will be set only once and will not change (or will change very rarely).
And with the help of a pre-render it can be rendered much faster.
Such, for example, can be used in buttons or console messages.

In dynamic labels, the text will change very often,
and therefore it is not efficient to use a pre-render.
This one is suitable for debug information output
*/

/* Label with the ability to dynamically change the text (pre-rendering is not used) */
class Label : public UIElement
{
    std::string text = "Label";
    color_t color = colors::WHITE;

public:
    Label() = default;
    Label(const Label&) = default;
    Label(Label&&) = default;
    ~Label() = default;

    void setText(const std::string& text) noexcept { this->text = text; }
    void setColor(color_t newColor) noexcept { color = newColor; }

    void render(const UIBatch& uiBatch) const noexcept override;
};