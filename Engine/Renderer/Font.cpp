#include "Font.h" 

#include <SDL_ttf.h> 
#include <iostream>


namespace neu
{
	Font::Font(const std::string& filename, int fontSize)
	{
		// !! call Load() function below passing filename and fontSize 
		Load(filename, fontSize);
		
	}

	Font::~Font()
	{
		// !! if m_ttfFont not null, close font (TTF_CloseFont) 
		if (m_ttfFont)
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	bool Font::Create(std::string name, ...)
	{

		va_list args;

		va_start(args, name);

		int fontSize = va_arg(args, int);

		va_end(args);
		
		return Load(name, fontSize);
	}

	bool Font::Load(const std::string& filename, int fontSize)
	{
		// !! call TTF_OpenFont  
		TTF_Init();
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);

		return m_ttfFont;
		// !! use filename.c_str() to get the c-style string 
		// !! assign the return value of TTF_OpenFont to m_ttfFont 
	}
}