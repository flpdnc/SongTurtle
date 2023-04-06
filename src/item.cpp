#include "item.h"

Item::Item(SDL_Renderer* renderer, int x, int y)
    : m_renderer(renderer) {
    m_rect = {x, y, 25, 25};
}

void Item::update() {
    // Update the item's position
    m_rect.y += 5;
}

void Item::render() const {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);
}

bool Item::isOffScreen() const {
    return m_rect.y > 600;
}

SDL_Rect Item::getRect() const {
    return m_rect;
}

