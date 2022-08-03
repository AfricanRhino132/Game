#include "Renderer.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

namespace neu
{
	void Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	}

	void Renderer::Shutdown()
	{
		SDL_DestroyRenderer(m_renderer);
		
		SDL_DestroyWindow(m_window);

		TTF_Quit();

		IMG_Quit();
	}

	void Renderer::CreateWindow(const char* name, int width, int height)
	{
		m_height = height;
		m_width = width;

		m_window = SDL_CreateWindow(name, 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(m_renderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}

	void Renderer::DrawPoint(float x1, float y1)
	{
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		SDL_RenderDrawPointF(m_renderer, x1, y1);
	}

	void Renderer::DrawPoint(const Vector2& v, const Color& color)
	{
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawPointF(m_renderer, v.x, v.y);
	}

	void Renderer::DrawLine(const Vector2& v1, const Vector2& v2, const Color& color)
	{
		SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
		SDL_RenderDrawLineF(m_renderer, v1.x, v1.y, v2.x, v2.y);
	}

	void Renderer::Draw(std::shared_ptr<Texture> texture, const Vector2& position, float angle)
	{
		Vector2 size = texture->GetSize();

		SDL_Rect dest;
		// !! make sure to cast to int to prevent compiler warnings 
		dest.x = (int)position.x;// !! set to position x 
		dest.y = (int)position.y;// !! set to position y 
		dest.w = (int)size.x;// !! set to size x 
		dest.h = (int)size.y;// !! set to size y 

		SDL_RenderCopyEx(m_renderer, texture->m_texture, nullptr, &dest, angle, nullptr, SDL_FLIP_NONE);
	}
}