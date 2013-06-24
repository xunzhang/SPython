#ifndef DICTOBJECT_H
#define DICTOBJECT_H

#include <map>
#include "pyobject.h"

typedef struct {
  PyObject_HEAD
  std::map<long, PyObject*> dict;  
} PyDictObject;

extern PyTypeObject PyDict_Type;

PyObject* PyDict_Create();

PyObject* PyDict_GetItem(PyObject*, PyObject*);

int PyDict_SetItem(PyObject*, PyObject*, PyObject*);

#endif
