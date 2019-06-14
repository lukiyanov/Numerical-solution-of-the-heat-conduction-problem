#pragma once
#include "Calculatable.h"
#include "Function.h"
#include <string>
#include <map>

namespace lang {

	///////////////////////////////////////////////////////////////////////////
	class Number : public Calculatable
	{
		Variant m_number;
	public:
		Number(double number) : m_number({ number }) {}
		const Variant Calculate() override { return m_number; }
	};

	///////////////////////////////////////////////////////////////////////////
	class Variable : public Calculatable
	{
		std::string m_strName;
		Variant* m_pValue;
	public:
		Variable(const std::string& id) : m_strName(id) {}

		const std::string& GetName() const { return m_strName; }

		void ReportIDs(VariableList& vars) override
		{
			vars.AddVariable(m_strName);
		}

		void ResolveIDs(VariableList& vars) override
		{
			m_pValue = vars.GetVariable(m_strName);
		}

		const Variant Calculate() override { return *m_pValue; }
	};

	///////////////////////////////////////////////////////////////////////////
	// Обобщённый бинарный оператор, реализующий общее для всех бинарных операторов поведение.
	class BinaryOperator : public Calculatable
	{
	protected:
		Calculatable *m_pLeft, *m_pRight;
	public:
		BinaryOperator(Calculatable* left, Calculatable* right) : m_pLeft(left), m_pRight(right) {}

		// Делегирует то же самое левой и правой частям.
		void ReportIDs(VariableList& vars) override
		{
			m_pLeft->ReportIDs(vars);
			m_pRight->ReportIDs(vars);
		}

		// Делегирует то же самое левой и правой частям.
		void ResolveIDs(VariableList& vars) override
		{
			m_pLeft->ResolveIDs(vars);
			m_pRight->ResolveIDs(vars);
		}

