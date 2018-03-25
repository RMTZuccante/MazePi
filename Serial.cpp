#include <iostream>
#include "Serial.h"

Serial::Serial(int baudrate, std::string port) {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");

    PyObject *script = PyImport_Import(PyString_FromString("Serial"));
    PyObject *dic = PyModule_GetDict(script);
    PyObject *initf = PyDict_GetItemString(dic, "init");

    PyObject *args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, PyString_FromString(port.c_str()));
    PyTuple_SetItem(args, 1, PyInt_FromLong(baudrate));

    readf = PyDict_GetItemString(dic, "read");
    writef = PyDict_GetItemString(dic, "write");

    errs = !PyObject_IsTrue(PyObject_CallObject(initf, args));

    if (errs) close();
}

std::string Serial::read() {
    std::string s = PyString_AsString(PyObject_CallObject(readf, PyTuple_New(0)));
    PyErr_Print();
    return s;
}

void Serial::write(std::string &data) {
    PyTuple_SetItem(writeArgs, 0, PyString_FromString(data.c_str()));
    PyObject_CallObject(writef, writeArgs);
    PyErr_Print();
}

void Serial::close() {
    Py_Finalize();
}