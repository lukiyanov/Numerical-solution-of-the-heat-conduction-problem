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
		virtual void ReportIDs(VariableList& vars) {}	// � ���� ������� ����� �������� � ��� ��� �� - ID
		virtual void ResolveIDs(VariableList& vars) {}	// � ���� ������� ����� �������� ��������� �� ���� ����������, ���� �� ID
		virtual void ResolveFuncs(FunctionList& funcs) {}	// � ���� ������� ����� �������� � ��� ��� �� - �������
	};
}