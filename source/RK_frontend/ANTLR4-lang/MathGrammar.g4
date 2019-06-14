grammar MathGrammar;

@header{
#include "stdafx.h"
#include "../RK_frontend/lang/Calculatables.h"
#include <vector>
}

// NB: данная продукция включает в себя окружающие её пробелы,
// в то время как продукции более нижнего уровня включают только внутренние.
root
    returns [lang::Calculatable* node, lang::ExpressionType type]:
            opt_WS
            ( real_expression   { $node = $real_expression.node; $type = lang::ExpressionType::Double; }
            | bool_expression   { $node = $bool_expression.node; $type = lang::ExpressionType::Bool; }
            ) opt_WS EOF
            ;

// ----------------- BOOL ------------------------------------------------------

bool_expression
    returns [lang::Calculatable* node]:
            first=bool_atom                      { $node = $first.node; }
            ( opt_WS AND opt_WS next=bool_atom   { $node = new lang::OperatorAnd($node, $next.node); }
            | opt_WS OR  opt_WS next=bool_atom   { $node = new lang::OperatorOr ($node, $next.node); }
            )*;

bool_atom
    returns [lang::Calculatable* node]:
            comparison                                  { $node = $comparison.node; }
            | NOT opt_WS bool_atom                      { $node = new lang::OperatorNot($bool_atom.node); }
            | BR_OP opt_WS bool_expression opt_WS BR_CL { $node = $bool_expression.node; }
            ;

comparison
    returns [lang::Calculatable* node]:
            left=real_expression opt_WS EQVAL      opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::Equal); }
          | left=real_expression opt_WS NOT_EQVAL  opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::NotEqual); }
          | left=real_expression opt_WS GREATER    opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::Greater); }
          | left=real_expression opt_WS LESS       opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::Less); }
          | left=real_expression opt_WS GREATER_EQ opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::GreaterOrEqual); }
          | left=real_expression opt_WS LESS_EQ    opt_WS right=real_expression { $node = new lang::Comparison($left.node, $right.node, lang::CmpType::LessOrEqual); }
          ;

// ----------------- REAL ------------------------------------------------------


////////////////////////////////////////////////////////////////////////////////
// Оператор ветвления.
if_expr
    returns [lang::OperatorIf* node]:
            IF opt_WS
                BR_OP opt_WS expr1=bool_expression opt_WS BR_CL
                opt_WS exec1=real_expression
                    { $node = new lang::OperatorIf(); $node->AddElseIf($expr1.node, $exec1.node); }
            (opt_WS ELSE WS IF opt_WS
                BR_OP opt_WS expr_next=bool_expression opt_WS BR_CL
                opt_WS exec_next=real_expression
                    { $node->AddElseIf($expr_next.node, $exec_next.node); }
            )*
            opt_WS ELSE
                opt_WS last=real_expression opt_WS SEMIC
                    { $node->AddElse($last.node); }
             ;

////////////////////////////////////////////////////////////////////////////////
real_expression
    returns [lang::Calculatable* node]:
            add_expr { $node = $add_expr.node; };

////////////////////////////////////////////////////////////////////////////////
add_expr
    returns [lang::Calculatable* node]:
            first=mult_expr                      { $node = $first.node; }
            ( opt_WS PLUS  opt_WS next=mult_expr { $node = new lang::OperatorAdd($node, $next.node); }
            | opt_WS MINUS opt_WS next=mult_expr { $node = new lang::OperatorSub($node, $next.node); }
            )*;

////////////////////////////////////////////////////////////////////////////////
mult_expr
    returns [lang::Calculatable* node]:
            first=atom                    { $node = $first.node; }
            ( opt_WS MUL opt_WS next=atom { $node = new lang::OperatorMul($node, $next.node); }
            | opt_WS DIV opt_WS next=atom { $node = new lang::OperatorDiv($node, $next.node); }
            )*;

////////////////////////////////////////////////////////////////////////////////
atom
    returns [lang::Calculatable* node]:
              number    { $node = $number.node; }
            | id        { $node = $id.node; }
            | function  { $node = $function.node; }
            | if_expr   { $node = $if_expr.node; }
            | BR_OP opt_WS add_expr opt_WS BR_CL { $node = $add_expr.node; };

////////////////////////////////////////////////////////////////////////////////
function
    returns [lang::Calculatable* node]:
            id opt_WS
            ( BR_OP opt_WS BR_CL                   { $node = new lang::FunctionCall($id.node); }
            | BR_OP opt_WS param_list opt_WS BR_CL { $node = new lang::FunctionCall($id.node, $param_list.args); }
            );

////////////////////////////////////////////////////////////////////////////////
// Список параметров функции. Не может быть пуст.
param_list
    returns [std::vector<lang::Calculatable*> args]:
            (param=add_expr opt_WS COMMA opt_WS  { $args.push_back($param.node); }
            )*
            last=add_expr                        { $args.push_back($last.node); };

////////////////////////////////////////////////////////////////////////////////
// Идентификатор. Самостоятельный идентификатор становится переменной,
// входящий в функцию — именем функции.
id
    returns [lang::Calculatable* node]:
            ID { $node = new lang::Variable($text); } ;

////////////////////////////////////////////////////////////////////////////////
// Вещественное число.
number
    returns [lang::Calculatable* node]:
            (MINUS opt_WS)? P_FLOAT { $node = new lang::Number(atof(($text).c_str())); };

////////////////////////////////////////////////////////////////////////////////
// Пробельные символы, которые могут как быть, так и нет.
opt_WS: WS | nothing;

////////////////////////////////////////////////////////////////////////////////
nothing:    ;

// ----------------- LEXER -----------------------------------------------------
// Мы не различаем регистр идентификаторов.
fragment A: 'a' | 'A';
fragment B: 'b' | 'B';
fragment C: 'c' | 'C';
fragment D: 'd' | 'D';
fragment E: 'e' | 'E';
fragment F: 'f' | 'F';
fragment G: 'g' | 'G';
fragment H: 'h' | 'H';
fragment I: 'i' | 'I';
fragment J: 'j' | 'J';
fragment K: 'k' | 'K';
fragment L: 'l' | 'L';
fragment M: 'm' | 'M';
fragment N: 'n' | 'N';
fragment O: 'o' | 'O';
fragment P: 'p' | 'P';
fragment Q: 'q' | 'Q';
fragment R: 'r' | 'R';
fragment S: 's' | 'S';
fragment T: 't' | 'T';
fragment U: 'u' | 'U';
fragment V: 'v' | 'V';
fragment W: 'w' | 'W';
fragment X: 'x' | 'X';
fragment Y: 'y' | 'Y';
fragment Z: 'z' | 'Z';

IF:         I F;
ELSE:       E L S E;
AND:        A N D;
OR:         O R;
NOT:        N O T;

ID:         ([a-zA-Z] | '_') ([a-zA-Z] | '_' | [0-9])*;
P_FLOAT:    [0-9]+ (DOT [0-9]+)? (E (PLUS|MINUS)? [0-9]+)?; // P == Positive

SEMIC:      ';';
PLUS:       '+';
MINUS:      '-';
MUL:        '*';
DIV:        '/';
DOT:        '.';
COMMA:      ',';
EQVAL:      '=';
NOT_EQVAL:  '!=';
GREATER:    '>';
LESS:       '<';
GREATER_EQ: '>=';
LESS_EQ:    '<=';

BR_OP: '(';
BR_CL: ')';

WS: [ \n\t\r]+;