# cpppython

This is a proof of concept project for educational purposes. It has been created in rapid prototyping approach. The project demonstrates how to call methods from a Python module, as well as how to create objects in Python modules. The main focus of this project is to demonstrate bi-directional communication between C/C++ and Python. Please keep in mind that this project has been created within 4-6 hours including induction and research. 

# Features

- load built-in modules
- execute Python methods from C/C++
- execute C/C++ object methods from Python
- load a module (*.py file) wich imports and uses built-in modules

# Dependencies

- CMake 3.18
- Python 3.9

# Testsetup

- Windows 10 x64
- CMake 3.18.2
- Python 3.9.1
    - (optional advanced options) Download debugging symbols
    - (optional advanced options) Download debug binaries (requires VS 2017 or later)
- Visual Studio 2017
    - Plattform Toolset: Visual Studio 2017 (v141)

Other operating systems might work as well.

# Known Issues

- While debugging the application prints the following output at the end:

```
D:\a\1\s\Modules\gcmodule.c:441: visit_decref: Assertion "!_PyObject_IsFreed(op)" failed
Enable tracemalloc to get the memory block allocation traceback

object address  : 000002534A56A410
object refcount : 2
object type     : 00007FF90249C650
object type name: dict
object repr     :
```