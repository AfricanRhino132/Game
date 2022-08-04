#pragma once
#include <cstdint>
#include <string>
#include <iostream>
namespace neu
{
	struct Color
	{
		uint8_t r, g, b, a;

		static const Color white;
		static const Color black;
		static const Color red;
		static const Color green;
		static const Color blue;
	};

	std::istream& operator >> (std::istream& stream, Color& color);
}