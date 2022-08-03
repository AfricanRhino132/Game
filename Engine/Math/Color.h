#pragma once
#include <cstdint>

#include <iostream>
namespace neu
{
	struct Color
	{
		uint8_t r, g, b, a;
	};

	inline std::istream& operator >> (std::istream& stream, Color& color)
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
}