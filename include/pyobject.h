#ifndef PYOBJECT_H
#define PYOBJECT_H

#include <stdio.h>

#define PyObject_HEAD	\
  int ob_refcnt;	\
  struct _typeobject *ob_type;

#define PyObject_HEAD_INIT(typePtr)	\
  0, typePtr,

//#define PyObject_VAR_HEAD	\
//  PyObject_HEAD
//  int ob_size; /* Number of items in variable part */

typedef struct _object {
  PyObject_HEAD
} PyObject;


typedef PyObject* (*binaryfunc)(PyObject*, PyObject*);
typedef long (*hashfunc)(PyObject *);
typedef int (*printfunc)(PyObject*);

typedef struct {
  binaryfunc add;
} PyNumberMethods;


typedef struct _typeobject {
  PyObject_HEAD
  const char* tp_name;
  PyNumberMethods *tp_as_number;
  hashfunc tp_hash; 
  printfunc tp_print;
} PyTypeObject;

extern PyTypeObject PyType_Type;

#endif
