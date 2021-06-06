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
    PyObject *pCodeObj = Py_CompileString(input.c_str(), "", Py_file_input);
    std::cout << "pCodeObj = " << pCodeObj << std::endl;
    // Ref: https://stackoverflow.com/questions/46825656/python-c-api-how-to-retrieve-lineno-attribute-of-nameerror
    if (!pCodeObj) {
        PyObject *ptype = NULL, *pvalue = NULL, *ptraceback = NULL;
        PyObject *line_no = NULL, *line_no_str = NULL, *line_no_unicode = NULL;
        char *actual_line_no = NULL;
        int line_num = 0;
        PyErr_PrintEx(1); // inside this function the PyErr_Fetch(ptype, pvalue, ptraceback) is called
                          // retrieve the information gained from PyErr_Fetch() called inside PyErr_PrintEx(1)
/*
        pvalue     = PySys_GetObject("last_value");
        ptype      = PySys_GetObject("last_type");
        ptraceback = PySys_GetObject("last_traceback");
        if (ptype) {
            PyErr_NormalizeException(&ptype, &pvalue, &ptraceback);
        }
        if (pCodeObj) { // NameError
            if (ptraceback) {
                PyTracebackObject *tb_o = (PyTracebackObject *)ptraceback;
                line_num = tb_o->tb_lineno;
            }
        } else { //Syntax Error
            line_no = PyObject_GetAttrString(pvalue, "lineno");
            if (line_no) {
                line_no_str = PyObject_Str(line_no);
                if (line_no_str)     line_no_unicode = PyUnicode_AsEncodedString(line_no_str, "utf-8", "Error");
                if (line_no_unicode) actual_line_no = PyBytes_AsString(line_no_unicode);
                if (actual_line_no)  line_num = atoi(actual_line_no);
                std::cout << "line_no_unicode=" << line_no_unicode << std::endl;
                std::cout << "actual_line_no = " << actual_line_no << std::endl;
                std::cout << "line_num = " << line_num << std::endl;
                Py_XDECREF(line_no);
                Py_XDECREF(line_no_str);
                Py_XDECREF(line_no_unicode);
            }
        }
*/
    }
     Py_XDECREF(pCodeObj);
     //Py_XDECREF(pGlobal);
     Py_Finalize();
     return 0;
}
