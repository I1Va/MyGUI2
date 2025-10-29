#ifndef I_HUI_WINDOW
#define I_HUI_WINDOW

#include <string>
#include <optional>

#include "dr4/event.hpp"
#include "dr4/math/color.hpp"
#include "dr4/math/vec2.hpp"
#include "dr4/texture.hpp"

namespace dr4 {

class Window {

    // Texture field

public:

    virtual void SetTitle(const std::string &title) = 0;
    virtual const std::string &GetTitle() const = 0;

    virtual Vec2f GetSize() const = 0;

    virtual void Open() = 0;
    virtual bool IsOpen() const = 0;
    virtual void Close() = 0;

    virtual void Clear(const Color &color) = 0;

    virtual void Draw(const Drawable &object) = 0;
    virtual void Draw(const Texture &texture, Vec2f pos) = 0;

    virtual void Display() = 0;

    virtual std::optional<Event> PollEvent() = 0;
};

}; // namespace dr4

#endif // I_HUI_WINDOW
