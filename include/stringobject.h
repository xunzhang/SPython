#ifndef STRINGOBJECT_H
#define STRINGOBJECT_H

#include "pyobject.h"

typedef struct {
  PyObject_HEAD
  int ob_size;
  long ob_shash;
  char ob_sval[100];   
} PyStringObject;

extern PyTypeObject PyString_Type;

PyObject* PyStr_Create(const char*);

#endif
