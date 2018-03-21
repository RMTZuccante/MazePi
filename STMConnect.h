#include <array>
#include <memory>
#include <sstream>
#include <iostream>
#include <python2.7/Python.h>
#include <fstream>

#ifndef STMCONNETCT_H
#define STMCONNETCT_H

class STMConnect {
public:
    static std::string exec(const char *cmd) {
        std::array<char, 128> buffer;
        std::string result;
        std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
        if (!pipe) throw std::runtime_error("popen() failed!");
        while (!feof(pipe.get())) {
            if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
                result += buffer.data();
        }
        return result;
    }

    STMConnect() {};

    int init(int baudrate) {
        port = findPort();

        if (port == "") return 1;

        Py_Initialize();

        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");

        PyObject *script = PyImport_Import(PyString_FromString("Serial"));
        PyErr_Print();

        PyObject *dic = PyModule_GetDict(script);
        PyObject *initf = PyDict_GetItemString(dic, "init");

        PyObject *args = PyTuple_New(3);
        PyTuple_SetItem(args, 0, PyString_FromString(("/dev/" + port).c_str()));

        PyTuple_SetItem(args, 1, PyInt_FromLong(baudrate));
        PyTuple_SetItem(args, 2, PyFloat_FromDouble(3));

        PyObject *stm = NULL;
        stm = PyObject_CallObject(initf, args);
        PyErr_Clear();

        if (stm == NULL) {
            Py_Finalize();
            return 2;
        }

        read = PyDict_GetItemString(dic, "read");
        write = PyDict_GetItemString(dic, "write");
        closef = PyDict_GetItemString(dic, "close");
        lcd_write = PyDict_GetItemString(dic, "lcdWrite");
        lcdw = PyTuple_New(1);
        PyTuple_SetItem(readargs, 0, stm);
        PyTuple_SetItem(writeargs, 0, stm);
        return 0;
    }

    std::string _read() {
        std::string s = PyString_AsString(PyObject_CallObject(read, readargs));
        PyErr_Print();
        return s;
    }

    void _write(std::string cmd) {
        PyTuple_SetItem(writeargs, 1, PyString_FromString(cmd.c_str()));
        PyObject_CallObject(write, writeargs);
        PyErr_Print();
    }

    static void lcd(std::string mex) {
        if (lcd_write == NULL) {
            Py_Initialize();

            PyRun_SimpleString("import sys");
            PyRun_SimpleString("sys.path.append(\".\")");

            PyObject *script = PyImport_Import(PyString_FromString("Serial"));
            PyErr_Print();

            PyObject *dic = PyModule_GetDict(script);
            lcd_write = PyDict_GetItemString(dic, "lcdWrite");
            lcdw = PyTuple_New(1);
        }
        PyTuple_SetItem(lcdw, 0, PyString_FromString(mex.c_str()));
        PyObject_CallObject(lcd_write, lcdw);
    }

    void close() {
        PyObject_CallObject(closef, readargs);
        PyErr_Print();
        Py_Finalize();
    }

    std::string getPort() {
        return port;
    }

private:
    PyObject *closef;
    PyObject *read;
    PyObject *write;
    static PyObject *lcd_write;

    PyObject *readargs = PyTuple_New(1);
    PyObject *writeargs = PyTuple_New(2);
    static PyObject *lcdw;

    std::string port;

    std::string findPort() {
        std::string list = STMConnect::exec("ls /dev/ | grep ACM");
        if (list == "") return list;
        std::stringstream ports(list);
        std::string port;
        std::string stm32;
        while (ports >> port) {
            //if (port.find("ACM") != std::string::npos)
            stm32 = port;
        }
        return stm32;
    }

    void replace(std::string *str, char a, char b) {
        for (int i = 0; i < str->size(); ++i) {
            if ((*str)[i] == a) (*str)[i] = b;
        }
    }
};

PyObject *STMConnect::lcd_write;
PyObject *STMConnect::lcdw;

#endif
