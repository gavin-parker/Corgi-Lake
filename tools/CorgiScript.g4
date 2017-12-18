grammar CorgiScript;
/*
 * Parser Rules
 */
 
program : statements ;

statements :
statement ( SEMICOLON statement )*
;

statement :
WRITE OPENPAREN ( INTNUM | string ) CLOSEPAREN
| WRITELN
| IDENT  ASSIGNMENT exp
| IF boolexp THEN statement ELSE statement
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
| exp LESSEQUAL exp
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

//---------------------------------------------------------------------------
// OPERATORS
//---------------------------------------------------------------------------
SEMICOLON    : ';' ;
OPENPAREN    : '(' ;
CLOSEPAREN   : ')' ;

EQUAL        : '=';
ASSIGNMENT   : ':=';
LESSEQUAL    : '<=';
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