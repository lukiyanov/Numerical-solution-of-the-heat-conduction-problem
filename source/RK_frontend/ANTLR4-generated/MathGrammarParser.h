
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>


// Generated from cpp/MathGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"


namespace antlr4_generated {


class  MathGrammarParser : public antlr4::Parser {
public:
  enum {
    IF = 1, ELSE = 2, AND = 3, OR = 4, NOT = 5, ID = 6, P_FLOAT = 7, SEMIC = 8, 
    PLUS = 9, MINUS = 10, MUL = 11, DIV = 12, DOT = 13, COMMA = 14, EQVAL = 15, 
    NOT_EQVAL = 16, GREATER = 17, LESS = 18, GREATER_EQ = 19, LESS_EQ = 20, 
    BR_OP = 21, BR_CL = 22, WS = 23
  };

  enum {
    RuleRoot = 0, RuleBool_expression = 1, RuleBool_atom = 2, RuleComparison = 3, 
    RuleIf_expr = 4, RuleReal_expression = 5, RuleAdd_expr = 6, RuleMult_expr = 7, 
    RuleAtom = 8, RuleFunction = 9, RuleParam_list = 10, RuleId = 11, RuleNumber = 12, 
    RuleOpt_WS = 13, RuleNothing = 14
  };

  MathGrammarParser(antlr4::TokenStream *input);
  ~MathGrammarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class RootContext;
  class Bool_expressionContext;
  class Bool_atomContext;
  class ComparisonContext;
  class If_exprContext;
  class Real_expressionContext;
  class Add_exprContext;
  class Mult_exprContext;
  class AtomContext;
  class FunctionContext;
  class Param_listContext;
  class IdContext;
  class NumberContext;
  class Opt_WSContext;
  class NothingContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    lang::ExpressionType type;
    MathGrammarParser::Real_expressionContext *real_expressionContext = nullptr;;
    MathGrammarParser::Bool_expressionContext *bool_expressionContext = nullptr;;
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    antlr4::tree::TerminalNode *EOF();
    Real_expressionContext *real_expression();
    Bool_expressionContext *bool_expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RootContext* root();

  class  Bool_expressionContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::Bool_atomContext *first = nullptr;;
    MathGrammarParser::Bool_atomContext *next = nullptr;;
    Bool_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Bool_atomContext *> bool_atom();
    Bool_atomContext* bool_atom(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bool_expressionContext* bool_expression();

  class  Bool_atomContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::ComparisonContext *comparisonContext = nullptr;;
    MathGrammarParser::Bool_atomContext *bool_atomContext = nullptr;;
    MathGrammarParser::Bool_expressionContext *bool_expressionContext = nullptr;;
    Bool_atomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ComparisonContext *comparison();
    antlr4::tree::TerminalNode *NOT();
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    Bool_atomContext *bool_atom();
    antlr4::tree::TerminalNode *BR_OP();
    Bool_expressionContext *bool_expression();
    antlr4::tree::TerminalNode *BR_CL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Bool_atomContext* bool_atom();

  class  ComparisonContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::Real_expressionContext *left = nullptr;;
    MathGrammarParser::Real_expressionContext *right = nullptr;;
    ComparisonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    antlr4::tree::TerminalNode *EQVAL();
    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    antlr4::tree::TerminalNode *NOT_EQVAL();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER_EQ();
    antlr4::tree::TerminalNode *LESS_EQ();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ComparisonContext* comparison();

  class  If_exprContext : public antlr4::ParserRuleContext {
  public:
    lang::OperatorIf* node;
    MathGrammarParser::Bool_expressionContext *expr1 = nullptr;;
    MathGrammarParser::Real_expressionContext *exec1 = nullptr;;
    MathGrammarParser::Bool_expressionContext *expr_next = nullptr;;
    MathGrammarParser::Real_expressionContext *exec_next = nullptr;;
    MathGrammarParser::Real_expressionContext *last = nullptr;;
    If_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IF();
    antlr4::tree::TerminalNode* IF(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BR_OP();
    antlr4::tree::TerminalNode* BR_OP(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BR_CL();
    antlr4::tree::TerminalNode* BR_CL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ELSE();
    antlr4::tree::TerminalNode* ELSE(size_t i);
    antlr4::tree::TerminalNode *SEMIC();
    std::vector<Bool_expressionContext *> bool_expression();
    Bool_expressionContext* bool_expression(size_t i);
    std::vector<Real_expressionContext *> real_expression();
    Real_expressionContext* real_expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  If_exprContext* if_expr();

  class  Real_expressionContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::Add_exprContext *add_exprContext = nullptr;;
    Real_expressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Add_exprContext *add_expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Real_expressionContext* real_expression();

  class  Add_exprContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::Mult_exprContext *first = nullptr;;
    MathGrammarParser::Mult_exprContext *next = nullptr;;
    Add_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Mult_exprContext *> mult_expr();
    Mult_exprContext* mult_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Add_exprContext* add_expr();

  class  Mult_exprContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::AtomContext *first = nullptr;;
    MathGrammarParser::AtomContext *next = nullptr;;
    Mult_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AtomContext *> atom();
    AtomContext* atom(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MUL();
    antlr4::tree::TerminalNode* MUL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIV();
    antlr4::tree::TerminalNode* DIV(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Mult_exprContext* mult_expr();

  class  AtomContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::NumberContext *numberContext = nullptr;;
    MathGrammarParser::IdContext *idContext = nullptr;;
    MathGrammarParser::FunctionContext *functionContext = nullptr;;
    MathGrammarParser::If_exprContext *if_exprContext = nullptr;;
    MathGrammarParser::Add_exprContext *add_exprContext = nullptr;;
    AtomContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumberContext *number();
    IdContext *id();
    FunctionContext *function();
    If_exprContext *if_expr();
    antlr4::tree::TerminalNode *BR_OP();
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    Add_exprContext *add_expr();
    antlr4::tree::TerminalNode *BR_CL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AtomContext* atom();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    MathGrammarParser::IdContext *idContext = nullptr;;
    MathGrammarParser::Param_listContext *param_listContext = nullptr;;
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IdContext *id();
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    antlr4::tree::TerminalNode *BR_OP();
    antlr4::tree::TerminalNode *BR_CL();
    Param_listContext *param_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionContext* function();

  class  Param_listContext : public antlr4::ParserRuleContext {
  public:
    std::vector<lang::Calculatable*> args;
    MathGrammarParser::Add_exprContext *param = nullptr;;
    MathGrammarParser::Add_exprContext *last = nullptr;;
    Param_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Add_exprContext *> add_expr();
    Add_exprContext* add_expr(size_t i);
    std::vector<Opt_WSContext *> opt_WS();
    Opt_WSContext* opt_WS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Param_listContext* param_list();

  class  IdContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    IdContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IdContext* id();

  class  NumberContext : public antlr4::ParserRuleContext {
  public:
    lang::Calculatable* node;
    NumberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *P_FLOAT();
    antlr4::tree::TerminalNode *MINUS();
    Opt_WSContext *opt_WS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumberContext* number();

  class  Opt_WSContext : public antlr4::ParserRuleContext {
  public:
    Opt_WSContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WS();
    NothingContext *nothing();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Opt_WSContext* opt_WS();

  class  NothingContext : public antlr4::ParserRuleContext {
  public:
    NothingContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NothingContext* nothing();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace antlr4_generated
