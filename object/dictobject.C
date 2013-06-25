#include "dictobject.h"
#include <stdlib.h>

PyObject* PyDict_Create() {
  PyDictObject* object = new PyDictObject;
  object->ob_refcnt = 1;
  object->ob_type = &PyDict_Type;
  return (PyObject *)object;
}

int PyDict_SetItem(PyObject *target, PyObject *key, PyObject *value) {
  long keyHashValue = (key->ob_type)->tp_hash(key);
  PyDictObject *dictobject = (PyDictObject *)target;
  (dictobject->dict)[keyHashValue] = value;
  return 0;
}

PyObject* PyDict_GetItem(PyObject *target, PyObject *key) {
  long keyHashValue = (key->ob_type)->tp_hash(key);
  std::map<long, PyObject*> dict = ((PyDictObject *)target)->dict;
  std::map<long, PyObject*>::iterator it = dict.find(keyHashValue);
  std::map<long, PyObject*>::iterator end = dict.end();
  if(it == end) return NULL;
  return it->second;
}

static int dict_print(PyDictObject *object) {
  PyDictObject *dictobject = (PyDictObject *)object;
  printf("{");
  std::map<long, PyObject*>::iterator it = (dictobject->dict).begin();
  std::map<long, PyObject*>::iterator end = (dictobject->dict).end();
  for(; it != end; ++it) {
    // print key
    printf("%ld : ", it->first);
    PyObject *val = it->second;
    // print value
    (val->ob_type)->tp_print(val);
    printf(", ");
  }
  printf("}\n");
}

PyTypeObject PyDict_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  "dict",
  0, /* tp_as_number */
  0, /* tp_hash(unhashable) */
  (printfunc)dict_print,
};
