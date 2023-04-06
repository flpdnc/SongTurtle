#ifndef ITEM_H
#define ITEM_H

#include <SDL.h>

class Item {
public:
    Item(SDL_Renderer* renderer, int x, int y);
    void update();
    void render() const;
    bool isOffScreen() const;
    SDL_Rect getRect() const;

private:
    SDL_Renderer* m_renderer;
    SDL_Rect m_rect;
};

#endif // ITEM_H

