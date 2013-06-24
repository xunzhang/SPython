#ifndef INTOBJECT_H 
#define INTOBJECT_H

#include "pyobject.h"

typedef struct {
  PyObject_HEAD
  int ob_ival;
} PyIntObject;

PyObject* CreatePyIntObject(int);

#endif
