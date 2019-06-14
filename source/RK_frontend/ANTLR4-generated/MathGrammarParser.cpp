
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>


// Generated from cpp/MathGrammar.g4 by ANTLR 4.7


#include "MathGrammarListener.h"

#include "MathGrammarParser.h"


using namespace antlrcpp;
using namespace antlr4_generated;
using namespace antlr4;

MathGrammarParser::MathGrammarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

MathGrammarParser::~MathGrammarParser() {
  delete _interpreter;
}

std::string MathGrammarParser::getGrammarFileName() const {
  return "MathGrammar.g4";
}

const std::vector<std::string>& MathGrammarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& MathGrammarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- RootContext ------------------------------------------------------------------

MathGrammarParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::RootContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::RootContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

tree::TerminalNode* MathGrammarParser::RootContext::EOF() {
  return getToken(MathGrammarParser::EOF, 0);
}

MathGrammarParser::Real_expressionContext* MathGrammarParser::RootContext::real_expression() {
  return getRuleContext<MathGrammarParser::Real_expressionContext>(0);
}

MathGrammarParser::Bool_expressionContext* MathGrammarParser::RootContext::bool_expression() {
  return getRuleContext<MathGrammarParser::Bool_expressionContext>(0);
}


size_t MathGrammarParser::RootContext::getRuleIndex() const {
  return MathGrammarParser::RuleRoot;
}

void MathGrammarParser::RootContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoot(this);
}

void MathGrammarParser::RootContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoot(this);
}

MathGrammarParser::RootContext* MathGrammarParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, MathGrammarParser::RuleRoot);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(30);
    opt_WS();
    setState(37);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      setState(31);
      dynamic_cast<RootContext *>(_localctx)->real_expressionContext = real_expression();
       dynamic_cast<RootContext *>(_localctx)->node =  dynamic_cast<RootContext *>(_localctx)->real_expressionContext->node; dynamic_cast<RootContext *>(_localctx)->type =  lang::ExpressionType::Double; 
      break;
    }

    case 2: {
      setState(34);
      dynamic_cast<RootContext *>(_localctx)->bool_expressionContext = bool_expression();
       dynamic_cast<RootContext *>(_localctx)->node =  dynamic_cast<RootContext *>(_localctx)->bool_expressionContext->node; dynamic_cast<RootContext *>(_localctx)->type =  lang::ExpressionType::Bool; 
      break;
    }

    }
    setState(39);
    opt_WS();
    setState(40);
    match(MathGrammarParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_expressionContext ------------------------------------------------------------------

MathGrammarParser::Bool_expressionContext::Bool_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::Bool_atomContext *> MathGrammarParser::Bool_expressionContext::bool_atom() {
  return getRuleContexts<MathGrammarParser::Bool_atomContext>();
}

MathGrammarParser::Bool_atomContext* MathGrammarParser::Bool_expressionContext::bool_atom(size_t i) {
  return getRuleContext<MathGrammarParser::Bool_atomContext>(i);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::Bool_expressionContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::Bool_expressionContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Bool_expressionContext::AND() {
  return getTokens(MathGrammarParser::AND);
}

tree::TerminalNode* MathGrammarParser::Bool_expressionContext::AND(size_t i) {
  return getToken(MathGrammarParser::AND, i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Bool_expressionContext::OR() {
  return getTokens(MathGrammarParser::OR);
}

tree::TerminalNode* MathGrammarParser::Bool_expressionContext::OR(size_t i) {
  return getToken(MathGrammarParser::OR, i);
}


size_t MathGrammarParser::Bool_expressionContext::getRuleIndex() const {
  return MathGrammarParser::RuleBool_expression;
}

void MathGrammarParser::Bool_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBool_expression(this);
}

void MathGrammarParser::Bool_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBool_expression(this);
}

MathGrammarParser::Bool_expressionContext* MathGrammarParser::bool_expression() {
  Bool_expressionContext *_localctx = _tracker.createInstance<Bool_expressionContext>(_ctx, getState());
  enterRule(_localctx, 2, MathGrammarParser::RuleBool_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(42);
    dynamic_cast<Bool_expressionContext *>(_localctx)->first = bool_atom();
     dynamic_cast<Bool_expressionContext *>(_localctx)->node =  dynamic_cast<Bool_expressionContext *>(_localctx)->first->node; 
    setState(58);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(56);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          setState(44);
          opt_WS();
          setState(45);
          match(MathGrammarParser::AND);
          setState(46);
          opt_WS();
          setState(47);
          dynamic_cast<Bool_expressionContext *>(_localctx)->next = bool_atom();
           dynamic_cast<Bool_expressionContext *>(_localctx)->node =  new lang::OperatorAnd(_localctx->node, dynamic_cast<Bool_expressionContext *>(_localctx)->next->node); 
          break;
        }

        case 2: {
          setState(50);
          opt_WS();
          setState(51);
          match(MathGrammarParser::OR);
          setState(52);
          opt_WS();
          setState(53);
          dynamic_cast<Bool_expressionContext *>(_localctx)->next = bool_atom();
           dynamic_cast<Bool_expressionContext *>(_localctx)->node =  new lang::OperatorOr (_localctx->node, dynamic_cast<Bool_expressionContext *>(_localctx)->next->node); 
          break;
        }

        } 
      }
      setState(60);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Bool_atomContext ------------------------------------------------------------------

MathGrammarParser::Bool_atomContext::Bool_atomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MathGrammarParser::ComparisonContext* MathGrammarParser::Bool_atomContext::comparison() {
  return getRuleContext<MathGrammarParser::ComparisonContext>(0);
}

tree::TerminalNode* MathGrammarParser::Bool_atomContext::NOT() {
  return getToken(MathGrammarParser::NOT, 0);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::Bool_atomContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::Bool_atomContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

MathGrammarParser::Bool_atomContext* MathGrammarParser::Bool_atomContext::bool_atom() {
  return getRuleContext<MathGrammarParser::Bool_atomContext>(0);
}

tree::TerminalNode* MathGrammarParser::Bool_atomContext::BR_OP() {
  return getToken(MathGrammarParser::BR_OP, 0);
}

MathGrammarParser::Bool_expressionContext* MathGrammarParser::Bool_atomContext::bool_expression() {
  return getRuleContext<MathGrammarParser::Bool_expressionContext>(0);
}

tree::TerminalNode* MathGrammarParser::Bool_atomContext::BR_CL() {
  return getToken(MathGrammarParser::BR_CL, 0);
}


size_t MathGrammarParser::Bool_atomContext::getRuleIndex() const {
  return MathGrammarParser::RuleBool_atom;
}

void MathGrammarParser::Bool_atomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBool_atom(this);
}

void MathGrammarParser::Bool_atomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBool_atom(this);
}

