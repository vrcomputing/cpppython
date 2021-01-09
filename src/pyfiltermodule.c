#include "pyfiltermodule.h"

// source: https://docs.python.org/3/extending/extending.html#a-simple-example

static PyObject* pyfilter_create_input_pin(PyObject* Py_UNUSED(self), PyObject *args)
{
	const char* command;
	if (!PyArg_ParseTuple(args, "s", &command))
	{
		return NULL;
	}
	return PyBool_FromLong(1);
}

static PyObject* pyfilter_create_output_pin(PyObject* Py_UNUSED(self), PyObject *args)
{
	const char* command;
	if (!PyArg_ParseTuple(args, "s", &command))
	{
		return NULL;
	}
	return PyBool_FromLong(1);
}

static PyMethodDef pyfiltermodulemethods[] = {
	{"create_input_pin",  pyfilter_create_input_pin, METH_VARARGS,	 "Creates a new input pin"},
	{"create_output_pin",  pyfilter_create_output_pin, METH_VARARGS,	 "Creates a new output pin"},
	{NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyfiltermodule = {
	PyModuleDef_HEAD_INIT,
	"pyfiltermodule", /* name of module */
	NULL,              /* module documentation, may be NULL */
	-1,               /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
	pyfiltermodulemethods
};

PyObject* PyInit_pyfilter(void)
{
	return PyModule_Create(&pyfiltermodule);
}