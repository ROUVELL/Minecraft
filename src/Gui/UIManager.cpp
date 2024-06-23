#include "UIManager.hpp"

#include "../Window/Events.hpp"

#include "Elements/UIElement.hpp"
#include "../Graphics/UIBatch.hpp"


std::vector<UIElement*> UIManager::elements;

void UIManager::process_input() noexcept
{
    if (Events::cursorLocked())
    {
        while (!Events::_queue.empty())
            Events::_queue.pop();

        return;
    }

    while (!Events::_queue.empty())
    {
        const event_t event = Events::_queue.front();
        Events::_queue.pop();

        for (const auto element : elements)
        {
            switch (event.type)
            {
            case EventType::KEY_PRESSED:
                element->on_key_pressed(event.key, event.mods);
                break;

            case EventType::KEY_RELEASED:
                element->on_key_released(event.key, event.mods);
                break;

            case EventType::MOUSE_BUTTON_PRESSED:
                element->on_mouse_button_pressed(event.button, event.x, event.y, event.mods);
                break;

            case EventType::MOUSE_BUTTON_RELEASED:
                element->on_mouse_button_released(event.button, event.x, event.y, event.mods);
                break;

            case EventType::MOUSE_MOVED:
                element->on_mouse_move(event.x, event.y);
                break;
            
            case EventType::TEXT_ENTER:
                element->on_text_enter(event.codepoint);
                break;
            }
        }
    }
}

void UIManager::render(AssetsLoader& assets) noexcept
{
    for (const auto element : elements)
        element->render(*uiBatch);

    uiBatch->render(assets);
}