MathGrammarParser::Bool_atomContext* MathGrammarParser::bool_atom() {
  Bool_atomContext *_localctx = _tracker.createInstance<Bool_atomContext>(_ctx, getState());
  enterRule(_localctx, 4, MathGrammarParser::RuleBool_atom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(76);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(61);
      dynamic_cast<Bool_atomContext *>(_localctx)->comparisonContext = comparison();
       dynamic_cast<Bool_atomContext *>(_localctx)->node =  dynamic_cast<Bool_atomContext *>(_localctx)->comparisonContext->node; 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(64);
      match(MathGrammarParser::NOT);
      setState(65);
      opt_WS();
      setState(66);
      dynamic_cast<Bool_atomContext *>(_localctx)->bool_atomContext = bool_atom();
       dynamic_cast<Bool_atomContext *>(_localctx)->node =  new lang::OperatorNot(dynamic_cast<Bool_atomContext *>(_localctx)->bool_atomContext->node); 
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(69);
      match(MathGrammarParser::BR_OP);
      setState(70);
      opt_WS();
      setState(71);
      dynamic_cast<Bool_atomContext *>(_localctx)->bool_expressionContext = bool_expression();
      setState(72);
      opt_WS();
      setState(73);
      match(MathGrammarParser::BR_CL);
       dynamic_cast<Bool_atomContext *>(_localctx)->node =  dynamic_cast<Bool_atomContext *>(_localctx)->bool_expressionContext->node; 
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonContext ------------------------------------------------------------------

MathGrammarParser::ComparisonContext::ComparisonContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::ComparisonContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::ComparisonContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::EQVAL() {
  return getToken(MathGrammarParser::EQVAL, 0);
}

std::vector<MathGrammarParser::Real_expressionContext *> MathGrammarParser::ComparisonContext::real_expression() {
  return getRuleContexts<MathGrammarParser::Real_expressionContext>();
}

MathGrammarParser::Real_expressionContext* MathGrammarParser::ComparisonContext::real_expression(size_t i) {
  return getRuleContext<MathGrammarParser::Real_expressionContext>(i);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::NOT_EQVAL() {
  return getToken(MathGrammarParser::NOT_EQVAL, 0);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::GREATER() {
  return getToken(MathGrammarParser::GREATER, 0);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::LESS() {
  return getToken(MathGrammarParser::LESS, 0);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::GREATER_EQ() {
  return getToken(MathGrammarParser::GREATER_EQ, 0);
}

tree::TerminalNode* MathGrammarParser::ComparisonContext::LESS_EQ() {
  return getToken(MathGrammarParser::LESS_EQ, 0);
}


size_t MathGrammarParser::ComparisonContext::getRuleIndex() const {
  return MathGrammarParser::RuleComparison;
}

void MathGrammarParser::ComparisonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}

void MathGrammarParser::ComparisonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}

MathGrammarParser::ComparisonContext* MathGrammarParser::comparison() {
  ComparisonContext *_localctx = _tracker.createInstance<ComparisonContext>(_ctx, getState());
  enterRule(_localctx, 6, MathGrammarParser::RuleComparison);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(120);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(78);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(79);
      opt_WS();
      setState(80);
      match(MathGrammarParser::EQVAL);
      setState(81);
      opt_WS();
      setState(82);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::Equal); 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(85);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(86);
      opt_WS();
      setState(87);
      match(MathGrammarParser::NOT_EQVAL);
      setState(88);
      opt_WS();
      setState(89);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::NotEqual); 
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(92);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(93);
      opt_WS();
      setState(94);
      match(MathGrammarParser::GREATER);
      setState(95);
      opt_WS();
      setState(96);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::Greater); 
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(99);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(100);
      opt_WS();
      setState(101);
      match(MathGrammarParser::LESS);
      setState(102);
      opt_WS();
      setState(103);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::Less); 
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(106);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(107);
      opt_WS();
      setState(108);
      match(MathGrammarParser::GREATER_EQ);
      setState(109);
      opt_WS();
      setState(110);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::GreaterOrEqual); 
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(113);
      dynamic_cast<ComparisonContext *>(_localctx)->left = real_expression();
      setState(114);
      opt_WS();
      setState(115);
      match(MathGrammarParser::LESS_EQ);
      setState(116);
      opt_WS();
      setState(117);
      dynamic_cast<ComparisonContext *>(_localctx)->right = real_expression();
       dynamic_cast<ComparisonContext *>(_localctx)->node =  new lang::Comparison(dynamic_cast<ComparisonContext *>(_localctx)->left->node, dynamic_cast<ComparisonContext *>(_localctx)->right->node, lang::CmpType::LessOrEqual); 
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_exprContext ------------------------------------------------------------------

