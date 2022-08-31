#pragma once

#include <functional>
#include <string>
#include <variant>

namespace neu
{
	class GameObject;

	struct Event
	{
	public:
		using functionPtr = std::function<void(const Event&)>;

	public:
		std::string name;
		GameObject* receiver = nullptr;
		std::variant<int, bool, float, std::string> data;
	};

	class INotify
	{
	public:
		virtual void OnNotify(const Event& event) = 0;
	};
}