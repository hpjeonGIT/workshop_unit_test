import unittest
import sys
import os
import antlr4

def find_leaf(tree):
    alist = []
    for n in range(tree.getChildCount()):
        child = tree.getChild(n)
        if isinstance(child, antlr4.tree.Tree.TerminalNodeImpl):
            #print(n, child.getText())
            if (n == 0):
                value = child.getText()
                return value
        else:
            alist.append(find_leaf(child))
    return alist

class TestingSample(unittest.TestCase):
    def test_amother(self):
        import antlr4
        import CSV2Lexer
        import CSV2Parser
        input = antlr4.FileStream('input.csv')
        lexer = CSV2Lexer.CSV2Lexer(input)
        stream = antlr4.CommonTokenStream(lexer)
        parser = CSV2Parser.CSV2Parser(stream)
        tree = parser.file()
        #tree.toStringTree()
        res = find_leaf(tree)
        for el in range(1,4):
            with self.subTest(i=el):
                if len(res[el]) != 4:
                    self.fail("size doesn'n match:", res[el])
                else:
                    print("passed:", res[el])

if __name__ == '__main__':
    unittest.main()
