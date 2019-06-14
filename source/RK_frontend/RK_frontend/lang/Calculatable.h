#pragma once
#include "Variant.h"
#include "VariableList.h"
#include "FunctionList.h"

namespace lang {

	enum class ExpressionType { Double, Bool };

	class Calculatable {
	public:
		virtual ~Calculatable() {}
		virtual const Variant Calculate() = 0;
		virtual void ReportIDs(VariableList& vars) {}	// В этой функции нужно сообщать о том что мы - ID
		virtual void ResolveIDs(VariableList& vars) {}	// В этой функции нужно получать указатель на нашу переменную, если мы ID
		virtual void ResolveFuncs(FunctionList& funcs) {}	// В этой функции нужно сообщать о том что мы - функция
	};
}