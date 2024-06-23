#pragma once

#include <functional>

#include "../../typedefs.hpp"


class UIBatch;
class UIElement;

using uihandler_t = std::function<void(UIElement* const)>;

/* Size of the ui element */
struct uisize_t
{
    u16 w = 0;
    u16 h = 0;
};

/* Ui element position on screen (top-left corner) */
struct uipos_t
{
    i16 x = 0;
    i16 y = 0;
};

/* Ui rect (position and size) */
struct uirect_t
{
    uipos_t position;
    uisize_t size;
};


/* Abstract class of all ui elements */
class UIElement
{
protected:
    uirect_t rect;

public:
    UIElement() noexcept;
    virtual ~UIElement() = default;

    virtual bool inside(uipos_t point) const noexcept;

    /* Get rect (position and size) of the element */
    virtual uirect_t getRect() const noexcept { return rect; }
    /* Get top-left corner position of the element */
    virtual uisize_t getSize() const noexcept { return rect.size; }
    /* Get size of the element */
    virtual uipos_t getPosition() const noexcept { return rect.position; }

    /* Set new size */
    virtual void setSize(uisize_t newSize) noexcept { rect.size = newSize; }
    /* Set new position */
    virtual void setPosition(uipos_t newPos) noexcept { rect.position = newPos; }

    /* Input handlers */
    virtual void on_mouse_button_pressed(u32 /* button */, f32 /* x */, f32 /* y */, u32 /* mods */) noexcept {  }
    virtual void on_mouse_button_released(u32 /* button */, f32 /* x */, f32 /* y */, u32 /* mods */) noexcept {  }
    virtual void on_mouse_move(f32 /* x */, f32 /* y */) noexcept {  }
    virtual void on_key_pressed(u32 /* key */, u32 /* mods */) noexcept {  }
    virtual void on_key_released(u32 /* key */, u32 /* mods */) noexcept {  }
    virtual void on_text_enter(u32 /* codepoint */) noexcept {  }

    /* Render element */
    virtual void render(const UIBatch&) const noexcept = 0;
};