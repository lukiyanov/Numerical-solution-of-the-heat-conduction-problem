#pragma once
#include <exception>
#include <string>
#include "BaseErrorListener.h"
#include "Transformation.h"

namespace lang
{
	class LangErrorListener : public antlr4::BaseErrorListener {
	public:
		void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token * offendingSymbol,
			size_t line, size_t charPositionInLine,
			const std::string &msg, std::exception_ptr e)
		{
			throw std::exception(
				(std::string("Ошибка в выражении, строка ") + ToString(line) + ", символ " +
				ToString(charPositionInLine) + ": " + msg).c_str()
			);
		}
	};
}