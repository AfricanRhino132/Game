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

    bool Texture::Create(const std::string& name, void* data)
    {
        
        if (data)
        {
            return Create(*static_cast<Renderer*>(data), name);
        }

        return false;
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
