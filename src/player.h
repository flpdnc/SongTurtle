#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    Player(SDL_Renderer* renderer);
    void update(float frequency);
    void render();
    SDL_Rect getRect() const;

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
};

#endif // PLAYER_H

