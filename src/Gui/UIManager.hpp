#pragma once

#include <vector>


class AssetsLoader;
class UIBatch;
class UIElement;

class UIManager
{
    static std::vector<UIElement*> elements;

    UIBatch* const uiBatch;

public:
    UIManager(UIBatch* const textBatch) noexcept : uiBatch(textBatch) {  }
    UIManager(const UIManager&) = delete;
    UIManager(UIManager&&) = delete;
    ~UIManager() = default;

    static void _register(UIElement* element) noexcept { elements.push_back(element); }

    void process_input() noexcept;
    void render(AssetsLoader& assets) noexcept;
};