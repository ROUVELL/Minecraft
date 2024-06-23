#pragma once

#include <string>

#include "UIElement.hpp"


class Button : public UIElement
{
    std::string text = "Button";
    uihandler_t handler = [](UIElement* const) -> void { };

    bool isHover = false;
    bool isPressed = false;

public:
    Button() = default;
    Button(const Button&) = default;
    Button(Button&&) = default;
    ~Button() = default;

    void setText(const std::string& newText) noexcept { text = newText; }
    void setHandler(uihandler_t newHandler) noexcept { handler = newHandler; }

    void autoResize() noexcept { setSize({ (u16)(text.length() * 8 + 20), 30 }); }

    void on_mouse_button_pressed(u32 button, f32, f32, u32) noexcept override;
    void on_mouse_button_released(u32 button, f32, f32, u32) noexcept override;
    void on_mouse_move(f32 x, f32 y) noexcept override;

    void render(const UIBatch& uiBatch) const noexcept override;
};
