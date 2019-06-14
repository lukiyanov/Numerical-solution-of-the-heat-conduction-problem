#include "stdafx.h"
#include "MathExpression.h"
#include "StdFunctions.h"
#include "VariableList.h"

#include "MathGrammarLexer.h"
#include "MathGrammarParser.h"
#include "LangErrorListener.h"
using namespace lang;

///////////////////////////////////////////////////////////////////////////////
MathExpression::MathExpression(const std::string& expression)
{
		using namespace antlr4_generated;
		using namespace antlr4;
		
		LangErrorListener listener;

		ANTLRInputStream input(expression);
		MathGrammarLexer lexer(&input);
		lexer.removeErrorListeners();
		lexer.addErrorListener(&listener);
		CommonTokenStream tokens(&lexer);
		MathGrammarParser parser(&tokens);
		parser.removeErrorListeners();
		parser.addErrorListener(&listener);

		// Получаем синтезированные атрибуты, само дерево нам не нужно
		auto root = parser.root();
		m_pRoot = root->node;
		m_type = root->type;

		if (!m_pRoot)
			throw std::exception("Неизвестная ошибка в выражении.");

		// Подготовка к запуску
		m_pRoot->ReportIDs(m_vars);
		m_vars.BuildVariables();
		m_pRoot->ResolveIDs(m_vars);
		m_pRoot->ResolveFuncs(m_funcs);

		// Сохраняем количество переменных
		m_nVariableCount = m_vars.GetVariableCount();
		
		// Всё, теперь можно подставлять переменные и запускать на выполнение.
}

///////////////////////////////////////////////////////////////////////////////
void MathExpression::GetVariableNames(std::vector<std::string>& names)
{
	m_vars.GetVariableNames(names);
}

///////////////////////////////////////////////////////////////////////////////
Variant MathExpression::Calculate(double *args)
{
	for (size_t i = 0; i < m_nVariableCount; i++)
		m_vars.SetVariable(i, args[i]);
	return m_pRoot->Calculate();
}

///////////////////////////////////////////////////////////////////////////////