MathGrammarParser::If_exprContext::If_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> MathGrammarParser::If_exprContext::IF() {
  return getTokens(MathGrammarParser::IF);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::IF(size_t i) {
  return getToken(MathGrammarParser::IF, i);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::If_exprContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::If_exprContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::If_exprContext::BR_OP() {
  return getTokens(MathGrammarParser::BR_OP);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::BR_OP(size_t i) {
  return getToken(MathGrammarParser::BR_OP, i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::If_exprContext::BR_CL() {
  return getTokens(MathGrammarParser::BR_CL);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::BR_CL(size_t i) {
  return getToken(MathGrammarParser::BR_CL, i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::If_exprContext::ELSE() {
  return getTokens(MathGrammarParser::ELSE);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::ELSE(size_t i) {
  return getToken(MathGrammarParser::ELSE, i);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::SEMIC() {
  return getToken(MathGrammarParser::SEMIC, 0);
}

std::vector<MathGrammarParser::Bool_expressionContext *> MathGrammarParser::If_exprContext::bool_expression() {
  return getRuleContexts<MathGrammarParser::Bool_expressionContext>();
}

MathGrammarParser::Bool_expressionContext* MathGrammarParser::If_exprContext::bool_expression(size_t i) {
  return getRuleContext<MathGrammarParser::Bool_expressionContext>(i);
}

std::vector<MathGrammarParser::Real_expressionContext *> MathGrammarParser::If_exprContext::real_expression() {
  return getRuleContexts<MathGrammarParser::Real_expressionContext>();
}

MathGrammarParser::Real_expressionContext* MathGrammarParser::If_exprContext::real_expression(size_t i) {
  return getRuleContext<MathGrammarParser::Real_expressionContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::If_exprContext::WS() {
  return getTokens(MathGrammarParser::WS);
}

tree::TerminalNode* MathGrammarParser::If_exprContext::WS(size_t i) {
  return getToken(MathGrammarParser::WS, i);
}


size_t MathGrammarParser::If_exprContext::getRuleIndex() const {
  return MathGrammarParser::RuleIf_expr;
}

void MathGrammarParser::If_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIf_expr(this);
}

void MathGrammarParser::If_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIf_expr(this);
}

MathGrammarParser::If_exprContext* MathGrammarParser::if_expr() {
  If_exprContext *_localctx = _tracker.createInstance<If_exprContext>(_ctx, getState());
  enterRule(_localctx, 8, MathGrammarParser::RuleIf_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(MathGrammarParser::IF);
    setState(123);
    opt_WS();
    setState(124);
    match(MathGrammarParser::BR_OP);
    setState(125);
    opt_WS();
    setState(126);
    dynamic_cast<If_exprContext *>(_localctx)->expr1 = bool_expression();
    setState(127);
    opt_WS();
    setState(128);
    match(MathGrammarParser::BR_CL);
    setState(129);
    opt_WS();
    setState(130);
    dynamic_cast<If_exprContext *>(_localctx)->exec1 = real_expression();
     dynamic_cast<If_exprContext *>(_localctx)->node =  new lang::OperatorIf(); _localctx->node->AddElseIf(dynamic_cast<If_exprContext *>(_localctx)->expr1->node, dynamic_cast<If_exprContext *>(_localctx)->exec1->node); 
    setState(148);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(132);
        opt_WS();
        setState(133);
        match(MathGrammarParser::ELSE);
        setState(134);
        match(MathGrammarParser::WS);
        setState(135);
        match(MathGrammarParser::IF);
        setState(136);
        opt_WS();
        setState(137);
        match(MathGrammarParser::BR_OP);
        setState(138);
        opt_WS();
        setState(139);
        dynamic_cast<If_exprContext *>(_localctx)->expr_next = bool_expression();
        setState(140);
        opt_WS();
        setState(141);
        match(MathGrammarParser::BR_CL);
        setState(142);
        opt_WS();
        setState(143);
        dynamic_cast<If_exprContext *>(_localctx)->exec_next = real_expression();
         _localctx->node->AddElseIf(dynamic_cast<If_exprContext *>(_localctx)->expr_next->node, dynamic_cast<If_exprContext *>(_localctx)->exec_next->node);  
      }
      setState(150);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx);
    }
    setState(151);
    opt_WS();
    setState(152);
    match(MathGrammarParser::ELSE);
    setState(153);
    opt_WS();
    setState(154);
    dynamic_cast<If_exprContext *>(_localctx)->last = real_expression();
    setState(155);
    opt_WS();
    setState(156);
    match(MathGrammarParser::SEMIC);
     _localctx->node->AddElse(dynamic_cast<If_exprContext *>(_localctx)->last->node); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Real_expressionContext ------------------------------------------------------------------

MathGrammarParser::Real_expressionContext::Real_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MathGrammarParser::Add_exprContext* MathGrammarParser::Real_expressionContext::add_expr() {
  return getRuleContext<MathGrammarParser::Add_exprContext>(0);
}


size_t MathGrammarParser::Real_expressionContext::getRuleIndex() const {
  return MathGrammarParser::RuleReal_expression;
}

void MathGrammarParser::Real_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReal_expression(this);
}

void MathGrammarParser::Real_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReal_expression(this);
}

MathGrammarParser::Real_expressionContext* MathGrammarParser::real_expression() {
  Real_expressionContext *_localctx = _tracker.createInstance<Real_expressionContext>(_ctx, getState());
  enterRule(_localctx, 10, MathGrammarParser::RuleReal_expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    dynamic_cast<Real_expressionContext *>(_localctx)->add_exprContext = add_expr();
     dynamic_cast<Real_expressionContext *>(_localctx)->node =  dynamic_cast<Real_expressionContext *>(_localctx)->add_exprContext->node; 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Add_exprContext ------------------------------------------------------------------

MathGrammarParser::Add_exprContext::Add_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::Mult_exprContext *> MathGrammarParser::Add_exprContext::mult_expr() {
  return getRuleContexts<MathGrammarParser::Mult_exprContext>();
}

MathGrammarParser::Mult_exprContext* MathGrammarParser::Add_exprContext::mult_expr(size_t i) {
  return getRuleContext<MathGrammarParser::Mult_exprContext>(i);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::Add_exprContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::Add_exprContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Add_exprContext::PLUS() {
  return getTokens(MathGrammarParser::PLUS);
}

tree::TerminalNode* MathGrammarParser::Add_exprContext::PLUS(size_t i) {
  return getToken(MathGrammarParser::PLUS, i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Add_exprContext::MINUS() {
  return getTokens(MathGrammarParser::MINUS);
}

tree::TerminalNode* MathGrammarParser::Add_exprContext::MINUS(size_t i) {
  return getToken(MathGrammarParser::MINUS, i);
}


size_t MathGrammarParser::Add_exprContext::getRuleIndex() const {
  return MathGrammarParser::RuleAdd_expr;
}

void MathGrammarParser::Add_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_expr(this);
}

void MathGrammarParser::Add_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_expr(this);
}

MathGrammarParser::Add_exprContext* MathGrammarParser::add_expr() {
  Add_exprContext *_localctx = _tracker.createInstance<Add_exprContext>(_ctx, getState());
  enterRule(_localctx, 12, MathGrammarParser::RuleAdd_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(162);
    dynamic_cast<Add_exprContext *>(_localctx)->first = mult_expr();
     dynamic_cast<Add_exprContext *>(_localctx)->node =  dynamic_cast<Add_exprContext *>(_localctx)->first->node; 
    setState(178);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(176);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          setState(164);
          opt_WS();
          setState(165);
          match(MathGrammarParser::PLUS);
          setState(166);
          opt_WS();
          setState(167);
          dynamic_cast<Add_exprContext *>(_localctx)->next = mult_expr();
           dynamic_cast<Add_exprContext *>(_localctx)->node =  new lang::OperatorAdd(_localctx->node, dynamic_cast<Add_exprContext *>(_localctx)->next->node); 
          break;
        }

        case 2: {
          setState(170);
          opt_WS();
          setState(171);
          match(MathGrammarParser::MINUS);
          setState(172);
          opt_WS();
          setState(173);
          dynamic_cast<Add_exprContext *>(_localctx)->next = mult_expr();
           dynamic_cast<Add_exprContext *>(_localctx)->node =  new lang::OperatorSub(_localctx->node, dynamic_cast<Add_exprContext *>(_localctx)->next->node); 
          break;
        }

        } 
      }
      setState(180);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Mult_exprContext ------------------------------------------------------------------

MathGrammarParser::Mult_exprContext::Mult_exprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::AtomContext *> MathGrammarParser::Mult_exprContext::atom() {
  return getRuleContexts<MathGrammarParser::AtomContext>();
}

MathGrammarParser::AtomContext* MathGrammarParser::Mult_exprContext::atom(size_t i) {
  return getRuleContext<MathGrammarParser::AtomContext>(i);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::Mult_exprContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::Mult_exprContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Mult_exprContext::MUL() {
  return getTokens(MathGrammarParser::MUL);
}

tree::TerminalNode* MathGrammarParser::Mult_exprContext::MUL(size_t i) {
  return getToken(MathGrammarParser::MUL, i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Mult_exprContext::DIV() {
  return getTokens(MathGrammarParser::DIV);
}

tree::TerminalNode* MathGrammarParser::Mult_exprContext::DIV(size_t i) {
  return getToken(MathGrammarParser::DIV, i);
}


size_t MathGrammarParser::Mult_exprContext::getRuleIndex() const {
  return MathGrammarParser::RuleMult_expr;
}

void MathGrammarParser::Mult_exprContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMult_expr(this);
}

void MathGrammarParser::Mult_exprContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMult_expr(this);
}

MathGrammarParser::Mult_exprContext* MathGrammarParser::mult_expr() {
  Mult_exprContext *_localctx = _tracker.createInstance<Mult_exprContext>(_ctx, getState());
  enterRule(_localctx, 14, MathGrammarParser::RuleMult_expr);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(181);
    dynamic_cast<Mult_exprContext *>(_localctx)->first = atom();
     dynamic_cast<Mult_exprContext *>(_localctx)->node =  dynamic_cast<Mult_exprContext *>(_localctx)->first->node; 
    setState(197);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(195);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          setState(183);
          opt_WS();
          setState(184);
          match(MathGrammarParser::MUL);
          setState(185);
          opt_WS();
          setState(186);
          dynamic_cast<Mult_exprContext *>(_localctx)->next = atom();
           dynamic_cast<Mult_exprContext *>(_localctx)->node =  new lang::OperatorMul(_localctx->node, dynamic_cast<Mult_exprContext *>(_localctx)->next->node); 
          break;
        }

        case 2: {
          setState(189);
          opt_WS();
          setState(190);
          match(MathGrammarParser::DIV);
          setState(191);
          opt_WS();
          setState(192);
          dynamic_cast<Mult_exprContext *>(_localctx)->next = atom();
           dynamic_cast<Mult_exprContext *>(_localctx)->node =  new lang::OperatorDiv(_localctx->node, dynamic_cast<Mult_exprContext *>(_localctx)->next->node); 
          break;
        }

        } 
      }
      setState(199);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AtomContext ------------------------------------------------------------------

MathGrammarParser::AtomContext::AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MathGrammarParser::NumberContext* MathGrammarParser::AtomContext::number() {
  return getRuleContext<MathGrammarParser::NumberContext>(0);
}

MathGrammarParser::IdContext* MathGrammarParser::AtomContext::id() {
  return getRuleContext<MathGrammarParser::IdContext>(0);
}

MathGrammarParser::FunctionContext* MathGrammarParser::AtomContext::function() {
  return getRuleContext<MathGrammarParser::FunctionContext>(0);
}

MathGrammarParser::If_exprContext* MathGrammarParser::AtomContext::if_expr() {
  return getRuleContext<MathGrammarParser::If_exprContext>(0);
}

tree::TerminalNode* MathGrammarParser::AtomContext::BR_OP() {
  return getToken(MathGrammarParser::BR_OP, 0);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::AtomContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::AtomContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

MathGrammarParser::Add_exprContext* MathGrammarParser::AtomContext::add_expr() {
  return getRuleContext<MathGrammarParser::Add_exprContext>(0);
}

tree::TerminalNode* MathGrammarParser::AtomContext::BR_CL() {
  return getToken(MathGrammarParser::BR_CL, 0);
}


size_t MathGrammarParser::AtomContext::getRuleIndex() const {
  return MathGrammarParser::RuleAtom;
}

void MathGrammarParser::AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtom(this);
}

void MathGrammarParser::AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtom(this);
}

MathGrammarParser::AtomContext* MathGrammarParser::atom() {
  AtomContext *_localctx = _tracker.createInstance<AtomContext>(_ctx, getState());
  enterRule(_localctx, 16, MathGrammarParser::RuleAtom);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(200);
      dynamic_cast<AtomContext *>(_localctx)->numberContext = number();
       dynamic_cast<AtomContext *>(_localctx)->node =  dynamic_cast<AtomContext *>(_localctx)->numberContext->node; 
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(203);
      dynamic_cast<AtomContext *>(_localctx)->idContext = id();
       dynamic_cast<AtomContext *>(_localctx)->node =  dynamic_cast<AtomContext *>(_localctx)->idContext->node; 
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(206);
      dynamic_cast<AtomContext *>(_localctx)->functionContext = function();
       dynamic_cast<AtomContext *>(_localctx)->node =  dynamic_cast<AtomContext *>(_localctx)->functionContext->node; 
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(209);
      dynamic_cast<AtomContext *>(_localctx)->if_exprContext = if_expr();
       dynamic_cast<AtomContext *>(_localctx)->node =  dynamic_cast<AtomContext *>(_localctx)->if_exprContext->node; 
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(212);
      match(MathGrammarParser::BR_OP);
      setState(213);
      opt_WS();
      setState(214);
      dynamic_cast<AtomContext *>(_localctx)->add_exprContext = add_expr();
      setState(215);
      opt_WS();
      setState(216);
      match(MathGrammarParser::BR_CL);
       dynamic_cast<AtomContext *>(_localctx)->node =  dynamic_cast<AtomContext *>(_localctx)->add_exprContext->node; 
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

MathGrammarParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

MathGrammarParser::IdContext* MathGrammarParser::FunctionContext::id() {
  return getRuleContext<MathGrammarParser::IdContext>(0);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::FunctionContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::FunctionContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

tree::TerminalNode* MathGrammarParser::FunctionContext::BR_OP() {
  return getToken(MathGrammarParser::BR_OP, 0);
}

tree::TerminalNode* MathGrammarParser::FunctionContext::BR_CL() {
  return getToken(MathGrammarParser::BR_CL, 0);
}

MathGrammarParser::Param_listContext* MathGrammarParser::FunctionContext::param_list() {
  return getRuleContext<MathGrammarParser::Param_listContext>(0);
}


size_t MathGrammarParser::FunctionContext::getRuleIndex() const {
  return MathGrammarParser::RuleFunction;
}

void MathGrammarParser::FunctionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunction(this);
}

void MathGrammarParser::FunctionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunction(this);
}

MathGrammarParser::FunctionContext* MathGrammarParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 18, MathGrammarParser::RuleFunction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(221);
    dynamic_cast<FunctionContext *>(_localctx)->idContext = id();
    setState(222);
    opt_WS();
    setState(235);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(223);
      match(MathGrammarParser::BR_OP);
      setState(224);
      opt_WS();
      setState(225);
      match(MathGrammarParser::BR_CL);
       dynamic_cast<FunctionContext *>(_localctx)->node =  new lang::FunctionCall(dynamic_cast<FunctionContext *>(_localctx)->idContext->node); 
      break;
    }

    case 2: {
      setState(228);
      match(MathGrammarParser::BR_OP);
      setState(229);
      opt_WS();
      setState(230);
      dynamic_cast<FunctionContext *>(_localctx)->param_listContext = param_list();
      setState(231);
      opt_WS();
      setState(232);
      match(MathGrammarParser::BR_CL);
       dynamic_cast<FunctionContext *>(_localctx)->node =  new lang::FunctionCall(dynamic_cast<FunctionContext *>(_localctx)->idContext->node, dynamic_cast<FunctionContext *>(_localctx)->param_listContext->args); 
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_listContext ------------------------------------------------------------------

MathGrammarParser::Param_listContext::Param_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<MathGrammarParser::Add_exprContext *> MathGrammarParser::Param_listContext::add_expr() {
  return getRuleContexts<MathGrammarParser::Add_exprContext>();
}

MathGrammarParser::Add_exprContext* MathGrammarParser::Param_listContext::add_expr(size_t i) {
  return getRuleContext<MathGrammarParser::Add_exprContext>(i);
}

std::vector<MathGrammarParser::Opt_WSContext *> MathGrammarParser::Param_listContext::opt_WS() {
  return getRuleContexts<MathGrammarParser::Opt_WSContext>();
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::Param_listContext::opt_WS(size_t i) {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(i);
}

std::vector<tree::TerminalNode *> MathGrammarParser::Param_listContext::COMMA() {
  return getTokens(MathGrammarParser::COMMA);
}

tree::TerminalNode* MathGrammarParser::Param_listContext::COMMA(size_t i) {
  return getToken(MathGrammarParser::COMMA, i);
}


size_t MathGrammarParser::Param_listContext::getRuleIndex() const {
  return MathGrammarParser::RuleParam_list;
}

void MathGrammarParser::Param_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_list(this);
}

void MathGrammarParser::Param_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_list(this);
}

MathGrammarParser::Param_listContext* MathGrammarParser::param_list() {
  Param_listContext *_localctx = _tracker.createInstance<Param_listContext>(_ctx, getState());
  enterRule(_localctx, 20, MathGrammarParser::RuleParam_list);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(245);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(237);
        dynamic_cast<Param_listContext *>(_localctx)->param = add_expr();
        setState(238);
        opt_WS();
        setState(239);
        match(MathGrammarParser::COMMA);
        setState(240);
        opt_WS();
         _localctx->args.push_back(dynamic_cast<Param_listContext *>(_localctx)->param->node);  
      }
      setState(247);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx);
    }
    setState(248);
    dynamic_cast<Param_listContext *>(_localctx)->last = add_expr();
     _localctx->args.push_back(dynamic_cast<Param_listContext *>(_localctx)->last->node); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdContext ------------------------------------------------------------------

MathGrammarParser::IdContext::IdContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MathGrammarParser::IdContext::ID() {
  return getToken(MathGrammarParser::ID, 0);
}


size_t MathGrammarParser::IdContext::getRuleIndex() const {
  return MathGrammarParser::RuleId;
}

void MathGrammarParser::IdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterId(this);
}

void MathGrammarParser::IdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitId(this);
}

MathGrammarParser::IdContext* MathGrammarParser::id() {
  IdContext *_localctx = _tracker.createInstance<IdContext>(_ctx, getState());
  enterRule(_localctx, 22, MathGrammarParser::RuleId);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    match(MathGrammarParser::ID);
     dynamic_cast<IdContext *>(_localctx)->node =  new lang::Variable(_input->getText(_localctx->start, _input->LT(-1))); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

MathGrammarParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MathGrammarParser::NumberContext::P_FLOAT() {
  return getToken(MathGrammarParser::P_FLOAT, 0);
}

tree::TerminalNode* MathGrammarParser::NumberContext::MINUS() {
  return getToken(MathGrammarParser::MINUS, 0);
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::NumberContext::opt_WS() {
  return getRuleContext<MathGrammarParser::Opt_WSContext>(0);
}


size_t MathGrammarParser::NumberContext::getRuleIndex() const {
  return MathGrammarParser::RuleNumber;
}

void MathGrammarParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}

void MathGrammarParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

MathGrammarParser::NumberContext* MathGrammarParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 24, MathGrammarParser::RuleNumber);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(256);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == MathGrammarParser::MINUS) {
      setState(254);
      match(MathGrammarParser::MINUS);
      setState(255);
      opt_WS();
    }
    setState(258);
    match(MathGrammarParser::P_FLOAT);
     dynamic_cast<NumberContext *>(_localctx)->node =  new lang::Number(atof((_input->getText(_localctx->start, _input->LT(-1))).c_str())); 
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Opt_WSContext ------------------------------------------------------------------

