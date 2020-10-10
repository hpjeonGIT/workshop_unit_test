#include <Python.h>
#include <iostream>
#include <string>
// Ref: https://awasu.com/weblog/embedding-python/calling-python-code-from-your-program/
int main(int agrc, char**argv){
    Py_Initialize();
    PyRun_SimpleString("a = 1");
    PyRun_SimpleString("a += 1; print(a)");
    PyRun_SimpleString("print(locals())");

    // Function object
    std::string input = "def add(n1,n2):\n  print(a)\n  return n1+n2";
    //
    PyObject *pArgs = PyTuple_New( 2 ) ;
    PyTuple_SetItem(pArgs, 0, PyLong_FromLong(10L));
    PyTuple_SetItem(pArgs, 1, PyLong_FromLong(100L));
    PyObject *pKywdArgs = PyDict_New() ; // this is dummy for now
    PyObject *pCodeObj = Py_CompileString(input.c_str(), "", Py_file_input);
    std::cout << "pCodeObj = " << pCodeObj << std::endl;
    PyObject *pModule = PyImport_ExecCodeModule("__main__", pCodeObj);
    PyObject *pFunc = PyObject_GetAttrString(pModule, "add");
    std::cout << "PyFnc check = "<< PyFunction_Check(pFunc)<< std::endl;
    PyObject *pResult = PyObject_Call(pFunc, pArgs, pKywdArgs);
    std::cout << pResult <<std::endl;
    PyObject* pResultRepr = PyObject_Repr( pResult ) ;
    std::cout << "The answer: " << PyUnicode_AsUTF8(pResultRepr) << std::endl ;

    Py_XDECREF(pResult);
    Py_XDECREF(pFunc);
    Py_XDECREF(pCodeObj);
    //Py_XDECREF(pGlobal);
    Py_Finalize();
    return 0;
}
