cmake_minimum_required(VERSION 3.18)

set(TARGET_NAME cpppython)

project(${TARGET_NAME})

set(Python3_USE_STATIC_LIBS TRUE)
find_package (Python REQUIRED COMPONENTS Interpreter Development)

# message(STATUS "Python_VERSION: ${Python_VERSION}")
# message(STATUS "Python_FOUND: ${Python_FOUND}")
# message(STATUS "Python_EXECUTABLE: ${Python_EXECUTABLE}")
# message(STATUS "Python_INCLUDE_DIRS: ${Python_INCLUDE_DIRS}")
# message(STATUS "Python_LIBRARIES: ${Python_LIBRARIES}")
# message(STATUS "Python_LIBRARY_DIRS: ${Python_LIBRARY_DIRS}")
# message(STATUS "Python_Development_FOUND: ${Python_Development_FOUND}")
# message(STATUS "Python_Interpreter_FOUND: ${Python_Interpreter_FOUND}")

add_executable(${TARGET_NAME} 
    src/main.c     
    src/pyfilter.c
    src/pyfilter.h
    src/pyfiltermodule.c
    src/pyfiltermodule.h
	src/example.py)

target_link_libraries(${TARGET_NAME} PRIVATE  Python::Python)
target_include_directories(${TARGET_NAME} PRIVATE ${Python_INCLUDE_DIRS})
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%;$<TARGET_FILE_DIR:Python::Python>")

install(TARGETS ${TARGET_NAME} DESTINATION bin$<$<CONFIG:Debug>:/debug>)
install(FILES src/example.py DESTINATION scripts)