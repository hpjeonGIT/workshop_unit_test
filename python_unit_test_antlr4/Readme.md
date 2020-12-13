# ANTLR4 python3 code generation command:
- antlr4 -Dlanguage=Python3 CSV2.g4

# Using antlr4 in python3
```
import antlr4
import CSV2Lexer
import CSV2Parser
input = antlr4.FileStream('input.csv')
lexer = CSV2Lexer.CSV2Lexer(input)
stream = antlr4.CommonTokenStream(lexer)
parser = CSV2Parser.CSV2Parser(stream)
tree = parser.file()
tree.toStringTree()
'([] ([8] ([14 8] ([16 14 8] Name) , ([18 14 8]  occupation) , ([18 14 8]  id) , ([18 14 8]  factor) \\n)) ([9] ([16 9] kim) , ([18 9]  scientist) , ([18 9]  0123 ) , ([18 9]  0.5) \\n) ([9] ([16 9] jane) , ([18 9]  engineer ) , ([18 9]  494) , ([18 9]  0.12) \\n) ([9] ([16 9] Shery) , ([18 9]  secretary ) , ([18 9]  102) , ([18 9]  0.35) \\n))'
```

# Running Unit-test
- antlr4 -Dlanguage=Python3 CSV2.g4
- python3 sample_unittest.py
```
ANTLR runtime and generated code versions disagree: 4.9!=4.8
ANTLR runtime and generated code versions disagree: 4.9!=4.8
passed: ['kim', ' scientist', ' 0123 ', ' 0.5']
passed: ['jane', ' engineer ', ' 494', ' 0.12']
passed: ['Shery', ' secretary ', ' 102', ' 0.35']
.
----------------------------------------------------------------------
Ran 1 test in 0.005s
OK
```
