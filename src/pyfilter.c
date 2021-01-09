#define PY_SSIZE_T_CLEAN
#include <Python.h>

// source: https://docs.python.org/3/extending/newtypes_tutorial.html

typedef struct
{
	double value;
}  FilterModel;

typedef struct {
	PyObject_HEAD
		FilterModel model;
} FilterObject;

static PyObject* Filter_set_property(FilterObject* self, PyObject* args)
{
	const char* name;
	int value;
	if (!PyArg_ParseTuple(args, "si", &name, &value))
	{
		return NULL;
	}

	((FilterObject*)(self))->model.value = value;

	return PyBool_FromLong(1);
}

static PyObject* Filter_get_property(FilterObject* self, PyObject* args)
{
	const char* name;
	if (!PyArg_ParseTuple(args, "s", &name))
	{
		return NULL;
	}
	return PyFloat_FromDouble(((FilterObject*)(self))->model.value);
}

static PyMethodDef Filter_methods[] = {
	{"set_property", (PyCFunction)Filter_set_property, METH_VARARGS,	 ""	},
	{"get_property", (PyCFunction)Filter_get_property, METH_VARARGS,	 ""	},
	{NULL}
};

static PyModuleDef FilterModule = {
	PyModuleDef_HEAD_INIT,
	.m_name = "pyfilter",
	.m_doc = "Example module that creates an extension type.",
	.m_size = -1
};

static PyTypeObject FilterType = {
	PyVarObject_HEAD_INIT(NULL, 0)
	.tp_name = "pyfilter.Filter",
	.tp_doc = "Custom objects",
	.tp_basicsize = sizeof(FilterObject),
	.tp_itemsize = 0,
	.tp_flags = Py_TPFLAGS_DEFAULT,
	.tp_new = PyType_GenericNew,
	.tp_methods = Filter_methods
};

PyObject* PyInit_filter(void)
{
	if (PyType_Ready(&FilterType) < 0)
	{
		return NULL;
	}

	PyObject* m = PyModule_Create(&FilterModule);
	if (m == NULL)
	{
		return NULL;
	}

	Py_INCREF(&FilterType);
	if (PyModule_AddObject(m, "Filter", (PyObject *)&FilterType) < 0)
	{
		Py_DECREF(&FilterType);
		Py_DECREF(m);
		return NULL;
	}

	return m;
}