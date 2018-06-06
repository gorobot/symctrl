// ----------------------------------------------------------------------
// Python Wrapper API Function Definitions
//
#include "py_wrapper.hpp"

#include "libsymctrl/c_wrapper.hpp"

// Function definitions.
PY_WRAPPER_FUNC(symss) {
  const char* name;

  if (!PyArg_ParseTuple(args, "s", &name))
    return NULL;

  printf("Hello %s!\n", name);

  Py_RETURN_NONE;
}

// Python Method Definitions
static PyMethodDef module_methods[] = {
  PY_WRAPPER_DEF(symss)
  {NULL, NULL, 0, NULL}
};

// Python Module Definition
static struct PyModuleDef pyctrlmodule = {
  PyModuleDef_HEAD_INIT,
  "pyctrl",
  NULL,
  -1,
  module_methods
};

// Initialization function.
PyMODINIT_FUNC
PyInit_pyctrl(void) {
  PyObject *m;

  m = PyModule_Create(&pyctrlmodule);

  if (m == NULL)
    return NULL;

  return m;
}