MathGrammarParser::Opt_WSContext::Opt_WSContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* MathGrammarParser::Opt_WSContext::WS() {
  return getToken(MathGrammarParser::WS, 0);
}

MathGrammarParser::NothingContext* MathGrammarParser::Opt_WSContext::nothing() {
  return getRuleContext<MathGrammarParser::NothingContext>(0);
}


size_t MathGrammarParser::Opt_WSContext::getRuleIndex() const {
  return MathGrammarParser::RuleOpt_WS;
}

void MathGrammarParser::Opt_WSContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOpt_WS(this);
}

void MathGrammarParser::Opt_WSContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOpt_WS(this);
}

MathGrammarParser::Opt_WSContext* MathGrammarParser::opt_WS() {
  Opt_WSContext *_localctx = _tracker.createInstance<Opt_WSContext>(_ctx, getState());
  enterRule(_localctx, 26, MathGrammarParser::RuleOpt_WS);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(263);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case MathGrammarParser::WS: {
        enterOuterAlt(_localctx, 1);
        setState(261);
        match(MathGrammarParser::WS);
        break;
      }

      case MathGrammarParser::EOF:
      case MathGrammarParser::IF:
      case MathGrammarParser::ELSE:
      case MathGrammarParser::AND:
      case MathGrammarParser::OR:
      case MathGrammarParser::NOT:
      case MathGrammarParser::ID:
      case MathGrammarParser::P_FLOAT:
      case MathGrammarParser::SEMIC:
      case MathGrammarParser::PLUS:
      case MathGrammarParser::MINUS:
      case MathGrammarParser::MUL:
      case MathGrammarParser::DIV:
      case MathGrammarParser::COMMA:
      case MathGrammarParser::EQVAL:
      case MathGrammarParser::NOT_EQVAL:
      case MathGrammarParser::GREATER:
      case MathGrammarParser::LESS:
      case MathGrammarParser::GREATER_EQ:
      case MathGrammarParser::LESS_EQ:
      case MathGrammarParser::BR_OP:
      case MathGrammarParser::BR_CL: {
        enterOuterAlt(_localctx, 2);
        setState(262);
        nothing();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NothingContext ------------------------------------------------------------------

MathGrammarParser::NothingContext::NothingContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t MathGrammarParser::NothingContext::getRuleIndex() const {
  return MathGrammarParser::RuleNothing;
}

void MathGrammarParser::NothingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNothing(this);
}

void MathGrammarParser::NothingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<MathGrammarListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNothing(this);
}

