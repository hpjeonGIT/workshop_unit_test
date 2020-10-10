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
    std::string input = "a+=1; print('a=',a)";
    PyObject *pModule = PyImport_AddModule("__main__");
    PyObject *pGlobal = PyModule_GetDict(pModule); // !!! important !!!
    //
    PyObject *pCodeObj = Py_CompileString(input.c_str(), "", Py_file_input);
    std::cout << "pCodeObj = " << pCodeObj << std::endl;
    PyObject *pFunc = PyFunction_New (pCodeObj, pGlobal);
    std::cout << " PyFnc check = "<< PyFunction_Check(pFunc)<< std::endl;
    PyObject *pResult = PyObject_CallFunctionObjArgs(pFunc, NULL);
    pResult = PyObject_CallFunctionObjArgs(pFunc, NULL);

    Py_XDECREF(pResult);
    Py_XDECREF(pFunc);
    Py_XDECREF(pCodeObj);
    Py_XDECREF(pGlobal);
    Py_Finalize();
    return 0;
}
