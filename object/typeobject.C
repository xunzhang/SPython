#include "pyobject.h"

PyTypeObject PyType_Type = {
  PyObject_HEAD_INIT(&PyType_Type)
  "type",	/* tp_name */
  0,	/* */
  0,	/* */
  0	/* */
};
