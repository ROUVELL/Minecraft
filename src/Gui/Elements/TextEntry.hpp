#pragma once

#include <string>

#include "UIElement.hpp"


class TextEntry : public UIElement
{
    std::string text = "";
    std::string placeholder = "Type...";

    u8 maxLenght = 255;

    uihandler_t handler = [](UIElement* const) -> void { };  // called on enter pressed

    bool isHover = false;
    bool isFocused = false;

public:
    TextEntry() = default;
    TextEntry(const TextEntry&) = default;
    TextEntry(TextEntry&&) = default;
    ~TextEntry() = default;

    std::string getText() const noexcept { return text; }

    void setText(const std::string& newText) noexcept { text = newText; }
    void setPlaceholder(const std::string& newPlaceholder) noexcept { placeholder = newPlaceholder; }
    void setMaxLenght(u8 newMaxLenght) noexcept { maxLenght = newMaxLenght; }
    void setHandler(uihandler_t newHandler) noexcept { handler = newHandler; }

    void clear() noexcept { text.clear(); }

    void on_mouse_button_pressed(u32 button, f32, f32, u32) noexcept override;
    void on_mouse_move(f32 x, f32 y) noexcept override;
    void on_key_pressed(u32 key, u32) noexcept override;
    void on_text_enter(u32 codepoint) noexcept override;

    void render(const UIBatch& uiBatch) const noexcept override;
};