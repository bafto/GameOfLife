#pragma once

#include "SFML/Graphics.hpp"
#include <unordered_set>

namespace std
{
	template<typename T>
	struct hash<sf::Vector2<T>>
	{
		static_assert(!std::is_same_v<T, float>, "You cannot hash floats");
		std::size_t operator()(const sf::Vector2<T>& v) const
		{
			//hash the individual values
			std::size_t temp0 = std::hash<T>()(v.x);
			std::size_t temp1 = std::hash<T>()(v.y);

			//combine the hashes with black magic
			temp0 ^= temp1 + 0x9e3779b9 + (temp0 << 6) + (temp0 >> 2);
			return temp0;
		}
	};
}