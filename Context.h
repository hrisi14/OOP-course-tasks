#pragma once
#include "Pair.hpp"

namespace GlobalConstants
{
	constexpr unsigned MAX_NUMBERS = 32;
	constexpr unsigned MAX_BUFF = 1024;
	constexpr char SEPARATOR = '\0';
}


class Context   //similar to an interface
{
public:
	virtual Pair<bool, int> operator()(int x) const = 0;
	virtual Context* clone() const = 0;
	virtual ~Context() = default;
};

