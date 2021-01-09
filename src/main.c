#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "pyfilter.h"
#include "pyfiltermodule.h"

int main(int argc, char* argv[])
{
	enum CLI { APP = 0, MODULE_PATH = 1, MODULE_NAME = 2, COUNT };
	const char* const property_module_path = argv[MODULE_PATH];
	const char* const property_module_name = argv[MODULE_NAME];

	if (argc != COUNT)
	{
		fprintf(stdout, "Usage: cpppython <MODULE_PATH> <MODULE_NAME>\n");
		exit(EXIT_SUCCESS);
	}

	if (PyImport_AppendInittab("pyfiltermodule", PyInit_pyfilter) == -1) {
		fprintf(stderr, "Error: could not extend in-built modules table\n");
		exit(EXIT_FAILURE);
	}

	if (PyImport_AppendInittab("pyfilter", PyInit_filter) == -1) {
		fprintf(stderr, "Error: could not extend in-built modules table\n");
		exit(EXIT_FAILURE);
	}

	Py_Initialize();
	{
		PyObject* sys_path = PySys_GetObject("path");
		PyObject* path = PyUnicode_FromString((const char*)property_module_path);
		const int insert_result = PyList_Insert(sys_path, 0, path);
		PyObject* module_name = PyUnicode_FromString((const char*)property_module_name);
		PyObject* module = PyImport_Import(module_name);

		// call process_input
		{
			PyObject* function = PyObject_GetAttrString(module, (const char*)"process_input");
			PyObject* name = PyUnicode_FromString("example_pin_name");
			PyObject* args = PyTuple_Pack(1, name);
			PyObject* result = PyObject_CallObject(function, args);
			const double value = PyFloat_AsDouble(result);

			// cleanup
			Py_DECREF(result);
			Py_DECREF(args);
			Py_DECREF(name);
			Py_DECREF(function);
		}

		// call process		
		{
			PyObject* function = PyObject_GetAttrString(module, (const char*)"process");
			PyObject* name = PyUnicode_FromString("example_runner");
			PyObject* args = PyTuple_Pack(1, name);
			PyObject* result = PyObject_CallObject(function, args);
			PyObject* body = PyUnicode_FromObject(result);
			const char* const data = PyUnicode_AsUTF8(body);

			// print the received html body
			fprintf(stdout, "%s\n", data);

			// cleanup
			Py_DECREF(body);
			Py_DECREF(result);
			Py_DECREF(args);
			Py_DECREF(name);
			Py_DECREF(function);
		}

		// cleanup
		Py_DECREF(module);
		Py_DECREF(module_name);
		Py_DECREF(path);
		//Py_DECREF(sys_path); // causes exception
	}
	Py_Finalize();

	return EXIT_SUCCESS;
}