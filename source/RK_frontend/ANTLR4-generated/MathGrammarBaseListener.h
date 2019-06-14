
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>


// Generated from cpp/MathGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MathGrammarListener.h"


namespace antlr4_generated {

/**
 * This class provides an empty implementation of MathGrammarListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  MathGrammarBaseListener : public MathGrammarListener {
public:

  virtual void enterRoot(MathGrammarParser::RootContext * /*ctx*/) override { }
  virtual void exitRoot(MathGrammarParser::RootContext * /*ctx*/) override { }

  virtual void enterBool_expression(MathGrammarParser::Bool_expressionContext * /*ctx*/) override { }
  virtual void exitBool_expression(MathGrammarParser::Bool_expressionContext * /*ctx*/) override { }

  virtual void enterBool_atom(MathGrammarParser::Bool_atomContext * /*ctx*/) override { }
  virtual void exitBool_atom(MathGrammarParser::Bool_atomContext * /*ctx*/) override { }

  virtual void enterComparison(MathGrammarParser::ComparisonContext * /*ctx*/) override { }
  virtual void exitComparison(MathGrammarParser::ComparisonContext * /*ctx*/) override { }

  virtual void enterIf_expr(MathGrammarParser::If_exprContext * /*ctx*/) override { }
  virtual void exitIf_expr(MathGrammarParser::If_exprContext * /*ctx*/) override { }

  virtual void enterReal_expression(MathGrammarParser::Real_expressionContext * /*ctx*/) override { }
  virtual void exitReal_expression(MathGrammarParser::Real_expressionContext * /*ctx*/) override { }

  virtual void enterAdd_expr(MathGrammarParser::Add_exprContext * /*ctx*/) override { }
  virtual void exitAdd_expr(MathGrammarParser::Add_exprContext * /*ctx*/) override { }

  virtual void enterMult_expr(MathGrammarParser::Mult_exprContext * /*ctx*/) override { }
  virtual void exitMult_expr(MathGrammarParser::Mult_exprContext * /*ctx*/) override { }

  virtual void enterAtom(MathGrammarParser::AtomContext * /*ctx*/) override { }
  virtual void exitAtom(MathGrammarParser::AtomContext * /*ctx*/) override { }

  virtual void enterFunction(MathGrammarParser::FunctionContext * /*ctx*/) override { }
  virtual void exitFunction(MathGrammarParser::FunctionContext * /*ctx*/) override { }

  virtual void enterParam_list(MathGrammarParser::Param_listContext * /*ctx*/) override { }
  virtual void exitParam_list(MathGrammarParser::Param_listContext * /*ctx*/) override { }

  virtual void enterId(MathGrammarParser::IdContext * /*ctx*/) override { }
  virtual void exitId(MathGrammarParser::IdContext * /*ctx*/) override { }

  virtual void enterNumber(MathGrammarParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(MathGrammarParser::NumberContext * /*ctx*/) override { }

  virtual void enterOpt_WS(MathGrammarParser::Opt_WSContext * /*ctx*/) override { }
  virtual void exitOpt_WS(MathGrammarParser::Opt_WSContext * /*ctx*/) override { }

  virtual void enterNothing(MathGrammarParser::NothingContext * /*ctx*/) override { }
  virtual void exitNothing(MathGrammarParser::NothingContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

}  // namespace antlr4_generated
