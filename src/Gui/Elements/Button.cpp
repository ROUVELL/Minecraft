#include "Button.hpp"

#include "../../Window/keys.hpp"
#include "../../Graphics/UIBatch.hpp"


inline constexpr color_t textColor = { 255 };
inline constexpr color_t bgColor = { 30, 100 };
inline constexpr color_t borderColor = colors::WHITE;

inline constexpr color_t hoverTextColor = { 230 };
inline constexpr color_t hoverBgColor = { 20, 100 };
inline constexpr color_t hoverBorderColor = { 230 };

inline constexpr color_t pressedTextColor = { 200 };
inline constexpr color_t pressedBgColor = { 0, 100 };
inline constexpr color_t pressedBorderColor = { 200 };

void Button::on_mouse_button_pressed(u32 button, f32, f32, u32) noexcept
{
    isPressed = button == MOUSE_BUTTON_LEFT && isHover && !isPressed;
}

void Button::on_mouse_button_released(u32 button, f32, f32, u32) noexcept
{
    if (isPressed && button == MOUSE_BUTTON_LEFT)
    {
        handler(this);
        isPressed = false;
    }
}

void Button::on_mouse_move(f32 x, f32 y) noexcept
{
    if (inside(uipos_t{ (i16)x, (i16)y }))
    {
        isHover = true;
    }
    else
    {
        isHover = false;
        isPressed = false;
    }
}

void Button::render(const UIBatch& uiBatch) const noexcept
{
    const auto [x, y] = rect.position;
    const auto [w, h] = rect.size;

    uiBatch.text(text, x + 10, y + 5, isPressed ? pressedTextColor : isHover ? hoverTextColor : textColor);

    uiBatch.rect(x, y, w, h, isPressed ? pressedBorderColor : isHover ? hoverBorderColor : borderColor);
    uiBatch.frect(x, y, w, h, isPressed ? pressedBgColor : isHover ? hoverBgColor : bgColor);
}