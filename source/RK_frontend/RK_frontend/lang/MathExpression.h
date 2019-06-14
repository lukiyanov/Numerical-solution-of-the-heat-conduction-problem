#pragma once
#include "Calculatable.h"
#include "VariableList.h"
#include "FunctionList.h"
#include <vector>
#include <string>

namespace lang
{
	class Function;

	// �������� ����� ���� ���������� lang.
	// �������������� ���������, ������� �� ��������� � ��������� ����.
	// �� ����� ��������� ��� �����������, ��������� ����������� ����������.
	class MathExpression
	{
	public:
		// ������ ��������� ������, ����� ���������� ������.
		// ��� ������������ �������������� ���������� �����������.
		// ������� ���������� ������ std::exception.
		MathExpression(const std::string& expressionStringToParse);

		// ���������� ������ ��� ���������� �� �������.
		void GetVariableNames(std::vector<std::string>& names);

		// ����������� �������� ���������� � ���������, ��������� ��� � ���������� ���������.
		// ���������� ������ ���� ������ �� GetVariableCount() ���������.
		// ���������� ����� ���� ������ ���� double.
		Variant Calculate(double *args);

		// ���������� ��� ���������
		ExpressionType GetType() { return m_type; }

		// ���������� ���������� ����������
		size_t GetVariableCount() { return m_nVariableCount; }

	private:
		Calculatable *m_pRoot;
		ExpressionType m_type;
		size_t m_nVariableCount;

		VariableList m_vars;
		FunctionList m_funcs;
	};

}