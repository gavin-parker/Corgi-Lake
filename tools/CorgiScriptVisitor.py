# Generated from CorgiScript.g4 by ANTLR 4.7.1
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .CorgiScriptParser import CorgiScriptParser
else:
    from CorgiScriptParser import CorgiScriptParser

# This class defines a complete generic visitor for a parse tree produced by CorgiScriptParser.

class CorgiScriptVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by CorgiScriptParser#program.
    def visitProgram(self, ctx:CorgiScriptParser.ProgramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#statements.
    def visitStatements(self, ctx:CorgiScriptParser.StatementsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#funcdef.
    def visitFuncdef(self, ctx:CorgiScriptParser.FuncdefContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#function.
    def visitFunction(self, ctx:CorgiScriptParser.FunctionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#statement.
    def visitStatement(self, ctx:CorgiScriptParser.StatementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#exp.
    def visitExp(self, ctx:CorgiScriptParser.ExpContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#boolean_.
    def visitBoolean_(self, ctx:CorgiScriptParser.Boolean_Context):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#boolterm.
    def visitBoolterm(self, ctx:CorgiScriptParser.BooltermContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#boolexp.
    def visitBoolexp(self, ctx:CorgiScriptParser.BoolexpContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#string.
    def visitString(self, ctx:CorgiScriptParser.StringContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#factor.
    def visitFactor(self, ctx:CorgiScriptParser.FactorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#term.
    def visitTerm(self, ctx:CorgiScriptParser.TermContext):
        return self.visitChildren(ctx)



del CorgiScriptParser