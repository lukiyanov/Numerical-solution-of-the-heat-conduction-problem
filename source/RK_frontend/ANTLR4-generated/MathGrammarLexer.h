
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>


// Generated from cpp/MathGrammar.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"


namespace antlr4_generated {


class  MathGrammarLexer : public antlr4::Lexer {
public:
  enum {
    IF = 1, ELSE = 2, AND = 3, OR = 4, NOT = 5, ID = 6, P_FLOAT = 7, SEMIC = 8, 
    PLUS = 9, MINUS = 10, MUL = 11, DIV = 12, DOT = 13, COMMA = 14, EQVAL = 15, 
    NOT_EQVAL = 16, GREATER = 17, LESS = 18, GREATER_EQ = 19, LESS_EQ = 20, 
    BR_OP = 21, BR_CL = 22, WS = 23
  };

  MathGrammarLexer(antlr4::CharStream *input);
  ~MathGrammarLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

}  // namespace antlr4_generated
