#pragma once
#include <vector>
#include <string>
#include "Function.h"

namespace lang
{

	class FunctionList
	{
		static std::vector<Function*> knownFunctions;
	public:
		Function* GetFunction(const std::string& name, const size_t argCount);
	};

}