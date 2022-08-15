#include "Texture.h" 
#include "Renderer.h" 
#include "Core/Logger.h"

#include <SDL.h> 
#include <SDL_image.h> 

namespace neu
{
    Texture::~Texture()
    {
        // !! if texture not null SDL_DestroyTexture 
        if (m_texture)
        {
            SDL_DestroyTexture(m_texture);
        }
        
    }

    bool Texture::Create(std::string name, ...)
    {
        // va_list - type to hold information about variable arguments 
        va_list args;

        // va_start - enables access to variadic function arguments 
        va_start(args, name);

        // va_arg - accesses the next variadic function arguments 
        Renderer& renderer = va_arg(args, Renderer);

        // va_end - ends traversal of the variadic function arguments 
        va_end(args);

        // create texture (returns true/false if successful) 
        return Create(renderer, name);
    }

    bool Texture::Create(Renderer& renderer, const std::string& filename)
    {
        // load surface 
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            LOG(SDL_GetError());
            return false;
        }
        // create texture 
        // !! call SDL_CreateTextureFromSurface passing in renderer and surface 
        // !! the first parameter takes in the m_renderer from renderer 
        m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
        if (!m_texture)
        {
            LOG(SDL_GetError());
            SDL_FreeSurface(surface);
            return false;
        }
        // !! call SDL_FreeSurface with surface as the parameter 
        SDL_FreeSurface(surface);
        // !! no need to keep surface after texture is created 

        return true;
    }

    neu::Vector2 Texture::GetSize() const
    {
        SDL_Point point;
        SDL_QueryTexture(m_texture, nullptr, nullptr, &point.x, &point.y);

        return { point.x, point.y };// !! return Vector2 of point.x, point.y 
    }
}
