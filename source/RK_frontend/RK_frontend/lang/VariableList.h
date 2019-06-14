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

		// Перед тем как запрашивать переменные должна быть полностью завершена стадия их сбора через AddVariable(),
		// после чего вызвана данная функция BuildVariables().
		void BuildVariables()
		{
			int pos = 0;
			for (auto i = m_mapNamesToIndexes.begin(); i != m_mapNamesToIndexes.end(); ++i)
				(*i).second = pos++;

			m_vctActualValues.resize(m_mapNamesToIndexes.size(), { 0 });
		}

		// Может вызываться ДО установки значения в сами переменные, это нормально.
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
		Variant* GetVariable(const std::string& name)
		{
			return &(m_vctActualValues[m_mapNamesToIndexes[ToLower(name)]]);
		}

		// Установка переменной в выбранное значение по её имени
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
		void SetVariable(const std::string& name, const double value)
		{
			m_vctActualValues[m_mapNamesToIndexes[ToLower(name)]].doubleValue = value;
		}

		// Установка переменной в выбранное значение по её UID
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
		void SetVariable(const int UID, const double value)
		{
			m_vctActualValues[UID].doubleValue = value;
		}

		// Получение UID переменной по её имени
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
		int GetVariableUID(const std::string& name)
		{
			return m_mapNamesToIndexes[ToLower(name)];
		}

		// Возвращает количество переменных
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
		size_t GetVariableCount()
		{
			return m_vctActualValues.size();
		}

		// Возвращает имена переменных по порядку, соответствующему их UID.
		// Довольно ресурсоёмкая операция, лучше не вызывать её часто.
		// Данная функция может быть вызвана только ПОСЛЕ BuildVariables().
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