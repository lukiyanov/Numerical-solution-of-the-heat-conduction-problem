#pragma once
#include "Function.h"
#include <cmath>

namespace lang {

	class Sin : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "sin"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::sin(arguments[0]) }; }
	};

	class Cos : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "cos"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::cos(arguments[0]) }; }
	};

	class Tg : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "tg"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::tan(arguments[0]) }; }
	};

	class Ctg : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "ctg"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ 1.0 / std::tan(arguments[0]) }; }
	};

	// Логарифм по основанию e
	class Ln : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "ln"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::log(arguments[0]) }; }
	};

	// Логарифм по основанию 10
	class Lg : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "lg"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::log10(arguments[0]) }; }
	};

	// Логарифм с заданным основанием
	class Log : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "log"; }
		int GetArgumentCount() const override { return 2; }
		// [0] - основание, [1] - само выражение
		Variant Calculate(const double* arguments) const override { return{ std::log(arguments[0]) / std::log(arguments[1]) }; }
	};

	// e^x
	class Exp : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "exp"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::exp(arguments[0]) }; }
	};

	// |x|
	class Abs : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "abs"; }
		int GetArgumentCount() const override { return 1; }
		Variant Calculate(const double* arguments) const override { return{ std::abs(arguments[0]) }; }
	};

	// x^y
	class Pow : public Function
	{
	public:
		const char * GetNameInLowerCase() const override { return "pow"; }
		int GetArgumentCount() const override { return 2; }
		Variant Calculate(const double* arguments) const override { return{ std::pow(arguments[0], arguments[1]) }; }
	};

}