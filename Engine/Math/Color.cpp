#include "Color.h"

namespace neu
{
	const Color Color::white{ 255, 255, 255, 255 };
	const Color Color::black{ 0, 0, 0, 255 };
	const Color Color::red{ 255, 0, 0, 255 };
	const Color Color::green{ 0, 255, 0, 255 };
	const Color Color::blue{ 0, 0, 255, 255 };

	std::istream& operator >> (std::istream& stream, Color& color)
	{
		std::string line;
		std::getline(stream, line);

		//{ #, #, # }
		color.r = (uint8_t)(std::stof(line.substr(line.find("{") + 1, line.find(","))) * 255.0f);
		color.g = (uint8_t)(std::stof(line.substr(line.find(",") + 1, line.find_last_of(","))) * 255.0f);
		color.b = (uint8_t)(std::stof(line.substr(line.find_last_of(",") + 1, line.find("}"))) * 255.0f);
		color.a = (uint8_t)255;

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)color.a;

		return stream;
	}
}