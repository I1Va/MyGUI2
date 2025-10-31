#pragma once


#include "dr4/window.hpp"
#include <SDL2/SDL.h>
#include <string>

namespace gr {

class Window : public dr4::Window {
    SDL_Renderer *renderer_ = nullptr;
    SDL_Window *window_ = nullptr;
    std::string title_;
    dr4::Vec2f size_;
    bool isOpen_ = false;

public:
    Window
    (
        const std::string &title,
        const int width,
        const int height
    ) : title_(title), size_(width, height)
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            printf("SDL_Init Error: %s\n", SDL_GetError());
            // return 1;
        }

        window_ = SDL_CreateWindow(
            title_.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            size_.x, size_.y,
            SDL_WINDOW_HIDDEN
        );

        if (!window_) {
            printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
            SDL_Quit();
            // return 1;
        }

        renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer_) {
            printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(window_);
            SDL_Quit();
            // return 1;
        }
    }

    ~Window() {
        if (renderer_) SDL_DestroyRenderer(renderer_);
        if (window_) SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    void SetTitle(const std::string &title) override { title_ = title; }
    const std::string &GetTitle() const override { return title_; }
    dr4::Vec2f GetSize() const override { return size_; };

    void Open() override { 
        SDL_ShowWindow(window_);
        isOpen_ = true;
    };
    bool IsOpen() const override { return isOpen_; }
    void Close() override { SDL_HideWindow(window_); }

    void Clear(const dr4::Color &color) override {};
    void Draw(const dr4::Texture &texture, dr4::Vec2f pos) override {}
    void Display() override { SDL_RenderPresent(renderer_); }

    std::optional<dr4::Event> PollEvent() override {
        SDL_Event SDLEvent{};
        dr4::Event dr4Event{};
        static int prevMouseX = 0, prevMouseY = 0;

        if (!SDL_PollEvent(&SDLEvent)) return std::nullopt;
        switch (SDLEvent.type) {
            case SDL_QUIT:
                dr4Event.type = dr4::Event::Type::QUIT;
                return dr4Event;
            
            case SDL_KEYDOWN:
                dr4Event.type = dr4::Event::Type::KEY_DOWN;
                dr4Event.keyDown.sym   = SDLEvent.key.keysym.sym;
                dr4Event.keyDown.mod   = SDLEvent.key.keysym.mod;
                return dr4Event;
            
            case SDL_KEYUP:
                dr4Event.type = dr4::Event::Type::KEY_UP;
                dr4Event.keyDown.sym   = SDLEvent.key.keysym.sym;
                dr4Event.keyDown.mod   = SDLEvent.key.keysym.mod;
                return dr4Event;
                
            case SDL_MOUSEWHEEL:
            {
                int mouseX = 0, mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);

                dr4Event.type = dr4::Event::Type::MOUSE_WHEEL;
                dr4Event.mouseWheel.pos = dr4::Vec2f(mouseX, mouseY);
                dr4Event.mouseWheel.delta = dr4::Vec2f(SDLEvent.wheel.x, SDLEvent.wheel.y);
                return dr4Event;
            }
        
            case SDL_MOUSEBUTTONDOWN:
                dr4Event.type = dr4::Event::Type::MOUSE_DOWN;
                dr4Event.mouseDown.button = SDLEvent.button.button;
                dr4Event.mouseDown.pos = dr4::Vec2f(SDLEvent.button.x, SDLEvent.button.y);
                dr4Event.mouseDown.pressed = true;
                return dr4Event;

            case SDL_MOUSEBUTTONUP:
                dr4Event.type = dr4::Event::Type::MOUSE_DOWN;
                dr4Event.mouseDown.button = SDLEvent.button.button;
                dr4Event.mouseDown.pos = dr4::Vec2f(SDLEvent.button.x, SDLEvent.button.y);
                dr4Event.mouseDown.pressed = false;
                return dr4Event;
            
            case SDL_MOUSEMOTION:
            {
                int mouseX = 0, mouseY = 0;
                SDL_GetMouseState(&mouseX, &mouseY);
                
                dr4Event.type = dr4::Event::Type::MOUSE_MOVE;
                dr4Event.mouseMove.pos = dr4::Vec2f(mouseX, mouseY);
                dr4Event.mouseMove.rel = dr4::Vec2f(mouseX - prevMouseX, mouseY - prevMouseY);

                return dr4Event;
            }    

            default:
                break;
        }
        SDL_GetMouseState(&prevMouseX, &prevMouseY);
        return std::nullopt;
    }
};

}