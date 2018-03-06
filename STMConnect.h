#include <string>
#include <array>
#include <memory>
#include <sstream>
#include <zconf.h>
#include <iostream>
#include <python2.7/Python.h>

using namespace std;

#ifndef UNTITLED_STMCONNETCT_H
#define UNTITLED_STMCONNETCT_H

class STMConnect {
public:
    static string exec(const char *cmd) {
        array<char, 128> buffer;
        string result;
        shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                result += buffer.data();
        }
        return result;
    }

    STMConnect(int baudrate) {
        Py_Initialize();

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");

        PyObject *script = PyImport_Import(PyString_FromString("Serial"));
        PyErr_Print();

        PyObject *dic = PyModule_GetDict(script);
        PyObject *initf = PyDict_GetItemString(dic, "init");

        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyString_FromString(("/dev/" + findPort()).c_str()));
        PyTuple_SetItem(args, 1, PyInt_FromLong(baudrate));
        PyTuple_SetItem(args, 2, PyFloat_FromDouble(3));

        PyObject *stm = NULL;
        while (stm == NULL) {
            usleep(5e5);
            stm = PyObject_CallObject(initf, args);
            PyErr_Clear();
        }

        read = PyDict_GetItemString(dic, "read");
        write = PyDict_GetItemString(dic, "write");
        closef = PyDict_GetItemString(dic, "close");
        lcd_write = PyDict_GetItemString(dic, "lcdWrite");
        PyTuple_SetItem(readargs, 0, stm);
        PyTuple_SetItem(writeargs, 0, stm);
    }

    string _read() {
        string s = PyString_AsString(PyObject_CallObject(read, readargs));
        PyErr_Print();
        return s;
    }

    void _write(string cmd) {
        cout << "ardp" << cmd << endl;
        PyTuple_SetItem(writeargs, 1, PyString_FromString(cmd.c_str()));
        PyObject_CallObject(write, writeargs);
        PyErr_Print();
    }

    void lcd(string mex) {
        PyObject_CallObject(lcd_write, PyString_FromString(mex.c_str()));
    }

    void close() {
        PyObject_CallObject(closef, readargs);
        PyErr_Print();
    }

private:
    PyObject *closef;
    PyObject *read;
    PyObject *write;
    PyObject *lcd_write;

    PyObject *readargs = PyTuple_New(1);
    PyObject *writeargs = PyTuple_New(2);

    string findPort() {
        string list = STMConnect::exec("ls /dev/");
        stringstream ports(list);
        string port;
        string stm32;
        while (ports >> port) {
            if (port.find("ACM") != string::npos)
                stm32 = port;
        }
        return stm32;
    }

    void replace(string *str, char a, char b) {
        for (int i = 0; i < str->size(); ++i) {
            if ((*str)[i] == a) (*str)[i] = b;
        }
    }
};

#endif //UNTITLED_STMCONNETCT_H
