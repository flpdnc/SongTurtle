#include "player.h"

Player::Player(SDL_Renderer* renderer)
    : m_renderer(renderer) {
    m_rect = {100, 500, 50, 50};
}

void Player::update(float frequency) {
    // Update the player's position based on the frequency
    // You might need to adjust the values for better gameplay
    if (frequency > 0) {
        m_rect.x = static_cast<int>((frequency - 130.81) * (800 - 50) / (261.63 - 130.81));
    }
}

void Player::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(m_renderer, &m_rect);
}

SDL_Rect Player::getRect() const {
    return m_rect;
}

