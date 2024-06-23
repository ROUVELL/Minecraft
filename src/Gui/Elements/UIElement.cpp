#include "UIElement.hpp"

#include "../UIManager.hpp"


UIElement::UIElement() noexcept
{
    UIManager::_register(this);
}

bool UIElement::inside(uipos_t point) const noexcept
{
    const i16 left = rect.position.x;
    const i16 right = left + rect.size.w;
    const i16 top = rect.position.y;
    const i16 bottom = top + rect.size.h;

    if (left < point.x && point.x < right && top < point.y && point.y < bottom)
        return true;
    
    return false;
}