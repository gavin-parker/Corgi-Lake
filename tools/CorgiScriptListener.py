# Generated from CorgiScript.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .CorgiScriptParser import CorgiScriptParser
else:
    from CorgiScriptParser import CorgiScriptParser

# This class defines a complete listener for a parse tree produced by CorgiScriptParser.
class CorgiScriptListener(ParseTreeListener):

    # Enter a parse tree produced by CorgiScriptParser#program.
    def enterProgram(self, ctx:CorgiScriptParser.ProgramContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#program.
    def exitProgram(self, ctx:CorgiScriptParser.ProgramContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#statements.
    def enterStatements(self, ctx:CorgiScriptParser.StatementsContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#statements.
    def exitStatements(self, ctx:CorgiScriptParser.StatementsContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#statement.
    def enterStatement(self, ctx:CorgiScriptParser.StatementContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#statement.
    def exitStatement(self, ctx:CorgiScriptParser.StatementContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#exp.
    def enterExp(self, ctx:CorgiScriptParser.ExpContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#exp.
    def exitExp(self, ctx:CorgiScriptParser.ExpContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#boolean_.
    def enterBoolean_(self, ctx:CorgiScriptParser.Boolean_Context):
        pass

    # Exit a parse tree produced by CorgiScriptParser#boolean_.
    def exitBoolean_(self, ctx:CorgiScriptParser.Boolean_Context):
        pass


    # Enter a parse tree produced by CorgiScriptParser#boolterm.
    def enterBoolterm(self, ctx:CorgiScriptParser.BooltermContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#boolterm.
    def exitBoolterm(self, ctx:CorgiScriptParser.BooltermContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#boolexp.
    def enterBoolexp(self, ctx:CorgiScriptParser.BoolexpContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#boolexp.
    def exitBoolexp(self, ctx:CorgiScriptParser.BoolexpContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#string.
    def enterString(self, ctx:CorgiScriptParser.StringContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#string.
    def exitString(self, ctx:CorgiScriptParser.StringContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#factor.
    def enterFactor(self, ctx:CorgiScriptParser.FactorContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#factor.
    def exitFactor(self, ctx:CorgiScriptParser.FactorContext):
        pass


    # Enter a parse tree produced by CorgiScriptParser#term.
    def enterTerm(self, ctx:CorgiScriptParser.TermContext):
        pass

    # Exit a parse tree produced by CorgiScriptParser#term.
    def exitTerm(self, ctx:CorgiScriptParser.TermContext):
        pass


