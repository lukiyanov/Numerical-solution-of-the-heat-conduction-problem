
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>


// Generated from cpp/MathGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"
#include "MathGrammarParser.h"


namespace antlr4_generated {

/**
 * This interface defines an abstract listener for a parse tree produced by MathGrammarParser.
 */
class  MathGrammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterRoot(MathGrammarParser::RootContext *ctx) = 0;
  virtual void exitRoot(MathGrammarParser::RootContext *ctx) = 0;

  virtual void enterBool_expression(MathGrammarParser::Bool_expressionContext *ctx) = 0;
  virtual void exitBool_expression(MathGrammarParser::Bool_expressionContext *ctx) = 0;

  virtual void enterBool_atom(MathGrammarParser::Bool_atomContext *ctx) = 0;
  virtual void exitBool_atom(MathGrammarParser::Bool_atomContext *ctx) = 0;

  virtual void enterComparison(MathGrammarParser::ComparisonContext *ctx) = 0;
  virtual void exitComparison(MathGrammarParser::ComparisonContext *ctx) = 0;

  virtual void enterIf_expr(MathGrammarParser::If_exprContext *ctx) = 0;
  virtual void exitIf_expr(MathGrammarParser::If_exprContext *ctx) = 0;

  virtual void enterReal_expression(MathGrammarParser::Real_expressionContext *ctx) = 0;
  virtual void exitReal_expression(MathGrammarParser::Real_expressionContext *ctx) = 0;

  virtual void enterAdd_expr(MathGrammarParser::Add_exprContext *ctx) = 0;
  virtual void exitAdd_expr(MathGrammarParser::Add_exprContext *ctx) = 0;

  virtual void enterMult_expr(MathGrammarParser::Mult_exprContext *ctx) = 0;
  virtual void exitMult_expr(MathGrammarParser::Mult_exprContext *ctx) = 0;

  virtual void enterAtom(MathGrammarParser::AtomContext *ctx) = 0;
  virtual void exitAtom(MathGrammarParser::AtomContext *ctx) = 0;

  virtual void enterFunction(MathGrammarParser::FunctionContext *ctx) = 0;
  virtual void exitFunction(MathGrammarParser::FunctionContext *ctx) = 0;

  virtual void enterParam_list(MathGrammarParser::Param_listContext *ctx) = 0;
  virtual void exitParam_list(MathGrammarParser::Param_listContext *ctx) = 0;

  virtual void enterId(MathGrammarParser::IdContext *ctx) = 0;
  virtual void exitId(MathGrammarParser::IdContext *ctx) = 0;

  virtual void enterNumber(MathGrammarParser::NumberContext *ctx) = 0;
  virtual void exitNumber(MathGrammarParser::NumberContext *ctx) = 0;

  virtual void enterOpt_WS(MathGrammarParser::Opt_WSContext *ctx) = 0;
  virtual void exitOpt_WS(MathGrammarParser::Opt_WSContext *ctx) = 0;

  virtual void enterNothing(MathGrammarParser::NothingContext *ctx) = 0;
  virtual void exitNothing(MathGrammarParser::NothingContext *ctx) = 0;


};

}  // namespace antlr4_generated
