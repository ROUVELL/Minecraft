#pragma once

#include <string>


class UIBatch;

class Label
{
    std::string text;
    int x, y;
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;

public:
    Label(const std::string& text = "Label", int x = 0, int y = 0);
    Label(const Label&) = default;
    Label(Label&&) noexcept = default;
    ~Label() = default;

    void setText(const std::string& text) { this->text = text; }
    void setPosition(int x, int y) { this->x = x; this->y = y; }
    void setColor(float r, float g, float b, float a = 1.0) { this->r = r; this->g = g; this->b = b; this->a = a; }

    void render(UIBatch& uiBatch);
};