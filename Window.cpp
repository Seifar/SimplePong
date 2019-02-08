//
// Created by Thomas Frank on 2019-02-07.
//

#include "Window.h"

Window::Window() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface* screen = SDL_SetVideoMode(800, 600, 32, SDL_DOUBLEBUF);
}

Window::~Window() {
}