MathGrammarParser::NothingContext* MathGrammarParser::nothing() {
  NothingContext *_localctx = _tracker.createInstance<NothingContext>(_ctx, getState());
  enterRule(_localctx, 28, MathGrammarParser::RuleNothing);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);

   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> MathGrammarParser::_decisionToDFA;
atn::PredictionContextCache MathGrammarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN MathGrammarParser::_atn;
std::vector<uint16_t> MathGrammarParser::_serializedATN;

std::vector<std::string> MathGrammarParser::_ruleNames = {
  "root", "bool_expression", "bool_atom", "comparison", "if_expr", "real_expression", 
  "add_expr", "mult_expr", "atom", "function", "param_list", "id", "number", 
  "opt_WS", "nothing"
};

std::vector<std::string> MathGrammarParser::_literalNames = {
  "", "", "", "", "", "", "", "", "';'", "'+'", "'-'", "'*'", "'/'", "'.'", 
  "','", "'='", "'!='", "'>'", "'<'", "'>='", "'<='", "'('", "')'"
};

std::vector<std::string> MathGrammarParser::_symbolicNames = {
  "", "IF", "ELSE", "AND", "OR", "NOT", "ID", "P_FLOAT", "SEMIC", "PLUS", 
  "MINUS", "MUL", "DIV", "DOT", "COMMA", "EQVAL", "NOT_EQVAL", "GREATER", 
  "LESS", "GREATER_EQ", "LESS_EQ", "BR_OP", "BR_CL", "WS"
};

