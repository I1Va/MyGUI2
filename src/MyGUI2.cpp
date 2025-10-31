#include "MyGUI2.hpp"

namespace hui {

class GTexture : dr4::Texture {
    char *bufer;
    // sizes;
};


Widget::Widget
(   
    const std::size_t width, const std::size_t height, 
    State *const state, Widget *parent
) :
    relPos(0, 0),
    parent(parent),
    state(state),
    texture(nullptr),
    textureIsInvalid(true)
{
    
}



}


