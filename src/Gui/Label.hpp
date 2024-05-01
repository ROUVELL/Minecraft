#pragma once

#include <string>


class TextBatch;

class Label
{
    TextBatch* textBatch;

    std::string text;
    int x, y;
    float r, g, b, a;

public:
    Label(TextBatch* textBatch);
    Label(TextBatch* textBatch, const std::string& text);
    Label(TextBatch* textBatch, const std::string& text, int x, int y);
    Label(const Label&);
    Label(Label&&) noexcept;
    ~Label() = default;

    void setText(const std::string& text) { this->text = text; }
    void setPosition(int x, int y) { this->x = x; this->y = y; }
    void setColor(float r, float g, float b, float a = 1.0) { this->r = r; this->g = g; this->b = b; this->a = a; }

    void render();

};