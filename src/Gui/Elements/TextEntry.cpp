#include "TextEntry.hpp"

#include "../../Window/keys.hpp"
#include "../../Graphics/UIBatch.hpp"


inline constexpr color_t bgColor{ 20, 220 };
inline constexpr color_t focusedBgColor{ 20, 150 };


void TextEntry::on_mouse_button_pressed(u32 button, f32, f32, u32) noexcept
{
    isFocused = (button == MOUSE_BUTTON_LEFT && isHover);
}

void TextEntry::on_mouse_move(f32 x, f32 y) noexcept
{
    isHover = inside(uipos_t{ (i16)x, (i16)y });
}

void TextEntry::on_key_pressed(u32 key, u32) noexcept
{
    if (!isFocused)
        return;

    if (key == KEY_BACKSPACE && !text.empty())
        text.pop_back();
    else if (key == KEY_ENTER && !text.empty())
        handler(this);
}

void TextEntry::on_text_enter(u32 codepoint) noexcept
{
    if (!isFocused)
        return;

    if (text.length() < maxLenght)
        text += (u8)codepoint;
}

void TextEntry::render(const UIBatch& uiBatch) const noexcept
{
    const auto [x, y] = rect.position;
    const auto [w, h] = rect.size;

    if (text.empty())
        uiBatch.text(placeholder, x + 10, y + 5, color_t{ 200, 150 });
    else
        uiBatch.text(text, x + 10, y + 5, colors::WHITE);

    uiBatch.rect(x, y, w, h, colors::WHITE);
    uiBatch.frect(x, y, w, h, isFocused ? focusedBgColor : bgColor);
}