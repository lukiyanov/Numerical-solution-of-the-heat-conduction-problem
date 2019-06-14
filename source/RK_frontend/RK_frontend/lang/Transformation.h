#pragma once
#include <string>
#include <sstream>

namespace lang {

	template <typename T>
	inline std::string ToString(T val)
	{
		std::ostringstream oss;
		oss << val;
		return oss.str();
	}

	inline const std::string ToLower(const std::string& str)
	{
		size_t size = str.size();
		std::string lowercaseStr(size, ' ');
		for (size_t i = 0; i < size; i++)
			lowercaseStr[i] = tolower(str[i]);
		return lowercaseStr;
	}

}