		void ResolveFuncs(FunctionList& funcs) override
		{
			m_pLeft->ResolveFuncs(funcs);
			m_pRight->ResolveFuncs(funcs);
		}

	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorAdd : public BinaryOperator
	{
	public:
		OperatorAdd(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}
		
		const Variant Calculate() override
		{
			return{ m_pLeft->Calculate().doubleValue + m_pRight->Calculate().doubleValue };
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorSub : public BinaryOperator
	{
	public:
		OperatorSub(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}
		
		const Variant Calculate() override
		{
			return{ m_pLeft->Calculate().doubleValue - m_pRight->Calculate().doubleValue };
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorMul : public BinaryOperator
	{
	public:
		OperatorMul(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}
		
		const Variant Calculate() override
		{
			return{ m_pLeft->Calculate().doubleValue * m_pRight->Calculate().doubleValue };
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorDiv : public BinaryOperator
	{
	public:
		OperatorDiv(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}
		const Variant Calculate() override
		{
			return{ m_pLeft->Calculate().doubleValue / m_pRight->Calculate().doubleValue };
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class Reference : public Calculatable
	{
	protected:
		Calculatable *m_pObject;
	public:
		Reference(Calculatable* p) : m_pObject(p) {}
		const Variant Calculate()           override { return m_pObject->Calculate(); }
		void ReportIDs(VariableList& vars)  override { m_pObject->ReportIDs(vars); }
		void ResolveIDs(VariableList& vars) override { m_pObject->ResolveIDs(vars); }
		void ResolveFuncs(FunctionList& funcs) override { m_pObject->ResolveFuncs(funcs); }
	};

	///////////////////////////////////////////////////////////////////////////
	class FunctionCall : public Calculatable
	{
		const std::string m_strName;
		const std::vector<Calculatable*> m_vctArgList;
		Function* m_pFunction;
		double *args;

	public:
		FunctionCall(Calculatable* pName):
			m_strName(dynamic_cast<Variable*>(pName)->GetName()),
			args(0)
		{}

		FunctionCall(Calculatable* pName, std::vector<Calculatable*> args) :
			m_strName(dynamic_cast<Variable*>(pName)->GetName()),
			m_vctArgList(args),
			args(0)
		{}

		~FunctionCall() { delete[] args; }

		void ResolveFuncs(FunctionList& funcs) override
		{
			const auto size = m_vctArgList.size();

			// В этом месте могут генериться исключения класса std::exception
			m_pFunction = funcs.GetFunction(m_strName, size);

			delete[] args;
			args = new double[size];

			// Делегируем аргументам
			for (size_t i = 0, size = m_vctArgList.size(); i < size; i++)
				m_vctArgList[i]->ResolveFuncs(funcs);
		}

		void ReportIDs(VariableList& vars)  override
		{
			// Делегируем аргументам
			for (size_t i = 0, size = m_vctArgList.size(); i < size; i++)
				m_vctArgList[i]->ReportIDs(vars);
		}

		void ResolveIDs(VariableList& vars) override
		{
			// Делегируем аргументам
			for (size_t i = 0, size = m_vctArgList.size(); i < size; i++)
				m_vctArgList[i]->ResolveIDs(vars);
		}

		const Variant Calculate() override
		{
			// Вычисляем аргументы, сохраняем их в args и выполняем функцию
			for (size_t i = 0, size = m_vctArgList.size(); i < size; i++)
				args[i] = m_vctArgList[i]->Calculate().doubleValue;

			return m_pFunction->Calculate(args);
		}
	};

	///////////////////////////////////////////////////////////////////////////
	enum CmpType { Equal, NotEqual, Greater, Less, GreaterOrEqual, LessOrEqual };

	class Comparison : public BinaryOperator
	{
		CmpType m_CmpType;

	public:
		Comparison (Calculatable *left, Calculatable *right, CmpType cmpType)
			: BinaryOperator(left, right), m_CmpType(cmpType)
		{}

		const Variant Calculate() override
		{
			auto resultLeft  = m_pLeft->Calculate();
			auto resultRight = m_pRight->Calculate();
			Variant result;

			switch (m_CmpType)
			{
			case Equal:				result.boolValue = (resultLeft.doubleValue == resultRight.doubleValue);	break;
			case NotEqual:			result.boolValue = (resultLeft.doubleValue != resultRight.doubleValue);	break;
			case Greater:			result.boolValue = (resultLeft.doubleValue >  resultRight.doubleValue);	break;
			case Less:				result.boolValue = (resultLeft.doubleValue <  resultRight.doubleValue);	break;
			case GreaterOrEqual:	result.boolValue = (resultLeft.doubleValue >= resultRight.doubleValue);	break;
			case LessOrEqual:		result.boolValue = (resultLeft.doubleValue <= resultRight.doubleValue);	break;
			default:
				throw std::exception("ERROR: the unknown comparance operation found");
			}

			return result;
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorNot : public Reference
	{
	public:
		OperatorNot(Calculatable *pObject) 
			: Reference(pObject)
		{}

		const Variant Calculate() override
		{
			Variant result;
			result.boolValue = !(m_pObject->Calculate().boolValue);
			return result;
		}

	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorAnd : public BinaryOperator
	{
	public:
		OperatorAnd(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}

		const Variant Calculate() override
		{
			Variant result;
			result.boolValue = m_pLeft->Calculate().boolValue && m_pRight->Calculate().boolValue;
			return result;
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorOr : public BinaryOperator
	{
	public:
		OperatorOr(Calculatable* left, Calculatable* right) : BinaryOperator(left, right) {}

		const Variant Calculate() override
		{
			Variant result;
			result.boolValue = m_pLeft->Calculate().boolValue || m_pRight->Calculate().boolValue;
			return result;
		}
	};

	///////////////////////////////////////////////////////////////////////////
	class OperatorIf : public Calculatable
	{
		std::vector<std::pair<Calculatable*, Calculatable*>> m_vctBranches;
		Calculatable* pElseBranch;

	public:
		OperatorIf(): pElseBranch(0) {}

		void AddElseIf(Calculatable* expression, Calculatable* thingToDo)
		{
			m_vctBranches.push_back(std::pair<Calculatable*, Calculatable*>(expression, thingToDo));
		}
		
		void AddElse(Calculatable* thingToDo)
		{
			pElseBranch = thingToDo;
		}
		
		const Variant Calculate() override
		{
			for (size_t i = 0, size = m_vctBranches.size(); i < size; i++)
			{
				if (m_vctBranches[i].first->Calculate().boolValue)
					return m_vctBranches[i].second->Calculate();
			}

			return pElseBranch->Calculate();
		}

		void ReportIDs(VariableList& vars) override
		{
			// Просто делегируем всем составным частям
			for each (auto& pair in m_vctBranches) {
				pair.first->ReportIDs(vars);
				pair.second->ReportIDs(vars);
			}
			pElseBranch->ReportIDs(vars);
		}

		void ResolveIDs(VariableList& vars) override
		{
			// Просто делегируем всем составным частям
			for each (auto& pair in m_vctBranches) {
				pair.first->ResolveIDs(vars);
				pair.second->ResolveIDs(vars);
			}
			pElseBranch->ResolveIDs(vars);
		}

		void ResolveFuncs(FunctionList& funcs) override
		{
			// Просто делегируем всем составным частям
			for each (auto& pair in m_vctBranches) {
				pair.first->ResolveFuncs(funcs);
				pair.second->ResolveFuncs(funcs);
			}
			pElseBranch->ResolveFuncs(funcs);
		}
	};

	///////////////////////////////////////////////////////////////////////////
}