// ---------------------------------------------------------------------------
// Python Wrapper API Interface
//
#ifndef PYTHON_PY_WRAPPER_HPP
#define PYTHON_PY_WRAPPER_HPP

#include "Python.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef POS_PARAM
#define POS_PARAM METH_VARARGS
#endif

#ifndef KWD_PARAM
#define KWD_PARAM METH_VARARGS | METH_KEYWORDS
#endif

#ifndef PY_WRAPPER_FUNC
#define PY_WRAPPER_FUNC(name) \
static PyObject* pyctrl_##name(PyObject* self, PyObject* args)
#endif

#ifndef PY_WRAPPER_DESC
#define PY_WRAPPER_DESC(name) \
static char pyctrl_##name##_desc[]
#endif

#ifndef PY_WRAPPER_DEF
#define PY_WRAPPER_DEF(name) \
  {#name, pyctrl_##name, POS_PARAM, pyctrl_##name##_desc},
#endif

// Function descriptions.
PY_WRAPPER_DESC(symss) = "Create a state-space model.";

PY_WRAPPER_FUNC(symss);

#ifdef __cplusplus
}
#endif

#endif // PYTHON_PY_WRAPPER_HPP
