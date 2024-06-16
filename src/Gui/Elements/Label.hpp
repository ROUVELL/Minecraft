#pragma once

#include <string>

#include "../../typedefs.hpp"


class UIBatch;

class Label
{
    std::string text;
    int x, y;
    color_t color;

public:
    Label(const std::string& text = "Label", int x = 0, int y = 0);
    Label(const Label&) = default;
    Label(Label&&) noexcept = default;
    ~Label() = default;

    void setText(const std::string& text) { this->text = text; }
    void setPosition(int x, int y) { this->x = x; this->y = y; }
    void setColor(color_t newColor) { color = newColor; }

    void render(UIBatch& uiBatch);
};