dfa::Vocabulary MathGrammarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> MathGrammarParser::_tokenNames;

MathGrammarParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x19, 0x10e, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 
    0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0x28, 0xa, 0x2, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x7, 0x3, 0x3b, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 
    0x3e, 0xb, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x4, 0x3, 0x4, 0x3, 0x4, 0x5, 0x4, 0x4f, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x7b, 0xa, 
    0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x7, 0x6, 0x95, 0xa, 0x6, 0xc, 0x6, 
    0xe, 0x6, 0x98, 0xb, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x7, 
    0x8, 0xb3, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0xb6, 0xb, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0xc6, 
    0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0xc9, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0xde, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0xee, 0xa, 
    0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 
    0xc, 0xf6, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xf9, 0xb, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 
    0xe, 0x103, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 
    0x5, 0xf, 0x10a, 0xa, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x2, 0x2, 
    0x11, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 
    0x1a, 0x1c, 0x1e, 0x2, 0x2, 0x2, 0x115, 0x2, 0x20, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x2c, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x8, 0x7a, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x7c, 0x3, 0x2, 0x2, 0x2, 0xc, 0xa1, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x10, 0xb7, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x14, 0xdf, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0xf7, 0x3, 0x2, 0x2, 0x2, 0x18, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x102, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x109, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x10b, 
    0x3, 0x2, 0x2, 0x2, 0x20, 0x27, 0x5, 0x1c, 0xf, 0x2, 0x21, 0x22, 0x5, 
    0xc, 0x7, 0x2, 0x22, 0x23, 0x8, 0x2, 0x1, 0x2, 0x23, 0x28, 0x3, 0x2, 
    0x2, 0x2, 0x24, 0x25, 0x5, 0x4, 0x3, 0x2, 0x25, 0x26, 0x8, 0x2, 0x1, 
    0x2, 0x26, 0x28, 0x3, 0x2, 0x2, 0x2, 0x27, 0x21, 0x3, 0x2, 0x2, 0x2, 
    0x27, 0x24, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 0x2, 0x2, 0x2, 0x29, 
    0x2a, 0x5, 0x1c, 0xf, 0x2, 0x2a, 0x2b, 0x7, 0x2, 0x2, 0x3, 0x2b, 0x3, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x5, 0x6, 0x4, 0x2, 0x2d, 0x3c, 0x8, 
    0x3, 0x1, 0x2, 0x2e, 0x2f, 0x5, 0x1c, 0xf, 0x2, 0x2f, 0x30, 0x7, 0x5, 
    0x2, 0x2, 0x30, 0x31, 0x5, 0x1c, 0xf, 0x2, 0x31, 0x32, 0x5, 0x6, 0x4, 
    0x2, 0x32, 0x33, 0x8, 0x3, 0x1, 0x2, 0x33, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x34, 0x35, 0x5, 0x1c, 0xf, 0x2, 0x35, 0x36, 0x7, 0x6, 0x2, 0x2, 0x36, 
    0x37, 0x5, 0x1c, 0xf, 0x2, 0x37, 0x38, 0x5, 0x6, 0x4, 0x2, 0x38, 0x39, 
    0x8, 0x3, 0x1, 0x2, 0x39, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x2e, 0x3, 
    0x2, 0x2, 0x2, 0x3a, 0x34, 0x3, 0x2, 0x2, 0x2, 0x3b, 0x3e, 0x3, 0x2, 
    0x2, 0x2, 0x3c, 0x3a, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x3d, 0x3, 0x2, 0x2, 
    0x2, 0x3d, 0x5, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x3c, 0x3, 0x2, 0x2, 0x2, 
    0x3f, 0x40, 0x5, 0x8, 0x5, 0x2, 0x40, 0x41, 0x8, 0x4, 0x1, 0x2, 0x41, 
    0x4f, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0x7, 0x7, 0x2, 0x2, 0x43, 0x44, 
    0x5, 0x1c, 0xf, 0x2, 0x44, 0x45, 0x5, 0x6, 0x4, 0x2, 0x45, 0x46, 0x8, 
    0x4, 0x1, 0x2, 0x46, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x47, 0x48, 0x7, 0x17, 
    0x2, 0x2, 0x48, 0x49, 0x5, 0x1c, 0xf, 0x2, 0x49, 0x4a, 0x5, 0x4, 0x3, 
    0x2, 0x4a, 0x4b, 0x5, 0x1c, 0xf, 0x2, 0x4b, 0x4c, 0x7, 0x18, 0x2, 0x2, 
    0x4c, 0x4d, 0x8, 0x4, 0x1, 0x2, 0x4d, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4e, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x42, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x47, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x7, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x5, 
    0xc, 0x7, 0x2, 0x51, 0x52, 0x5, 0x1c, 0xf, 0x2, 0x52, 0x53, 0x7, 0x11, 
    0x2, 0x2, 0x53, 0x54, 0x5, 0x1c, 0xf, 0x2, 0x54, 0x55, 0x5, 0xc, 0x7, 
    0x2, 0x55, 0x56, 0x8, 0x5, 0x1, 0x2, 0x56, 0x7b, 0x3, 0x2, 0x2, 0x2, 
    0x57, 0x58, 0x5, 0xc, 0x7, 0x2, 0x58, 0x59, 0x5, 0x1c, 0xf, 0x2, 0x59, 
    0x5a, 0x7, 0x12, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0x1c, 0xf, 0x2, 0x5b, 0x5c, 
    0x5, 0xc, 0x7, 0x2, 0x5c, 0x5d, 0x8, 0x5, 0x1, 0x2, 0x5d, 0x7b, 0x3, 
    0x2, 0x2, 0x2, 0x5e, 0x5f, 0x5, 0xc, 0x7, 0x2, 0x5f, 0x60, 0x5, 0x1c, 
    0xf, 0x2, 0x60, 0x61, 0x7, 0x13, 0x2, 0x2, 0x61, 0x62, 0x5, 0x1c, 0xf, 
    0x2, 0x62, 0x63, 0x5, 0xc, 0x7, 0x2, 0x63, 0x64, 0x8, 0x5, 0x1, 0x2, 
    0x64, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x65, 0x66, 0x5, 0xc, 0x7, 0x2, 0x66, 
    0x67, 0x5, 0x1c, 0xf, 0x2, 0x67, 0x68, 0x7, 0x14, 0x2, 0x2, 0x68, 0x69, 
    0x5, 0x1c, 0xf, 0x2, 0x69, 0x6a, 0x5, 0xc, 0x7, 0x2, 0x6a, 0x6b, 0x8, 
    0x5, 0x1, 0x2, 0x6b, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6d, 0x5, 0xc, 
    0x7, 0x2, 0x6d, 0x6e, 0x5, 0x1c, 0xf, 0x2, 0x6e, 0x6f, 0x7, 0x15, 0x2, 
    0x2, 0x6f, 0x70, 0x5, 0x1c, 0xf, 0x2, 0x70, 0x71, 0x5, 0xc, 0x7, 0x2, 
    0x71, 0x72, 0x8, 0x5, 0x1, 0x2, 0x72, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x73, 
    0x74, 0x5, 0xc, 0x7, 0x2, 0x74, 0x75, 0x5, 0x1c, 0xf, 0x2, 0x75, 0x76, 
    0x7, 0x16, 0x2, 0x2, 0x76, 0x77, 0x5, 0x1c, 0xf, 0x2, 0x77, 0x78, 0x5, 
    0xc, 0x7, 0x2, 0x78, 0x79, 0x8, 0x5, 0x1, 0x2, 0x79, 0x7b, 0x3, 0x2, 
    0x2, 0x2, 0x7a, 0x50, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x57, 0x3, 0x2, 0x2, 
    0x2, 0x7a, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x65, 0x3, 0x2, 0x2, 0x2, 
    0x7a, 0x6c, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x73, 0x3, 0x2, 0x2, 0x2, 0x7b, 
    0x9, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x3, 0x2, 0x2, 0x7d, 0x7e, 
    0x5, 0x1c, 0xf, 0x2, 0x7e, 0x7f, 0x7, 0x17, 0x2, 0x2, 0x7f, 0x80, 0x5, 
    0x1c, 0xf, 0x2, 0x80, 0x81, 0x5, 0x4, 0x3, 0x2, 0x81, 0x82, 0x5, 0x1c, 
    0xf, 0x2, 0x82, 0x83, 0x7, 0x18, 0x2, 0x2, 0x83, 0x84, 0x5, 0x1c, 0xf, 
    0x2, 0x84, 0x85, 0x5, 0xc, 0x7, 0x2, 0x85, 0x96, 0x8, 0x6, 0x1, 0x2, 
    0x86, 0x87, 0x5, 0x1c, 0xf, 0x2, 0x87, 0x88, 0x7, 0x4, 0x2, 0x2, 0x88, 
    0x89, 0x7, 0x19, 0x2, 0x2, 0x89, 0x8a, 0x7, 0x3, 0x2, 0x2, 0x8a, 0x8b, 
    0x5, 0x1c, 0xf, 0x2, 0x8b, 0x8c, 0x7, 0x17, 0x2, 0x2, 0x8c, 0x8d, 0x5, 
    0x1c, 0xf, 0x2, 0x8d, 0x8e, 0x5, 0x4, 0x3, 0x2, 0x8e, 0x8f, 0x5, 0x1c, 
    0xf, 0x2, 0x8f, 0x90, 0x7, 0x18, 0x2, 0x2, 0x90, 0x91, 0x5, 0x1c, 0xf, 
    0x2, 0x91, 0x92, 0x5, 0xc, 0x7, 0x2, 0x92, 0x93, 0x8, 0x6, 0x1, 0x2, 
    0x93, 0x95, 0x3, 0x2, 0x2, 0x2, 0x94, 0x86, 0x3, 0x2, 0x2, 0x2, 0x95, 
    0x98, 0x3, 0x2, 0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 0x2, 0x2, 0x96, 0x97, 
    0x3, 0x2, 0x2, 0x2, 0x97, 0x99, 0x3, 0x2, 0x2, 0x2, 0x98, 0x96, 0x3, 
    0x2, 0x2, 0x2, 0x99, 0x9a, 0x5, 0x1c, 0xf, 0x2, 0x9a, 0x9b, 0x7, 0x4, 
    0x2, 0x2, 0x9b, 0x9c, 0x5, 0x1c, 0xf, 0x2, 0x9c, 0x9d, 0x5, 0xc, 0x7, 
    0x2, 0x9d, 0x9e, 0x5, 0x1c, 0xf, 0x2, 0x9e, 0x9f, 0x7, 0xa, 0x2, 0x2, 
    0x9f, 0xa0, 0x8, 0x6, 0x1, 0x2, 0xa0, 0xb, 0x3, 0x2, 0x2, 0x2, 0xa1, 
    0xa2, 0x5, 0xe, 0x8, 0x2, 0xa2, 0xa3, 0x8, 0x7, 0x1, 0x2, 0xa3, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x5, 0x10, 0x9, 0x2, 0xa5, 0xb4, 0x8, 
    0x8, 0x1, 0x2, 0xa6, 0xa7, 0x5, 0x1c, 0xf, 0x2, 0xa7, 0xa8, 0x7, 0xb, 
    0x2, 0x2, 0xa8, 0xa9, 0x5, 0x1c, 0xf, 0x2, 0xa9, 0xaa, 0x5, 0x10, 0x9, 
    0x2, 0xaa, 0xab, 0x8, 0x8, 0x1, 0x2, 0xab, 0xb3, 0x3, 0x2, 0x2, 0x2, 
    0xac, 0xad, 0x5, 0x1c, 0xf, 0x2, 0xad, 0xae, 0x7, 0xc, 0x2, 0x2, 0xae, 
    0xaf, 0x5, 0x1c, 0xf, 0x2, 0xaf, 0xb0, 0x5, 0x10, 0x9, 0x2, 0xb0, 0xb1, 
    0x8, 0x8, 0x1, 0x2, 0xb1, 0xb3, 0x3, 0x2, 0x2, 0x2, 0xb2, 0xa6, 0x3, 
    0x2, 0x2, 0x2, 0xb2, 0xac, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb6, 0x3, 0x2, 
    0x2, 0x2, 0xb4, 0xb2, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xb5, 0x3, 0x2, 0x2, 
    0x2, 0xb5, 0xf, 0x3, 0x2, 0x2, 0x2, 0xb6, 0xb4, 0x3, 0x2, 0x2, 0x2, 
    0xb7, 0xb8, 0x5, 0x12, 0xa, 0x2, 0xb8, 0xc7, 0x8, 0x9, 0x1, 0x2, 0xb9, 
    0xba, 0x5, 0x1c, 0xf, 0x2, 0xba, 0xbb, 0x7, 0xd, 0x2, 0x2, 0xbb, 0xbc, 
    0x5, 0x1c, 0xf, 0x2, 0xbc, 0xbd, 0x5, 0x12, 0xa, 0x2, 0xbd, 0xbe, 0x8, 
    0x9, 0x1, 0x2, 0xbe, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc0, 0x5, 0x1c, 
    0xf, 0x2, 0xc0, 0xc1, 0x7, 0xe, 0x2, 0x2, 0xc1, 0xc2, 0x5, 0x1c, 0xf, 
    0x2, 0xc2, 0xc3, 0x5, 0x12, 0xa, 0x2, 0xc3, 0xc4, 0x8, 0x9, 0x1, 0x2, 
    0xc4, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xb9, 0x3, 0x2, 0x2, 0x2, 0xc5, 
    0xbf, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc9, 0x3, 0x2, 0x2, 0x2, 0xc7, 0xc5, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xca, 0xcb, 0x5, 0x1a, 
    0xe, 0x2, 0xcb, 0xcc, 0x8, 0xa, 0x1, 0x2, 0xcc, 0xde, 0x3, 0x2, 0x2, 
    0x2, 0xcd, 0xce, 0x5, 0x18, 0xd, 0x2, 0xce, 0xcf, 0x8, 0xa, 0x1, 0x2, 
    0xcf, 0xde, 0x3, 0x2, 0x2, 0x2, 0xd0, 0xd1, 0x5, 0x14, 0xb, 0x2, 0xd1, 
    0xd2, 0x8, 0xa, 0x1, 0x2, 0xd2, 0xde, 0x3, 0x2, 0x2, 0x2, 0xd3, 0xd4, 
    0x5, 0xa, 0x6, 0x2, 0xd4, 0xd5, 0x8, 0xa, 0x1, 0x2, 0xd5, 0xde, 0x3, 
    0x2, 0x2, 0x2, 0xd6, 0xd7, 0x7, 0x17, 0x2, 0x2, 0xd7, 0xd8, 0x5, 0x1c, 
    0xf, 0x2, 0xd8, 0xd9, 0x5, 0xe, 0x8, 0x2, 0xd9, 0xda, 0x5, 0x1c, 0xf, 
    0x2, 0xda, 0xdb, 0x7, 0x18, 0x2, 0x2, 0xdb, 0xdc, 0x8, 0xa, 0x1, 0x2, 
    0xdc, 0xde, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xca, 0x3, 0x2, 0x2, 0x2, 0xdd, 
    0xcd, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xd0, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xd3, 
    0x3, 0x2, 0x2, 0x2, 0xdd, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xde, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0xdf, 0xe0, 0x5, 0x18, 0xd, 0x2, 0xe0, 0xed, 0x5, 0x1c, 
    0xf, 0x2, 0xe1, 0xe2, 0x7, 0x17, 0x2, 0x2, 0xe2, 0xe3, 0x5, 0x1c, 0xf, 
    0x2, 0xe3, 0xe4, 0x7, 0x18, 0x2, 0x2, 0xe4, 0xe5, 0x8, 0xb, 0x1, 0x2, 
    0xe5, 0xee, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe7, 0x7, 0x17, 0x2, 0x2, 0xe7, 
    0xe8, 0x5, 0x1c, 0xf, 0x2, 0xe8, 0xe9, 0x5, 0x16, 0xc, 0x2, 0xe9, 0xea, 
    0x5, 0x1c, 0xf, 0x2, 0xea, 0xeb, 0x7, 0x18, 0x2, 0x2, 0xeb, 0xec, 0x8, 
    0xb, 0x1, 0x2, 0xec, 0xee, 0x3, 0x2, 0x2, 0x2, 0xed, 0xe1, 0x3, 0x2, 
    0x2, 0x2, 0xed, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xee, 0x15, 0x3, 0x2, 0x2, 
    0x2, 0xef, 0xf0, 0x5, 0xe, 0x8, 0x2, 0xf0, 0xf1, 0x5, 0x1c, 0xf, 0x2, 
    0xf1, 0xf2, 0x7, 0x10, 0x2, 0x2, 0xf2, 0xf3, 0x5, 0x1c, 0xf, 0x2, 0xf3, 
    0xf4, 0x8, 0xc, 0x1, 0x2, 0xf4, 0xf6, 0x3, 0x2, 0x2, 0x2, 0xf5, 0xef, 
    0x3, 0x2, 0x2, 0x2, 0xf6, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xf5, 0x3, 
    0x2, 0x2, 0x2, 0xf7, 0xf8, 0x3, 0x2, 0x2, 0x2, 0xf8, 0xfa, 0x3, 0x2, 
    0x2, 0x2, 0xf9, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x5, 0xe, 0x8, 
    0x2, 0xfb, 0xfc, 0x8, 0xc, 0x1, 0x2, 0xfc, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0xfd, 0xfe, 0x7, 0x8, 0x2, 0x2, 0xfe, 0xff, 0x8, 0xd, 0x1, 0x2, 0xff, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0x100, 0x101, 0x7, 0xc, 0x2, 0x2, 0x101, 0x103, 
    0x5, 0x1c, 0xf, 0x2, 0x102, 0x100, 0x3, 0x2, 0x2, 0x2, 0x102, 0x103, 
    0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 0x105, 
    0x7, 0x9, 0x2, 0x2, 0x105, 0x106, 0x8, 0xe, 0x1, 0x2, 0x106, 0x1b, 0x3, 
    0x2, 0x2, 0x2, 0x107, 0x10a, 0x7, 0x19, 0x2, 0x2, 0x108, 0x10a, 0x5, 
    0x1e, 0x10, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 0x2, 0x109, 0x108, 0x3, 
    0x2, 0x2, 0x2, 0x10a, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x10c, 0x3, 0x2, 
    0x2, 0x2, 0x10c, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x11, 0x27, 0x3a, 0x3c, 0x4e, 
    0x7a, 0x96, 0xb2, 0xb4, 0xc5, 0xc7, 0xdd, 0xed, 0xf7, 0x102, 0x109, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

MathGrammarParser::Initializer MathGrammarParser::_init;
