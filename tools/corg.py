import sys
from antlr4 import *
from CorgiScriptLexer import CorgiScriptLexer
from CorgiScriptParser import CorgiScriptParser
from CorgiScriptListener import CorgiScriptListener
from CorgiScriptGenerator import CorgiScriptGenerator


def main(argv):
    input = FileStream(argv[1])
    lexer = CorgiScriptLexer(input)
    stream = CommonTokenStream(lexer)
    parser = CorgiScriptParser(stream)
    tree = parser.program()
    outFile = open('out.corg', 'w')
    visitor = CorgiScriptGenerator(outFile)
    visitor.visit(tree)
 
if __name__ == '__main__':
    main(sys.argv)