#include "stdafx.h"
#include <sstream>
#include "FunctionList.h"
#include "StdFunctions.h"
#include "Transformation.h"
using namespace lang;

std::vector<Function*> FunctionList::knownFunctions({
	new Sin,
	new Cos,
	new Tg,
	new Ctg,
	new Ln,
	new Lg,
	new Log,
	new Exp,
	new Abs,
	new Pow
});

Function* FunctionList::GetFunction(const std::string& name, const size_t argCount)
{
	// ����������� ��� ������� � ������ ������� ������ ��� ������ ���.
	std::string lowerName = ToLower(name);

	// ���� �� ����� ������� � ����� ������ ��� ����� ���������� �� ������� � ������� ����������.
	// ���� �� ����, ���������� ��������� �� ��������������� ������ Function.
	for each (auto& pFunc in knownFunctions)
		if (lowerName == pFunc->GetNameInLowerCase()) {
			if (argCount == pFunc->GetArgumentCount())
				return pFunc;

			throw std::exception((
					std::string("�������������� ����� ���������� � ������� \"") + lowerName
					+ "\": ��������� " + ToString(pFunc->GetArgumentCount()) + ", ������� " + ToString(argCount)
				).c_str());
		}

	throw std::exception((std::string("���������� ����������� ������� \"") + lowerName + '\"').c_str());
}
