#include "intobject.h"

PyObject* CreatePyIntObject(int val) {
  PyIntObject* object= new PyIntObject;
  object->ob_refcnt = 1;
  object->ob_type = &PyInt_Type;
  object->ob_ival = val;
  return (PyObject *) object;
}

static long int_hash(PyObject* v) {
  int x = v->ob_ival;
  if(x == -1)
    x = -2;
  return (long)x;
}

static int int_print(PyObject* v) {
  PyIntObject* intv = (PyIntObject *)v;
  printf("%d\n", intv->ob_ival);
  return 0;
}

static PyObject* int_add(PyIntObject* l, PyIntObject* r) {
  PyIntObject *sum = (PyIntObject *)CreatePyIntObject(0);
  if(sum == NULL) {
    printf("new PyIntObject error!\n");
    exit(1);
  } else {
    sum->ob_ival = l->ob_ival + r->ob_ival;
  }
  return (PyObject *)sum;
}

static PyNumberMethods int_as_number = {
  (binaryfunc)int_add,
};


PyTypeObject PyInt_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  "int",
  &int_as_number,
  int_hash,
  int_print,
};
