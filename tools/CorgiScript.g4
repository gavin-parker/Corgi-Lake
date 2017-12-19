grammar CorgiScript;
/*
 * Parser Rules
 */


program : (funcdef )* statements ;

statements :
statement ( SEMICOLON statement )* SEMICOLON
;

funcdef : DEF function statement ;

function : IDENT OPENPAREN (IDENT)* CLOSEPAREN
;

statement :
WRITE OPENPAREN ( INTNUM | string ) CLOSEPAREN
| WRITELN
| IDENT  ASSIGNMENT function
| IDENT  ASSIGNMENT exp
| IDENT ASSIGNMENT OPENARRAY INTNUM CLOSEARRAY
| IDENT OPENARRAY exp CLOSEARRAY ASSIGNMENT exp
| IF boolexp THEN statement ELSE statement
| function
| WHILE boolexp DO statement
| READ OPENPAREN IDENT CLOSEPAREN
| WRITE OPENPAREN exp CLOSEPAREN
| WRITE OPENPAREN boolexp CLOSEPAREN
| WRITE OPENPAREN string CLOSEPAREN
| OPENPAREN statements CLOSEPAREN
| GOTO IDENT
| IDENT
;

exp :
term ((PLUS | SUB) term )*
;
boolean_ :
TRUE
| FALSE
| exp EQUAL exp
| exp LESS exp
| OPENPAREN boolexp CLOSEPAREN
;
boolterm :
NOT boolean_
| boolean_
;
boolexp :
boolterm (AND boolterm)*
;
string : STRING ;

factor :
IDENT
| INTNUM
| OPENPAREN exp CLOSEPAREN
| IDENT OPENARRAY exp CLOSEARRAY
;
term :
factor ( (MULTIPLY|DIVIDE|MODULO) factor )*
;

/*
 * Lexer Rules
 */
 
//---------------------------------------------------------------------------
// KEYWORDS
//---------------------------------------------------------------------------
WRITE      : 'write' ;
WRITELN    : 'writeln' ;

DO		   : 'do';
ELSE 		: 'else';
FALSE		: 'false';
IF 			: 'if';
READ 		: 'read';
THEN 		: 'then';
TRUE 		: 'true';
WHILE 		: 'while';
GOTO		: 'goto';
DEF         : 'def';

//---------------------------------------------------------------------------
// OPERATORS
//---------------------------------------------------------------------------
SEMICOLON    : ';' ;
OPENPAREN    : '(' ;
CLOSEPAREN   : ')' ;

OPENARRAY    : '[';
CLOSEARRAY   : ']';
EQUAL        : '=';
ASSIGNMENT   : ':=';
LESS    : '<';
PLUS         : '+';
NOT 		 : '!';


MULTIPLY     : '*';
SUB          : '-';
AND          : '&';
DIVIDE 		 : '/';
MODULO 		 : '%';

INTNUM       : ('0'..'9')+ ;

STRING       : '\'' ('\'' '\'' | ~'\'')* '\'';

COMMENT      : '{' (~'}')* '}' -> skip ;

WS           : (' ' | '\t' | '\r' | '\n' )+ -> skip ;

IDENT 		 : ('a'..'z' | 'A'..'Z') ('a'..'z' | 'A'..'Z' | '0'..'9')* ;

COLON 		 : ':';