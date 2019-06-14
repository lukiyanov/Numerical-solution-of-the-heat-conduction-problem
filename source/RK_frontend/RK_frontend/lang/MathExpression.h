#pragma once
#include "Calculatable.h"
#include "VariableList.h"
#include "FunctionList.h"
#include <vector>
#include <string>

namespace lang
{
	class Function;

	// Корневой класс всей библиотеки lang.
	// Математическое выражение, которое мы считываем в текстовом виде.
	// Мы можем вычислить его динамически, подставив неизвестные переменные.
	class MathExpression
	{
	public:
		// Создаёт экземпляр класса, парся переданную строку.
		// Все неопознанные идентификаторы признаются переменными.
		// Генерит исключения класса std::exception.
		MathExpression(const std::string& expressionStringToParse);

		// Возвращает список имён переменных по порядку.
		void GetVariableNames(std::vector<std::string>& names);

		// Подставляет значения переменных в выражение, вычисляет его и возвращает результат.
		// Параметром должен быть массив из GetVariableCount() элементов.
		// Переменные могут быть только типа double.
		Variant Calculate(double *args);

		// Возвращает тип выражения
		ExpressionType GetType() { return m_type; }

		// Возвращает количество переменных
		size_t GetVariableCount() { return m_nVariableCount; }

	private:
		Calculatable *m_pRoot;
		ExpressionType m_type;
		size_t m_nVariableCount;

		VariableList m_vars;
		FunctionList m_funcs;
	};

}