#include <Python.h>
#include <iostream>
#include <string>

int main(int agrc, char**argv){
    Py_Initialize();
    // Simple string
    PyRun_SimpleString("a = 1");
    PyRun_SimpleString("a += 1; print(a)");
    PyRun_SimpleString("print(locals())");
    // Function object
    std::string input = "def show():\n  b=a+1\n  print('from show', a,b)";
    // cannot edit value of a inside of show()
    PyObject *pCodeObj = Py_CompileString(input.c_str(), "", Py_file_input);
    std::cout << "pCodeObj = " << pCodeObj << std::endl;
    PyObject *pModule = PyImport_ExecCodeModule("__main__", pCodeObj);
    PyObject *pFunc = PyObject_GetAttrString(pModule, "show");
    std::cout << " PyFnc check = "<< PyFunction_Check(pFunc)<< std::endl;
    PyObject *pResult = PyObject_CallFunctionObjArgs(pFunc, NULL);
    std::cout << pResult << std::endl;
    pResult = PyObject_CallFunctionObjArgs(pFunc, NULL);
    PyObject* pResultRepr = PyObject_Repr( pResult ) ;
    std::cout << "The answer: " << PyUnicode_AsUTF8(pResultRepr) << std::endl ;

    Py_XDECREF(pResult);
    Py_XDECREF(pFunc);
    Py_XDECREF(pCodeObj);
    Py_Finalize();
    return 0;
}
