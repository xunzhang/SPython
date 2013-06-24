#include "stringobject.h"
#include <stdlib.h>
#include <string.h>

PyObject* PyStr_Create(const char* val) {
  PyStringObject* object = new PyStringObject;
  object->ob_refcnt = 1;
  object->ob_type = &PyString_Type;
  object->ob_size = (val == NULL) ? 0 : strlen(val);
  object->ob_shash = -1;
  memset(object->ob_sval, 0, 80);
  if(val != NULL)
    strcpy(object->ob_sval, val);
  return (PyObject *)object;
}

static long string_hash(PyStringObject *v) {
  register int len;
  register unsigned char *p;
  register long x;
  if(v->ob_shash != -1) 
    return v->ob_shash;
  len = v->ob_size;
  p = (unsigned char *)v->ob_sval;
  x = *p << 7;
  while(--len >= 0) 
    x = (1000003*x) ^ *p++;
  x ^= v->ob_size;
  if(x == -1)
    x = -2;
  v->ob_shash = x;
  return x;
}

static int string_print(PyStringObject* v) {
  printf("%s\n", v->ob_sval);
  return 0;
}

static PyObject* string_add(PyStringObject *l, PyStringObject *r) {
  PyStringObject *sum = (PyStringObject *)PyStr_Create(NULL);
  if(sum == NULL) {
    printf("new PyStringObject error!\n");
    exit(1);
  }
  else {
    strcpy(sum->ob_sval, l->ob_sval);
    strcat(sum->ob_sval, r->ob_sval);
  }
  return (PyObject *)sum;
}

static PyNumberMethods string_as_number = {
  (binaryfunc)string_add,
};

PyTypeObject PyString_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  "string",
  &string_as_number,
  (hashfunc)string_hash,
  (printfunc)string_print,
};
