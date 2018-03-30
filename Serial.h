#ifndef SERIAL_H
#define SERIAL_H

#include <string>
#include <python2.7/Python.h>

class Serial {
public:
    bool errs = false;

    Serial(int baudrate, std::string port);

    std::string read();

    void write(std::string &data);

    void close();

private:
    PyObject *writeArgs = PyTuple_New(1);
    PyObject *readf;
    PyObject *writef;
};


#endif