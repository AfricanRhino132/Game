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

	bool Font::Create(const std::string& name, void* data)
	{
		int* fontSize = static_cast<int*>(data);

		if (fontSize)
		{
			Load(name, *fontSize);
			return true;
		}

		return false;
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		// !! call TTF_OpenFont  
		TTF_Init();
		m_ttfFont = TTF_OpenFont(filename.c_str(), fontSize);
		// !! use filename.c_str() to get the c-style string 
		// !! assign the return value of TTF_OpenFont to m_ttfFont 
	}
}