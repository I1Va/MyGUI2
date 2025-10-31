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

    std::optional<dr4::Event> PollEvent() override { return std::nullopt; }

    // переорпделения 
};

}