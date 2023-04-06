#include <SDL.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "item.h"
#include "audio.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Audio Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    AudioInput audioInput;
    audioInput.startCapture();

    Player player(renderer);
    std::vector<Item> items;

    std::srand(std::time(nullptr));

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

/*        // Update game objects and check for collisions
        float frequency = audioInput.getPrimaryFrequency();
        player.update(frequency);

        for (auto& item : items) {
            item.update();
            if (SDL_HasIntersection(&player.getRect(), &item.getRect())) {
                // Handle item collection here, e.g., increment score
                item = items.back();
                items.pop_back();
            }
        }
*/
	// Update game objects and check for collisions
        float frequency = audioInput.getPrimaryFrequency();
        player.update(frequency);

        for (auto& item : items) {
            item.update();
            SDL_Rect playerRect = player.getRect();
            SDL_Rect itemRect = item.getRect();
            if (SDL_HasIntersection(&playerRect, &itemRect)) {
                // Handle item collection here, e.g., increment score
                item = items.back();
                items.pop_back();
            }
        }


        // Remove off-screen items
        items.erase(std::remove_if(items.begin(), items.end(),
                                   [](const Item& item) { return item.isOffScreen(); }),
                    items.end());

        // Generate new items periodically
        if (std::rand() % 100 < 3) {  // Adjust the probability for better gameplay
            int x = std::rand() % (800 - 25);
            items.emplace_back(renderer, x, 0);
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Render game objects
        player.render();
        for (const auto& item : items) {
            item.render();
        }

        // Update the screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16);  // Approximately 60 FPS
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

