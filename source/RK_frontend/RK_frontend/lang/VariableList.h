#pragma once
#include <map>
#include <vector>
#include "Variant.h"
#include "Transformation.h"

namespace lang {

	class VariableList {
	public:
		void AddVariable(const std::string& name)
		{
			m_mapNamesToIndexes[ToLower(name)] = 0;
		}

		// ����� ��� ��� ����������� ���������� ������ ���� ��������� ��������� ������ �� ����� ����� AddVariable(),
		// ����� ���� ������� ������ ������� BuildVariables().
		void BuildVariables()
		{
			int pos = 0;
			for (auto i = m_mapNamesToIndexes.begin(); i != m_mapNamesToIndexes.end(); ++i)
				(*i).second = pos++;

			m_vctActualValues.resize(m_mapNamesToIndexes.size(), { 0 });
		}

		// ����� ���������� �� ��������� �������� � ���� ����������, ��� ���������.
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		Variant* GetVariable(const std::string& name)
		{
			return &(m_vctActualValues[m_mapNamesToIndexes[ToLower(name)]]);
		}

		// ��������� ���������� � ��������� �������� �� � �����
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		void SetVariable(const std::string& name, const double value)
		{
			m_vctActualValues[m_mapNamesToIndexes[ToLower(name)]].doubleValue = value;
		}

		// ��������� ���������� � ��������� �������� �� � UID
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		void SetVariable(const int UID, const double value)
		{
			m_vctActualValues[UID].doubleValue = value;
		}

		// ��������� UID ���������� �� � �����
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		int GetVariableUID(const std::string& name)
		{
			return m_mapNamesToIndexes[ToLower(name)];
		}

		// ���������� ���������� ����������
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		size_t GetVariableCount()
		{
			return m_vctActualValues.size();
		}

		// ���������� ����� ���������� �� �������, ���������������� �� UID.
		// �������� ����������� ��������, ����� �� �������� � �����.
		// ������ ������� ����� ���� ������� ������ ����� BuildVariables().
		void GetVariableNames(std::vector<std::string>& names)
		{
			names.resize(m_vctActualValues.size());

			int pos = 0;
			for (auto i = m_mapNamesToIndexes.begin(); i != m_mapNamesToIndexes.end(); ++i)
				names[pos++] = (*i).first;
		}

	private:
		std::map<std::string, int> m_mapNamesToIndexes;
		std::vector<Variant> m_vctActualValues;
	};

}