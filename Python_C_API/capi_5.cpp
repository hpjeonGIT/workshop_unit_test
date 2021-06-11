#include <Python.h>
#include <iostream>
#include <string>

int main(int agrc, char**argv){
    Py_Initialize();
    // Function object
    std::string input = "a+=1; print('a=',a); print('a='a)"; // adding typo
    PyObject *pModule = PyImport_AddModule("__main__");
    PyObject *pGlobal = PyModule_GetDict(pModule); // !!! important !!!
    //
    PyObject *pCodeObj = PyRun_String(input.c_str(),Py_single_input, pGlobal, pGlobal);
    std::cout << "pCodeObj = " << pCodeObj << std::endl;
    // https://stackoverflow.com/questions/1796510/accessing-a-python-traceback-from-the-c-api
    if (!pCodeObj) {
        PyObject *pyExcType, *pyExcValue, *pyExcTraceBack;
        PyErr_Fetch(&pyExcType, &pyExcValue, &pyExcTraceBack);
        PyErr_NormalizeException(&pyExcType, &pyExcValue, &pyExcTraceBack);
        PyObject *str_exc_type = PyObject_Repr(pyExcType);
        PyObject *pyStr = PyUnicode_AsEncodedString(str_exc_type, "utf-8", "Error ~");
        const char *strExcType = PyBytes_AS_STRING(pyStr);
        std::cout << "Error type " << strExcType << std::endl; // <class 'SyntaxError'>
        PyObject *str_exc_value = PyObject_Repr(pyExcValue);
        PyObject *pyValueStr = PyUnicode_AsEncodedString(str_exc_value, "utf-8", "Error ~");
        const char *strExcValue = PyBytes_AS_STRING(pyValueStr);
        std::cout << "Error message " << strExcValue << std::endl;
        // SyntaxError('invalid syntax', ('<string>', 1, 32, "a+=1; print('a=',a); print('a='a)"))
        Py_XDECREF(pyExcType);
        Py_XDECREF(pyExcValue);
        Py_XDECREF(pyExcTraceBack);
    }
    Py_XDECREF(pCodeObj);
    //Py_XDECREF(pGlobal);
    Py_Finalize();
    return 0;
}
