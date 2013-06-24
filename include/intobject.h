#ifndef INTOBJECT_H 
#define INTOBJECT_H

#include "pyobject.h"

typedef struct {
  PyObject_HEAD
  int ob_ival;
} PyIntObject;

extern PyTypeObject PyInt_Type;

PyObject* CreatePyIntObject(int);

#endif
