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
	// Преобразуем имя функции в нижний регистр прежде чем искать его.
	std::string lowerName = ToLower(name);

	// Если не нашли функцию с таким именем или число аргументов не совпало — генерим исключение.
	// Если всё норм, возвращаем указатель на соответствующий объект Function.
	for each (auto& pFunc in knownFunctions)
		if (lowerName == pFunc->GetNameInLowerCase()) {
			if (argCount == pFunc->GetArgumentCount())
				return pFunc;

			throw std::exception((
					std::string("Несоответствие числа аргументов в функции \"") + lowerName
					+ "\": ожидается " + ToString(pFunc->GetArgumentCount()) + ", найдено " + ToString(argCount)
				).c_str());
		}

	throw std::exception((std::string("Обнаружена неизвестная функция \"") + lowerName + '\"').c_str());
}
