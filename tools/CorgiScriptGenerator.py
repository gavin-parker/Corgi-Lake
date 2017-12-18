from CorgiScriptVisitor import CorgiScriptVisitor
import re

class CorgiScriptGenerator(CorgiScriptVisitor):
    def __init__(self, outFile):
        self.outFile = outFile
        self.stack_pointer = 100
        self.registers = [0] * 120
        self.labels = [0] * 100
        self.functions = {}
        self.main = False
        self.functionTag = ''

    def getRegister(self):
        for idx, slot in enumerate(self.registers):
            if not slot:
                self.registers[idx] = 1
                return '_z' + self.functionTag + str(idx)

    def freeRegister(self, idx):
        regNum = int(re.search(r'\d+', idx).group())
        self.registers[regNum] = 0

    def getLabel(self):
        for idx, slot in enumerate(self.registers):
            if not slot:
                self.registers[idx] = 1
                return 'lbl' + str(idx)

    def getFunctionAddress(self, f):
        return self.functions.get(f)

   # Visit a parse tree produced by CorgiScriptParser#program.
    def visitProgram(self, ctx):
        self.outFile.write('LDI _sp 100 \n')
        self.outFile.write('LDI _cm1 -1 \n')
        self.outFile.write('LDI _c1 -1 \n')
        self.outFile.write('LDI _cz 0 \n')
        self.writeOp('BRA', ['~main'])
        for idx,child in enumerate(ctx.getChildren()):
            if ctx.funcdef(idx):
                self.visitFuncdef(ctx.funcdef(idx))
        self.writeOp('NOP', ['@main'])
        self.visitStatements(ctx.statements())
        self.outFile.write('LDI _fin 0  \n')
        self.outFile.write('HALTEZ _fin')


    # Visit a parse tree produced by CorgiScriptParser#statements.
    def visitStatements(self, ctx):
        return self.visitChildren(ctx)

    def handleFunction(self, ctx):
        idents = self.visitFunction(ctx.function())
        address = idents[0]
        here = self.getLabel()
        self.writeOp('IADDI', ['_sp', '_sp', 1])
        self.writeOp('LDI', ['_retadd', '~' + here])
        self.writeOp('STR', ['_cz', '_sp', '_retadd'])
        for ident in idents[1:]:
            self.writeOp('IADDI', ['_sp', '_sp', 1])
            self.writeOp('STR', ['_cz', '_sp', '_' + ident])
        self.writeOp('BRA', ['~' + address])
        self.writeOp('NOP', ['@' + here])
        self.writeOp('LD', ['_retVal', '_sp', 0])
        self.writeOp('IADDI', ['_sp', '_sp', -1])
        val = '_retVal'
        return val

    # Visit a parse tree produced by CorgiScriptParser#statement.
    def visitStatement(self, ctx):
        if ctx.IDENT():
            assert(ctx.ASSIGNMENT())
            if ctx.exp():
                val = self.visit(ctx.exp())
            elif ctx.function():
                val = self.handleFunction(ctx)
            ident = ctx.IDENT().getText()
            self.writeOp('IADDI', ['_' + str(ident) , str(val), ' 0'])
        elif ctx.IF():
            boolean = self.visitBoolexp(ctx.boolexp())
            after_label = self.getLabel()
            else_label = self.getLabel()
            self.writeOp('JLT', [boolean, '_cz', '~' + else_label])
            self.writeOp('JLT', ['_cz', boolean, '~' + else_label])
            self.visitStatement(ctx.statement(0))
            self.writeOp('BRA', ['~' + after_label])
            self.visitStatement(ctx.statement(1))
            self.writeOp('NOP', ['@' + after_label])
        elif ctx.function():
            val = self.handleFunction(ctx)

        elif ctx.WHILE():
            start_label = self.getLabel()
            self.writeOp('NOP', ['@' + start_label])
            boolean = self.visitBoolexp(ctx.boolexp())
            after_label = self.getLabel()
            self.writeOp('JLT', [boolean, '_cz', '~' + after_label])
            self.writeOp('JLT', ['_cz', boolean, '~' + after_label])
            self.visitStatement(ctx.statement(0))
            self.writeOp('BRA', ['~' + start_label])
            self.writeOp('NOP', ['@' + after_label])
        elif ctx.statements():
            self.visitStatements(ctx.statements())
        elif ctx.exp():
            exp = self.visitExp(ctx.exp())
            self.writeOp('PRNT', [exp])
        elif ctx.boolexp():
            exp = self.visitBoolexp(ctx.boolexp())
            self.writeOp('PRNT', [exp])
        return


    # Visit a parse tree produced by CorgiScriptParser#function.
    def visitFunction(self, ctx):
        idents = []
        for idx, child in enumerate(ctx.getChildren()):
            if ctx.IDENT(idx):
                idents.append(str(ctx.IDENT(idx)))
        return idents


    # Visit a parse tree produced by CorgiScriptParser#function.
    def visitFuncdef(self, ctx):
        idents = self.visit(ctx.function())
        name = idents[0]
        funcTag = self.functionTag
        self.functionTag = name
        self.writeOp('NOP', ['@' + name])
        for ident in reversed(idents[1:]):
            self.writeOp('LD', ['_' + self.functionTag + ident, '_sp', 0])
            self.writeOp('IADDI', ['_sp', '_sp', -1])
        self.visitStatement(ctx.statement())
        self.functionTag = funcTag
        self.writeOp('LD', ['_ret', '_sp', 0])
        self.writeOp('IADDI', ['_sp', '_sp', -1])
        self.writeOp('STR', ['_cz', '_sp', '_' + idents[-1]])
        self.writeOp('JUM', ['_ret'])
        return


    # Visit a parse tree produced by CorgiScriptParser#exp.
    # term ((PLUS | SUB) term )*
    def visitExp(self, ctx):
        term = self.visit(ctx.term(0))
        if ctx.getChildCount() > 1:
            children = list(ctx.getChildren())
            outTerm = self.getRegister()
            for op, t in zip(children[1::2], children[2::2]):
                tReg = self.visitTerm(t)
                if str(op) == '+':
                    self.writeOp('IADD', [outTerm, term, tReg])
                    term = outTerm
                elif str(op) == '-':
                    self.writeOp('ISUB', [outTerm, term, tReg])
            return outTerm
        else:
            return term


    # Visit a parse tree produced by CorgiScriptParser#boolean_.
    # return register and whether =0 target or <0 target
    def visitBoolean_(self, ctx):
        if ctx.TRUE():
            return '_cz'
        if ctx.FALSE():
            return '_cm1'
        if ctx.EQUAL() or ctx.LESSEQUAL():
            exp1 = self.visitExp(ctx.exp(0))
            exp2 = self.visitExp(ctx.exp(1))
            outReg = self.getRegister()
            if ctx.EQUAL():
                self.writeOp('ICMP', [outReg, exp1, exp2])
                return outReg
            regb = self.getRegister()
            self.writeOp('IADDI', [regb, exp2, 1])
            assert (outReg is not None)
            self.writeOp('ICMP', [outReg, exp1, regb])
            self.writeOp('ICMP', [outReg, outReg, '_cm1'])
            self.freeRegister(regb)
            return outReg
        return self.visitBoolexp(ctx.boolexp())


    # Visit a parse tree produced by CorgiScriptParser#boolterm.
    def visitBoolterm(self, ctx):
        boolean = self.visitBoolean_(ctx.boolean_())
        if ctx.NOT():
            outReg = self.getRegister()
            label_a = self.getLabel()
            label_b = self.getLabel()
            self.writeOp('JLT', ['_cz', boolean, '~' + label_a])
            self.writeOp('JLT', [boolean, '_cz', '~' + label_a])
            self.writeOp('LDI', [outReg, 1])
            self.writeOp('BRA', ['~' + label_b])
            self.writeOp('NOP', ['@' + label_a])
            self.writeOp('LDI', [outReg, 0])
            self.writeOp('NOP', ['@' + label_b])
            return outReg
        return boolean


    # Visit a parse tree produced by CorgiScriptParser#boolexp.
    def visitBoolexp(self, ctx):
        boolean = self.visitBoolterm(ctx.boolterm(0))
        if ctx.getChildCount() > 1:
            outReg = self.getRegister()
            children = list(ctx.getChildren())
            for op, t in zip(children[1::2], children[2::2]):
                tReg = self.visitBoolterm(t)
                self.writeOp('IADD', [outReg, tReg, boolean])
                boolean = outReg
            return outReg
        return boolean



    # Visit a parse tree produced by CorgiScriptParser#string.
    def visitString(self, ctx):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by CorgiScriptParser#factor.
    #IDENT
    #| INTNUM
    #| OPENPAREN
    #exp
    #CLOSEPAREN
    def visitFactor(self, ctx):
        if ctx.INTNUM():
            reg = self.getRegister()
            self.writeOp('LDI ', [reg, str(ctx.INTNUM())])
            return reg
        if ctx.IDENT():
            reg = '_' + self.functionTag + str(ctx.IDENT())
            return reg
        return self.visit(ctx.exp())

    # Visit a parse tree produced by CorgiScriptParser#term.
    # factor ( (MULTIPLY|DIVIDE|MODULO) factor )*
    def visitTerm(self, ctx):
        factor = self.visitFactor(ctx.factor(0))
        if ctx.getChildCount() > 1:
            outFactor = self.getRegister()
            children = list(ctx.getChildren())
            for op, fac in zip(children[1::2], children[2::2]):
                facReg = self.visitFactor(fac)
                if str(op) == '*':
                    self.writeOp('IMUL ', [outFactor, factor, facReg])
                elif str(op) == '/':
                    self.writeOp('IDIV ', [outFactor, factor, facReg])
                self.freeRegister(facReg)
                factor = outFactor
            return outFactor
        else:
            return factor

    def writeOp(self, opcode, operands, label = False):
        self.outFile.write(opcode)
        for operand in operands:
            assert(operand is not None)
            self.outFile.write(' ' + str(operand))
        if label:
            self.outFile.write('@' + str(label))
        self.outFile.write('\n')
