# compiling command
- g++ -g -std=c++14 capi_0.cpp $(python3-config --includes) $(python3-config --ldflags)

# ref
- https://learning-python.com/class/Workbook/unit16.htm
- https://stackoverflow.com/questions/3789881/create-and-call-python-function-from-string-via-c-api
- https://stackoverflow.com/questions/3286448/calling-a-python-method-from-c-c-and-extracting-its-return-value
- Python callback: https://docs.python.org/3/extending/extending.html
- https://awasu.com/weblog/embedding-python/calling-python-code-from-your-program/

# Some descriptions
- capi_0.cpp: testing the basic PyRun_SimpleString
- capi_1.cpp: testing PyFunction_New()
- capi_2.cpp: testing ExecCodeModule, adding arguments
- capi_3.cpp: testing void functions
- capi_4.cpp: reads python script and detect any syntax error
```
./a.out
pCodeObj = 0
  File "", line 1
    a+=1; print('a=',a); print('a='a)
                                   ^
SyntaxError: invalid syntax
```
