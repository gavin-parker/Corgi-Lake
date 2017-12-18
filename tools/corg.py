import sys
import os
from antlr4 import *
from CorgiScriptLexer import CorgiScriptLexer
from CorgiScriptParser import CorgiScriptParser
from CorgiScriptListener import CorgiScriptListener
from CorgiScriptGenerator import CorgiScriptGenerator


def main(argv):
    for filename in os.listdir('./src'):
        if filename.endswith('.w'):
            input = FileStream('./src/' + filename)
            lexer = CorgiScriptLexer(input)
            stream = CommonTokenStream(lexer)
            parser = CorgiScriptParser(stream)
            tree = parser.program()
            outFile = open('./build/' + filename[:-2] + '.corg', 'w')
            visitor = CorgiScriptGenerator(outFile)
            visitor.visit(tree)
 
if __name__ == '__main__':
    main(sys.argv)