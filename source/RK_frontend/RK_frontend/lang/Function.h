#pragma once
#include "Variant.h"

namespace lang {
	class Function {
	public:
		virtual const char * GetNameInLowerCase() const = 0;
		virtual int GetArgumentCount() const = 0;
		virtual Variant Calculate(const double* arguments) const = 0;
	};
}